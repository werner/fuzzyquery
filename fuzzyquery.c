#include "postgres.h"
#include "gram.h"
#include "utils/builtins.h"
#include "funcapi.h"
#include "executor/spi.h"
#include "access/heapam.h"
#include "fmgr.h"
#include "miscadmin.h"

extern Datum sqlf(PG_FUNCTION_ARGS);

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(sqlf);

Datum
sqlf(PG_FUNCTION_ARGS)
{
    char                *query = text_to_cstring(PG_GETARG_TEXT_PP(0));
    char                *sql;
    ReturnSetInfo       *rsinfo = (ReturnSetInfo *) fcinfo->resultinfo;
    Tuplestorestate     *tupstore;
    TupleDesc           tupdesc;
    int                 call_cntr;
    int                 max_calls;
    AttInMetadata       *attinmeta;
    SPITupleTable       *spi_tuptable;
    TupleDesc           spi_tupdesc;
    bool		firstpass;
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

    /* check to see if caller supports us returning a tuplestore */
    if (rsinfo == NULL || !IsA(rsinfo, ReturnSetInfo))
            ereport(ERROR,
                    (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
                     errmsg("set-valued function called in context that cannot accept a set")));
    if (!(rsinfo->allowedModes & SFRM_Materialize))
            ereport(ERROR,
                    (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
                     errmsg("materialize mode required, but it is not " \
                                    "allowed in this context")));

    per_query_ctx = rsinfo->econtext->ecxt_per_query_memory;

    /* Connect to SPI manager */
    if ((ret = SPI_connect()) < 0)
            /* internal error */
            elog(ERROR, "SPI_connect returned %d", ret);

    /* Retrieve the desired rows */
    ret = SPI_execute(sql, false, 0);
    proc = SPI_processed;

    /* If no qualifying tuples, fall out early */
    if (ret != SPI_OK_SELECT || proc <= 0)
    {
            SPI_finish();
            rsinfo->isDone = ExprEndResult;
            PG_RETURN_NULL();
    }

    spi_tuptable = SPI_tuptable;
    spi_tupdesc = spi_tuptable->tupdesc;

    /* get a tuple descriptor for our result type */
    switch (get_call_result_type(fcinfo, NULL, &tupdesc))
    {
            case TYPEFUNC_COMPOSITE:
                    /* success */
                    break;
            case TYPEFUNC_RECORD:
                    /* failed to determine actual type of RECORD */
                    ereport(ERROR,
                            (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
                             errmsg("function returning record called in context "
                                            "that cannot accept type record")));
                    break;
            default:
                    /* result type isn't composite */
                    elog(ERROR, "return type must be a row type");
                    break;
    }


    /*
     * switch to long-lived memory context
     */
    oldcontext = MemoryContextSwitchTo(per_query_ctx);

    /* make sure we have a persistent copy of the result tupdesc */
    tupdesc = CreateTupleDescCopy(tupdesc);

    /* initialize our tuplestore in long-lived context */
    tupstore =
            tuplestore_begin_heap(rsinfo->allowedModes & SFRM_Materialize_Random,
                                                      false, work_mem);

    MemoryContextSwitchTo(oldcontext);


    /*
     * Generate attribute metadata needed later to produce tuples from raw C
     * strings
     */
    attinmeta = TupleDescGetAttInMetadata(tupdesc);

    /* total number of tuples to be examined */
    max_calls = proc;

    /* the return tuple always must have 1 rowid + num_categories columns */
    num_categories = tupdesc->natts;

    firstpass = true;
    lastrowid = NULL;

    for (call_cntr = 0; call_cntr < max_calls; call_cntr++)
    {
        char            **values;
        HeapTuple	spi_tuple;
        HeapTuple	tuple;

        /* allocate and zero space */
        values = (char **) palloc0((1 + num_categories) * sizeof(char *));

        /* get the next sql result tuple */
        spi_tuple = spi_tuptable->vals[call_cntr];

      /*
         * now loop through the sql results and assign each value in sequence
         * to the next category
         */
        for (i = 0; i < num_categories; i++)
        {
                /* see if we've gone too far already */
                if (call_cntr >= max_calls)
                        break;

                values[i] = SPI_getvalue(spi_tuple, spi_tupdesc, i+1);
        }

        /* build the tuple */
        tuple = BuildTupleFromCStrings(attinmeta, values);

        /* switch to appropriate context while storing the tuple */
        oldcontext = MemoryContextSwitchTo(per_query_ctx);
        tuplestore_puttuple(tupstore, tuple);
        MemoryContextSwitchTo(oldcontext);

        heap_freetuple(tuple);

        /* Clean up */
        for (i = 0; i < num_categories + 1; i++)
                if (values[i] != NULL)
                        pfree(values[i]);
        pfree(values);

    }

    /* let the caller know we're sending back a tuplestore */
    rsinfo->returnMode = SFRM_Materialize;
    rsinfo->setResult = tupstore;
    rsinfo->setDesc = tupdesc;

    /* release SPI related resources (and return to caller's context) */
    SPI_finish();

    return (Datum) 0;

}
