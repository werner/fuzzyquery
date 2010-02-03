%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    #include "postgres.h"
    #include "parsing.h"

    #define YYDEBUG 1
    #define QUERY_LENGTH 5
    #define YYPARSE_PARAM result  /* need this to pass a pointer (void *) to yyparse */
	#define IS_FLOAT(x) (strcmp(x,"0")==0 || atof(x)) ? true : false

    int real_length=0;
    char *field;
    char *fuzzy_query[QUERY_LENGTH];
	#define DDL_FP_CLAUSE 0
		
	//To know if it is an AND or an OR in the query
	#define LEAST 1
	#define GREATEST 2
	int fop;

	enum sql_type {SELECT_CLAUSE,FROM_CLAUSE,WHERE_CLAUSE,ORDER_BY_CLAUSE,CALIBRATION_CLAUSE};

	char *sub_sqlf_filters[1024];
	char *args_membdg[1024];
	
	int count_membdg=0;
	int filter_times=0;
	char *select_items;

    typedef struct Membdg_values {
        char *min;
        char *first_core;
        char *second_core;
        char *max;
    } Membdg_values;

    Membdg_values membdg_values;

	int *is_fuzzy;

	int ScanKeyword(const char *keyword);

	char  *sql;

%}

%union {
    int	integer;
    char *text;
}

%token CREATE FUZZY PREDICATE ON AS COMMA DOTDOT LEFTP RIGHTP INFINIT INNER JOIN LEFT RIGHT
        DROP EQUAL SELECT WHERE FROM AND OR ORDER BY ASC DESC WITH CALIBRATION
%token <text> PARAMETER 
%type <text> Param Param_select Param_from List_where List_order SelectStmt Memb_degree

%%

query:  /* empty string */
      |  query command
        {
			if (real_length>=0){
				int   i=0;
				int   j=0;
				int   len;
				//This variable is used to add the membership degree function
				//in the where clause 
				char	*calib_where;

				len=0;
				for (i=0;i<real_length;i++)
					len+=strlen(fuzzy_query[i]);
				len+=20;
				if(filter_times==1 || real_length==1 || count_membdg==1){
				
					sql=(char *)palloc(sizeof(char *)*len);
					strcpy(sql,"");

					for (i=0;i<real_length;i++){
						if (i==FROM_CLAUSE){
							strcat(sql,args_membdg[0]);
							strcat(sql," as membdg");
						}

						strcat(sql,fuzzy_query[i]);

						if (i==WHERE_CLAUSE)
							strcat(sql," ORDER BY membdg");
					}
				}else{

					for(i=0;i<filter_times;i++){
						len+=strlen(sub_sqlf_filters[i]);
						len+=150;
					}

					for(i=0;i<count_membdg;i++)
						len+=strlen(args_membdg[i]);
					
					len+=strlen(fuzzy_query[SELECT_CLAUSE])+strlen(select_items);

					sql=(char *)palloc(sizeof(char *)*len);
					strcpy(sql,"");

					len=0;
					for (i=0;i<real_length;i++){
						if (i==FROM_CLAUSE){

							for (j=0;j<count_membdg;j++)
								len+=strlen(args_membdg[j]);

							calib_where=(char *)palloc(sizeof(char *)*len);
							strcpy(calib_where,"");
							
								strcpy(calib_where,"fuzzy.membdg_total(");

								for (j=0;j<count_membdg;j++){
									strcat(calib_where,args_membdg[j]);
									if (j<count_membdg-1)
										strcat(calib_where,"||");							
								}
								strcat(calib_where,") ");
							
							strcat(sql,calib_where);
							strcat(sql," as membdg ");

						}

						//This is to prevent adding the WITH CALIBRATION at the end of the query
						if (i!=CALIBRATION_CLAUSE)
						strcat(sql,fuzzy_query[i]);

						if (i==WHERE_CLAUSE){
							if (real_length==5){
								strcat(sql," AND ");
								strcat(sql,calib_where);
								strcat(sql,"=");
								strcat(sql,fuzzy_query[CALIBRATION_CLAUSE]);
							}
							strcat(sql," ORDER BY membdg");
						}

					}
					pfree(calib_where);

				}

				//Cleaning
				if (real_length>1)
					pfree(select_items);
				for (i=0;i<real_length;i++){
					strcpy(fuzzy_query[i],"");            
					pfree(fuzzy_query[i]);
				}
				for (i=0;i<count_membdg;i++){
					strcpy(args_membdg[i],"");
					pfree(args_membdg[i]);
				}
				for (i=0;i<filter_times;i++){
					strcpy(sub_sqlf_filters[i],"");						
					pfree(sub_sqlf_filters[i]);
				}
				count_membdg=0;
				filter_times=0;
				real_length=0;
			}
			*((void **)result) = sql;

			pfree(sql);
			
        }
