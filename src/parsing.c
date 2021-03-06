#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "parsing.h"

#include "postgres.h"
#include "executor/spi.h"
#include "access/heapam.h"
#include "fmgr.h"

#ifndef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

char *create_fuzzy_pred( const char *name,
                        const char *begin,const char *end,
                        const char *min,
                        const char *core1,const char *core2,
                        const char *max){


    const char *head;
    char *str;
    int len;

    head="INSERT INTO fuzzy.pg_fuzzypredicate(predicate,beginf,endf,minimum,first_core,second_core,maximum) VALUES(";

    len=strlen(head)+strlen(name)+strlen(begin)+strlen(end)+strlen(min)+strlen(core1)+strlen(core2)+strlen(max);

    //I do the len 2 times because all of the commas and brackets involved
    str= (char *)palloc(sizeof (char)*(len*2));

    snprintf(str,(len*2),"%s'%s','%s','%s','%s','%s','%s','%s')",head,name,begin,end,min,core1,core2,max);

    return str;
}

char *drop_fuzzy_pred(const char *name){

    const char *head;
    char *str;
    int len;

    head="DELETE FROM fuzzy.pg_fuzzypredicate WHERE predicate=";

    len=strlen(head)+strlen(name);

    str= (char *)palloc(sizeof (char)*(len*2));

    snprintf(str,(len*2),"%s'%s'",head,name);

    return str;
}

char *translate_fuzzy_preds(char *result,char *field,const char *value,char **min, char **fcore,char **score,char **max, int *is_fuzzy){
    char *fp_sqlf;
    int len,ret,proc;
    const char *head="SELECT predicate,beginf,endf,minimum,first_core,second_core,maximum "
                    "FROM fuzzy.pg_fuzzypredicate "
                    "WHERE predicate=";

    len=strlen(head)+strlen(value);

    fp_sqlf=(char *)palloc(sizeof(char)*(len*2));

    snprintf(fp_sqlf,(len*2),"%s'%s'",head,value);

    SPI_connect();

    ret=SPI_execute(fp_sqlf,true,1);

    proc=SPI_processed;

    if (proc==0){
      len=strlen(value)+strlen(field)+30;
			snprintf(result,(len*2),"%s=%s",field,value);
		  SPI_finish();
			*is_fuzzy=0;
		  pfree(fp_sqlf);
		  return result;
		}

    if (ret > 0 && SPI_tuptable != NULL){
      TupleDesc tupdesc = SPI_tuptable->tupdesc;
      SPITupleTable *tuptable = SPI_tuptable;
      HeapTuple tuple = tuptable->vals[0];

      *min=SPI_getvalue(tuple,tupdesc,4);
      *fcore=SPI_getvalue(tuple,tupdesc,5);
      *score=SPI_getvalue(tuple,tupdesc,6);
      *max=SPI_getvalue(tuple,tupdesc,7);

      len=strlen(value)+strlen(field)+30;

      if (strcmp(*min,"INFINIT")==0){
          snprintf(result,(len*2)," %s < %s",field,*max);
      }else if(strcmp(*max,"INFINIT")==0){
          snprintf(result,(len*2)," %s > %s",field, *min);
      }else{
          snprintf(result,(len*2)," %s > %s AND %s < %s",field,*min,field,*max);
      }
    }

		*is_fuzzy=1;
    SPI_finish();
    pfree(fp_sqlf);
    return result;
}
