#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "postgres.h"
#include "gram.h"
#include "utils/builtins.h"
#include "funcapi.h"
#include "executor/spi.h"
#include "access/heapam.h"
#include "fmgr.h"
#include "miscadmin.h"

#define ISINFINIT(x) strcmp(x,"INFINIT")==0 ? 0 : atof(x)
#define IS_FLOAT(x) (strcmp(x,"0")==0 || atof(x)) ? true : false
#define GET_TEXT(cstrp) DatumGetTextP(DirectFunctionCall1(textin, CStringGetDatum(cstrp)))
#define GET_STR(textp) DatumGetCString(DirectFunctionCall1(textout, PointerGetDatum(textp)))

extern Datum sqlf(PG_FUNCTION_ARGS);
extern Datum membdg(PG_FUNCTION_ARGS);

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(sqlf);

Datum
sqlf(PG_FUNCTION_ARGS)
{
    char                *query = GET_STR(PG_GETARG_TEXT_P(0));
    char                *sql;
    ReturnSetInfo       *rsinfo = (ReturnSetInfo *) fcinfo->resultinfo;
    Tuplestorestate     *tupstore;
    TupleDesc           tupdesc;
    int                 call_cntr;
    int                 max_calls;
    AttInMetadata       *attinmeta;
    SPITupleTable       *spi_tuptable;
    TupleDesc           spi_tupdesc;
    bool				firstpass;
    char                *lastrowid;
    int                 i;
    int                 num_categories;
    MemoryContext       per_query_ctx;
    MemoryContext       oldcontext;
    int                 ret;
    int                 proc;
    void                *result;
    
    sql=(char *)palloc(strlen(query)*sizeof(char *));

    yy_scan_string(query);

    yyparse(&result);

    sql=result;

    // check to see if caller supports us returning a tuplestore
    if (rsinfo == NULL || !IsA(rsinfo, ReturnSetInfo))
            ereport(ERROR,
                    (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
                     errmsg("set-valued function called in context that cannot accept a set")));
                     
    per_query_ctx = rsinfo->econtext->ecxt_per_query_memory;

    // Connect to SPI manager 
    if ((ret = SPI_connect()) < 0)
            // internal error
            elog(ERROR, "SPI_connect returned %d", ret);

    // Retrieve the desired rows
    ret = SPI_execute(sql, false, 0);
    proc = SPI_processed;

    // If no qualifying tuples, fall out early
    if (ret != SPI_OK_SELECT || proc <= 0)
    {
            SPI_finish();
            rsinfo->isDone = ExprEndResult;
            PG_RETURN_NULL();
    }

    spi_tuptable = SPI_tuptable;
    spi_tupdesc = spi_tuptable->tupdesc;

    // get a tuple descriptor for our result type
    switch (get_call_result_type(fcinfo, NULL, &tupdesc))
    {
            case TYPEFUNC_COMPOSITE:
                    // success 
                    break;
            case TYPEFUNC_RECORD:
                    // failed to determine actual type of RECORD
                    ereport(ERROR,
                            (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
                             errmsg("function returning record called in context "
                                            "that cannot accept type record")));
                    break;
            default:
                    // result type isn't composite
                    elog(ERROR, "return type must be a row type");
                    break;
    }


    // switch to long-lived memory context     
    oldcontext = MemoryContextSwitchTo(per_query_ctx);

    // make sure we have a persistent copy of the result tupdesc
    tupdesc = CreateTupleDescCopy(tupdesc);

    // initialize our tuplestore in long-lived context
    tupstore =
            tuplestore_begin_heap(true,false, work_mem);

    MemoryContextSwitchTo(oldcontext);

    
    //  Generate attribute metadata needed later to produce tuples from raw C
    // strings
	attinmeta = TupleDescGetAttInMetadata(tupdesc);

    // total number of tuples to be examined 
    max_calls = proc;

    // the return tuple always must have 1 rowid + num_categories columns
    num_categories = tupdesc->natts;

    firstpass = true;
    lastrowid = NULL;

    for (call_cntr = 0; call_cntr < max_calls; call_cntr++)
    {
        char            **values;
        HeapTuple	spi_tuple;
        HeapTuple	tuple;

        // allocate and zero space  
        values = (char **) palloc0((1 + num_categories) * sizeof(char *));

        // get the next sql result tuple  
        spi_tuple = spi_tuptable->vals[call_cntr];

        // now loop through the sql results and assign each value in sequence
        // to the next category
  
        for (i = 0; i < num_categories; i++)
        {
                // see if we've gone too far already  
                if (call_cntr >= max_calls)
                        break;

                values[i] = SPI_getvalue(spi_tuple, spi_tupdesc, i+1);
        }

        // build the tuple  
        tuple = BuildTupleFromCStrings(attinmeta, values);

        // switch to appropriate context while storing the tuple  
        oldcontext = MemoryContextSwitchTo(per_query_ctx);
        tuplestore_puttuple(tupstore, tuple);
        MemoryContextSwitchTo(oldcontext);

        heap_freetuple(tuple);

        // Clean up  
        for (i = 0; i < num_categories + 1; i++)
                if (values[i] != NULL)
                        pfree(values[i]);
        pfree(values);

    }

    // let the caller know we're sending back a tuplestore  
    rsinfo->returnMode = SFRM_Materialize;
    rsinfo->setResult = tupstore;
    rsinfo->setDesc = tupdesc;

    // release SPI related resources (and return to caller's context)  
    SPI_finish();

    return (Datum) 0;

}
 