;

command: '\n'
        | CreateFuzzyPredStmt { real_length=1; }
        | DropFuzzyPredStmt { real_length=1; }
        | SelectStmt 
		| Memb_degree { 
			int len;
			real_length=-1;

			sql=(char *)palloc(sizeof(double));
			strcpy(sql,"");
			sql=$1; 
		}
        | error '\n'  { yyerrok;}
;

CreateFuzzyPredStmt:
        CREATE FUZZY PREDICATE Param ON Param DOTDOT Param AS LEFTP Param COMMA Param COMMA Param COMMA Param RIGHTP
        {
            fuzzy_query[DDL_FP_CLAUSE]=create_fuzzy_pred($4,$6,$8,$11,$13,$15,$17);
        }
        |
		CREATE FUZZY PREDICATE Param ON Param DOTDOT Param AS LEFTP INFINIT COMMA INFINIT COMMA Param COMMA Param RIGHTP
		{
			fuzzy_query[DDL_FP_CLAUSE]=create_fuzzy_pred($4,$6,$8,"INFINIT","INFINIT",$15,$17);
		}
		|
		CREATE FUZZY PREDICATE Param ON Param DOTDOT Param AS LEFTP Param COMMA Param COMMA INFINIT COMMA INFINIT RIGHTP
		{
			fuzzy_query[DDL_FP_CLAUSE]=create_fuzzy_pred($4,$6,$8,$11,$13,"INFINIT","INFINIT");
		}
;

DropFuzzyPredStmt:
		DROP FUZZY PREDICATE Param
		{
			fuzzy_query[DDL_FP_CLAUSE]=drop_fuzzy_pred($4);
		}
;

/**************SELECT STATEMENT**********************************/
/*

[ WITH [ RECURSIVE ] with_query [, ...] ]
SELECT [ ALL | DISTINCT [ ON ( expression [, ...] ) ] ]
    * | expression [ [ AS ] output_name ] [, ...]
    [ FROM from_item [, ...] ]
    [ WHERE condition ]
    [ GROUP BY expression [, ...] ]
    [ HAVING condition [, ...] ]
    [ WINDOW window_name AS ( window_definition ) [, ...] ]
    [ { UNION | INTERSECT | EXCEPT } [ ALL ] select ]
    [ ORDER BY expression [ ASC | DESC | USING operator ] [ NULLS { FIRST | LAST } ] [, ...] ]
    [ LIMIT { count | ALL } ]
    [ OFFSET start [ ROW | ROWS ] ]
    [ FETCH { FIRST | NEXT } [ count ] { ROW | ROWS } ONLY ]
    [ FOR { UPDATE | SHARE } [ OF table_name [, ...] ] [ NOWAIT ] [...] ]

where from_item can be one of:

    [ ONLY ] table_name [ * ] [ [ AS ] alias [ ( column_alias [, ...] ) ] ]
    ( select ) [ AS ] alias [ ( column_alias [, ...] ) ]
    with_query_name [ [ AS ] alias [ ( column_alias [, ...] ) ] ]
    function_name ( [ argument [, ...] ] ) [ AS ] alias [ ( column_alias [, ...] | column_definition [, ...] ) ]
    function_name ( [ argument [, ...] ] ) AS ( column_definition [, ...] )
    from_item [ NATURAL ] join_type from_item [ ON join_condition | USING ( join_column [, ...] ) ]

and with_query is:

    with_query_name [ ( column_name [, ...] ) ] AS ( select )

*/

/* Missing pretty much everything, it parses the basic select */

SelectStmt:
            SELECT Param_select FROM Param_from
            {
                int len;
                len=strlen($2)+10;
                fuzzy_query[SELECT_CLAUSE]=(char *)palloc(sizeof(char *)*len);
				select_items=(char *)palloc(sizeof(char *)*len);
				snprintf(select_items,len,"%s",$2);

                len=strlen($4)+10;
                fuzzy_query[FROM_CLAUSE]=(char *)palloc(sizeof(char *)*len);
							
                snprintf(fuzzy_query[SELECT_CLAUSE],(strlen($2)+40)," SELECT %s,",$2);
                snprintf(fuzzy_query[FROM_CLAUSE],(strlen($4)+60)," FROM %s ",$4);

                real_length=2;
            }
            |
            SelectStmt WHERE List_where
            {
				int i,len=0;
				
				for(i=0;i<filter_times;i++)
					len+=strlen(sub_sqlf_filters[i]);

				len+=10;
                fuzzy_query[WHERE_CLAUSE]=(char *)palloc(sizeof(char *)+len);
                strcpy(fuzzy_query[WHERE_CLAUSE],"WHERE ");

				for(i=0;i<filter_times;i++)
					strcat(fuzzy_query[WHERE_CLAUSE],sub_sqlf_filters[i]);
							
                real_length=3;
            }
            |
            SelectStmt ORDER BY List_order
            {
                int len;
                len=strlen($4)+2;
                fuzzy_query[ORDER_BY_CLAUSE]=(char *)palloc(sizeof(char *)*len);
                snprintf(fuzzy_query[ORDER_BY_CLAUSE],(strlen($4)+20),", %s",$4);
                real_length=4;
            }
            |
            SelectStmt WITH CALIBRATION Param
            {
                int len;
                len=strlen($4)+2;
                fuzzy_query[CALIBRATION_CLAUSE]=(char *)palloc(sizeof(char *)*len);
                snprintf(fuzzy_query[CALIBRATION_CLAUSE],len,"%s",$4);
                real_length=5;
            }
