#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "parsing.h"
#include "gram.h"

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

    head="INSERT INTO fuzzy.pg_fuzzypredicate VALUES(";

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

char *translate_fuzzy_preds(char *result,char *field,const char *value,double *min, double *fcore,double *score,double *max){
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

    if (proc==0)
        elog(ERROR,"there's a query trouble, maybe there's no data to show");

    if (ret > 0 && SPI_tuptable != NULL){
      TupleDesc tupdesc = SPI_tuptable->tupdesc;
      SPITupleTable *tuptable = SPI_tuptable;
      HeapTuple tuple = tuptable->vals[0];

      *fcore=atof(SPI_getvalue(tuple,tupdesc,5));
      *score=atof(SPI_getvalue(tuple,tupdesc,6));

      len=strlen(value)+strlen(field)+15;

      if (strcmp(SPI_getvalue(tuple,tupdesc,4),"INFINIT")==0){
          *max=atof(SPI_getvalue(tuple,tupdesc,7));
          snprintf(result,(len*2)," < %f",*max);
      }else if(strcmp(SPI_getvalue(tuple,tupdesc,7),"INFINIT")==0){
          *min=atof(SPI_getvalue(tuple,tupdesc,4));
          snprintf(result,(len*2)," > %f",*min);
      }else{
          *min=atof(SPI_getvalue(tuple,tupdesc,4));
          *max=atof(SPI_getvalue(tuple,tupdesc,7));

          snprintf(result,(len*2)," > %f AND %s < %f",*min,field,*max);
      }
    }

    SPI_finish();
    pfree(fp_sqlf);
    return result;
}

int ScanKeyword(const char *word){
        int i,len;

    Keyword keyfuzzywords[] = {
                    {"AND",AND},
                    {"AS",AS},
                    {"CREATE",CREATE},
                    {"DROP",DROP},
                    {"FROM",FROM},
                    {"FUZZY",FUZZY},
                    {"INFINIT",INFINIT},
                    {"ON",ON},
                    {"OR",OR},
                    {"PREDICATE",PREDICATE},
                    {"SELECT",SELECT},
                    {"WHERE",WHERE},
                    {"ORDER",ORDER},
                    {"BY",BY},
                    {"ASC",ASC},
                    {"DESC",DESC},
                    {"WITH",WITH},
                    {"CALIBRATION",CALIBRATION}
    };

    len=sizeof(keyfuzzywords)/sizeof(Keyword);

    for(i=0;i<len;i++){
            if (strcmp(keyfuzzywords[i].name,word)==0)
                    return keyfuzzywords[i].value;
    }

    return 0;
}