PG_FUNCTION_INFO_V1(membdg);

Datum
membdg(PG_FUNCTION_ARGS)
{
    float field,min,fcore,score,max,range;
    double result, return_value;
    char *str_result;
	const char *mintxt=GET_STR(PG_GETARG_TEXT_P(1));
	const char *maxtxt=GET_STR(PG_GETARG_TEXT_P(4));
	const char *fcoretxt=GET_STR(PG_GETARG_TEXT_P(2));
	const char *scoretxt=GET_STR(PG_GETARG_TEXT_P(3));
	
    field=PG_GETARG_FLOAT8(0);

    min=ISINFINIT(mintxt);
    fcore=ISINFINIT(fcoretxt); //first core
    score=ISINFINIT(scoretxt); //second core
    max=ISINFINIT(maxtxt);
    result=0;

    //if min is INFINITE, then fcore should be INFINITE
    if (strcmp(mintxt,"INFINIT")==0){
        if (field<=score)
            result=1.0;
        else if (field>score)
            result=(field-max)*0.1;
    //if max is INFINITE, then score should be INFINITE
    }else if (strcmp(maxtxt,"INFINIT")==0){
        if (field>=fcore)
            result=1.0;
        else if (field<fcore)
            result=(field-min)*0.1;
    //Everything else
    }else if (field >= fcore && field <= score){
        result=1.0;
    }else{
        if (field>score){
            range=max-score;
            result=(field-max)/range;
        }else if (field<fcore){
            range=fcore-min;
            result=(field-min)/range;
        }
    }

    str_result=(char *)palloc(sizeof(double));

    snprintf(str_result,sizeof(double),"%.2f",fabs(result));

    return_value=atof(str_result);
	    
    pfree(str_result);
	
    //I do this to prevent a membership degree bigger than 1.0
    if (return_value>1.0)
        return Float8GetDatum(0.0);
    else  
        return Float8GetDatum(return_value);

}

PG_FUNCTION_INFO_V1(membdg_total);

Datum
membdg_total(PG_FUNCTION_ARGS)
{
	ArrayType  *qa = (ArrayType *) DatumGetPointer(PG_DETOAST_DATUM_COPY(PG_GETARG_DATUM(0)));
	static Oid	tsqOid = InvalidOid;
	Datum	   *elemsp;
	int			nelemsp;
	char 		*fuzzymdgs[1024];
	int 		i;
	float		tmp_result;
	char 		*pnum_s;
	char 		*opr;
	char 		*snum_s;
	
	deconstruct_array(qa, tsqOid, -1, false, 'i', &elemsp, NULL, &nelemsp);
	
	int 	j=0;	
	int 	p=0; //This is to pass through the indexes taken
	for (i=0;i<(nelemsp-1);i++){
		if ((i+2)>(nelemsp-1))
			break;
		pnum_s=GET_STR(elemsp[i]);
		opr=GET_STR(elemsp[i+1]);
		snum_s=GET_STR(elemsp[i+2]);
		if ((IS_FLOAT(pnum_s)) && (IS_FLOAT(snum_s))){
			float pnum=atof(pnum_s);
			float snum=atof(snum_s);
			p=i+2;
			if (pnum==snum)
				tmp_result=pnum;
			else if (strcmp(opr,"or")==0){
				if (pnum>snum)
					tmp_result=pnum;
				else if (snum>pnum)
					tmp_result=snum;
			}else if (strcmp(opr,"and")==0){
				if (pnum<snum)
					tmp_result=pnum;
				else if (snum<pnum)
					tmp_result=snum;	
			}
			fuzzymdgs[j]=(char *)palloc(sizeof(double));
		    snprintf(fuzzymdgs[j],sizeof(double),"%f",tmp_result);
			j++;
		}else{
			if (i>p){
				fuzzymdgs[j]=(char *)palloc(strlen(GET_STR(elemsp[i])));
				fuzzymdgs[j]=GET_STR(elemsp[i]);
				j++;
			}
		}
	}
	
	for (i=0;i<j;i++)
		pfree(fuzzymdgs[i]);
	
	return Float8GetDatum(tmp_result);
}