;

Param:	PARAMETER { $$ = $1; };

Param_select:
            Param { $$ = $1; }
            | Param_select COMMA Param {
                strcat($$,", ");
                strcat($$,$3);
            }
            | Param_select AS Param {
                strcat($$," AS ");
                strcat($$,$3);
            }
            | Param_select Param {
                strcat($$," ");
                strcat($$,$2);
            }
;

Param_from:
		Param { $$ = $1;}
		| Param_from COMMA Param {
			strcat($$,", ");
			strcat($$,$3);
		}
		| Param_from AS Param {
			strcat($$," AS ");
			strcat($$,$3);
		}
		| Param_from Param {
			strcat($$," ");
			strcat($$,$2);
		}
		| Param_from INNER JOIN Param {
			strcat($$," INNER JOIN ");
			strcat($$,$4);
		}
		| Param_from LEFT JOIN Param {
			strcat($$," LEFT JOIN ");
			strcat($$,$4);
		}
		| Param_from RIGHT JOIN Param {
			strcat($$," RIGHT JOIN ");
			strcat($$,$4);
		}
		| Param_from ON Param EQUAL Param{
			strcat($$," ON ");
			strcat($$,$3);
			strcat($$," = ");
			strcat($$,$5);
		}
;

List_where:
		Param {
			$$=$1;
			field=(char *)palloc(sizeof(char *)*strlen($1));
			strcpy(field,$1);
		}
		| LEFTP Param {
			field=(char *)palloc(sizeof(char *)*strlen($2));
			strcpy(field,$2);

			args_membdg[count_membdg]=(char *)palloc(sizeof(char *)+5);
			snprintf(args_membdg[count_membdg],5,"'('");
			count_membdg++;
			
			sub_sqlf_filters[filter_times]=(char *)palloc(sizeof(char *)+2);
			snprintf(sub_sqlf_filters[filter_times],2,"(");
			filter_times++;
		}
		| List_where EQUAL Param {
			int len;
			char *str_filter;
			char *str_result;
			
			//I use str_filter to save the translated filter from sqlf to sql
			len=strlen(field)+strlen($3)+15; //15 is the length of "%s > %f AND %s < %f"
			str_result=(char *)palloc(sizeof(char *)*(len));

			is_fuzzy=0;
			str_filter=(char *)palloc(sizeof(char *)*(len));
			str_filter=translate_fuzzy_preds(str_result,field,$3,&membdg_values.min,&membdg_values.first_core,
			&membdg_values.second_core,&membdg_values.max,&is_fuzzy);

			if (is_fuzzy==1){
								
				//This is used to get the membership degree
				len=strlen(field)+100;
				args_membdg[count_membdg]=(char *)palloc(sizeof(char *)*len);
				snprintf(args_membdg[count_membdg],len,
						"fuzzy.membdg(%s,'%s'::text,'%s'::text,'%s'::text,'%s'::text)",field,
						membdg_values.min,membdg_values.first_core,membdg_values.second_core,membdg_values.max);
			
				count_membdg++;
			}else if (is_fuzzy==0){
				args_membdg[count_membdg]=(char *)palloc(sizeof(char *)+5);
				snprintf(args_membdg[count_membdg],5,"'nf'");
				count_membdg++;
			}
			
			len=strlen(str_filter);

			sub_sqlf_filters[filter_times]=(char *)palloc(sizeof(char *)*len*2);

			snprintf(sub_sqlf_filters[filter_times],(len*2),"%s",str_filter);

			filter_times++;
			pfree(str_result);
		}
		| List_where AND Param {

			//I add a comma to args_membdg to separate the memberships degrees
			args_membdg[count_membdg]=(char *)palloc(sizeof(char *)+10);
			snprintf(args_membdg[count_membdg],10,"' AND '");
			count_membdg++;

			//This I add an AND to the sub_sqlf_filters array
			sub_sqlf_filters[filter_times]=(char *)palloc(sizeof(char *)+10);
			snprintf(sub_sqlf_filters[filter_times],10," AND ");
			filter_times++;
			
			//Add a field name to field variable
			field=(char *)palloc(sizeof(char *)*strlen($3));
			strcpy(field,$3);
		}
		| List_where RIGHTP AND Param {

			args_membdg[count_membdg]=(char *)palloc(sizeof(char *)+5);
			snprintf(args_membdg[count_membdg],5,"')'");
			count_membdg++;

			args_membdg[count_membdg]=(char *)palloc(sizeof(char *)+10);
			snprintf(args_membdg[count_membdg],10,"' AND '");
			count_membdg++;

			sub_sqlf_filters[filter_times]=(char *)palloc(sizeof(char *)+10);
			snprintf(sub_sqlf_filters[filter_times],10,") AND ");
			filter_times++;

			field=(char *)palloc(sizeof(char *)*strlen($4));
			strcpy(field,$4);
		}
		| List_where OR Param {

			args_membdg[count_membdg]=(char *)palloc(sizeof(char *)+10);
			snprintf(args_membdg[count_membdg],10,"' OR '");
			count_membdg++;

			sub_sqlf_filters[filter_times]=(char *)palloc(sizeof(char *)+10);
			snprintf(sub_sqlf_filters[filter_times],10," OR ");
			filter_times++;

			field=(char *)palloc(sizeof(char *)*strlen($3));
			strcpy(field,$3);
		}
		| List_where RIGHTP OR Param {

			//fop=GREATEST;
			args_membdg[count_membdg]=(char *)palloc(sizeof(char *)+5);
			snprintf(args_membdg[count_membdg],5,"')'");
			count_membdg++;
		
			args_membdg[count_membdg]=(char *)palloc(sizeof(char *)+10);
			snprintf(args_membdg[count_membdg],10,"' OR '");
			count_membdg++;

			sub_sqlf_filters[filter_times]=(char *)palloc(sizeof(char *)+10);
			snprintf(sub_sqlf_filters[filter_times],6,") OR ");
			filter_times++;

			field=(char *)palloc(sizeof(char *)*strlen($4));
			strcpy(field,$4);
		}
		| List_where RIGHTP {
		
			args_membdg[count_membdg]=(char *)palloc(sizeof(char *)+5);
			snprintf(args_membdg[count_membdg],5,"')'");
			count_membdg++;
		
			sub_sqlf_filters[filter_times]=(char *)palloc(sizeof(char *)+2);
			snprintf(sub_sqlf_filters[filter_times],2,")");
			filter_times++;
		}
			
;

List_order:
	Param { $$=$1; }
	| List_order COMMA Param {
		strcat($$,", ");
		strcat($$,$3);
	}
	| List_order ASC { 
		strcat($$," ASC");
		strcat($$,$1);
	}
	| List_order DESC { 
		strcat($$," DESC");
		strcat($$,$1);
	}
;

Memb_degree:
	Param { $$=$1; }
	| LEFTP Param { $$=$2; }
	| Memb_degree AND Param {
		float pnum;
		float snum;
		if (IS_FLOAT($1) && IS_FLOAT($3)){
			pnum=atof($1);
			snum=atof($3);
			if (pnum<snum) 
				$$=$1;
			else 
				$$=$3;
		}
	}
	| Memb_degree RIGHTP AND Param { 
		float pnum;
		float snum;
		if (IS_FLOAT($1) && IS_FLOAT($4)){
			pnum=atof($1);
			snum=atof($4);
			if (pnum<snum) 
				$$=$1;
			else 
				$$=$4;	
		}
	}
	| Memb_degree OR Param { 
		float pnum;
		float snum;
		if (IS_FLOAT($1) && IS_FLOAT($3)){
			pnum=atof($1);
			snum=atof($3);
			if (pnum>snum) 
				$$=$1;
			else 
				$$=$3;	
		}
	}
	| Memb_degree RIGHTP OR Param { 
		float pnum;
		float snum;
		if (IS_FLOAT($1) && IS_FLOAT($4)){
			pnum=atof($1);
			snum=atof($4);
			if (pnum>snum) 
				$$=$1;
			else 
				$$=$4;
		}				
	}
	| Memb_degree RIGHTP { $$=$1; }
;
	

%%
void yyerror (char *s) {elog (ERROR, "%s\n", s);}

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
			{"CALIBRATION",CALIBRATION},
			{"INNER",INNER},
			{"JOIN",JOIN},
			{"LEFT",LEFT},
			{"RIGHT",RIGHT}
    };

    len=sizeof(keyfuzzywords)/sizeof(Keyword);

    for(i=0;i<len;i++){
            if (strcmp(keyfuzzywords[i].name,word)==0)
                    return keyfuzzywords[i].value;
    }

    return 0;
}

#include "scan.c"
