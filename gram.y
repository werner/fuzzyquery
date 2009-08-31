%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    #include "postgres.h"
    #include "parsing.h"

    #define YYDEBUG 1
    #define QUERY_LENGTH 4
    #define YYPARSE_PARAM result  /* need this to pass a pointer (void *) to yyparse */

    int real_length;
    char *field;
    char *fuzzy_query[QUERY_LENGTH];

%}

%union {
    int	integer;
    char *text;
}

%token CREATE FUZZY PREDICATE ON AS COMMA DOTDOT LEFTP RIGHTP INFINIT
        DROP EQUAL SELECT WHERE FROM AND OR ORDER BY ASC DESC WITH CALIBRATION
%token <text> PARAMETER 
%type <text> Param Param_select Param_from List_where List_order SelectStmt

%%


query:  /* empty string */
      |  query command
        {
          int i;

          *((void **)result) = fuzzy_query[real_length-1];

          for (i=0;i<real_length;i++)
            pfree(fuzzy_query[i]);
        }
;

command: '\n'
            | CreateFuzzyPredStmt { real_length=1; }
            | DropFuzzyPredStmt { real_length=1; }
            | SelectStmt
            | error '\n'  { yyerrok;}
;

CreateFuzzyPredStmt:
            CREATE FUZZY PREDICATE Param ON Param DOTDOT Param AS LEFTP Param COMMA Param COMMA Param COMMA Param RIGHTP
            {
                    fuzzy_query[0]=create_fuzzy_pred($4,$6,$8,$11,$13,$15,$17);
            }
            |
            CREATE FUZZY PREDICATE Param ON Param DOTDOT Param AS LEFTP INFINIT COMMA INFINIT COMMA Param COMMA Param RIGHTP
            {
                    fuzzy_query[0]=create_fuzzy_pred($4,$6,$8,"INFINIT","INFINIT",$15,$17);
            }
            |
            CREATE FUZZY PREDICATE Param ON Param DOTDOT Param AS LEFTP Param COMMA Param COMMA INFINIT COMMA INFINIT RIGHTP
            {
                    fuzzy_query[0]=create_fuzzy_pred($4,$6,$8,$11,$13,"INFINIT","INFINIT");
            }
;

DropFuzzyPredStmt:
            DROP FUZZY PREDICATE Param
            {
                    fuzzy_query[0]=drop_fuzzy_pred($4);
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

    WITH CALIBRATION
*/

/* Missing pretty much everything, it parses the basic select */

SelectStmt:
            SELECT Param_select FROM Param_from
            {
                fuzzy_query[0]=(char *)palloc(sizeof(char)*(strlen($2)+strlen($4)+20));
                snprintf(fuzzy_query[0],(strlen($2)+strlen($4)+20),"SELECT %s FROM %s",$2,$4);
                $$=fuzzy_query[0];
                real_length=1;
            }
            |
            SelectStmt WHERE List_where
            {
                fuzzy_query[1]=(char *)palloc(sizeof(char)*(strlen($1)+strlen($3)+20));
                snprintf(fuzzy_query[1],(strlen($1)+strlen($3)+20),"%s WHERE %s",$1,$3);
                $$=fuzzy_query[1];
                real_length=2;
            }
            |
            SelectStmt ORDER BY List_order
            {
                fuzzy_query[2]=(char *)palloc(sizeof(char)*(strlen($1)+strlen($4)+20));
                snprintf(fuzzy_query[2],(strlen($1)+strlen($4)+20),"%s ORDER BY %s",$1,$4);
                $$=fuzzy_query[2];
                real_length=3;
            }
            |
            SelectStmt WITH CALIBRATION Param
            {
                fuzzy_query[3]=(char *)palloc(sizeof(char)*(strlen($1)+strlen($4)+20));
                snprintf(fuzzy_query[3],(strlen($1)+strlen($4)+20),"%s WITH CALIBRATION %s",$1,$4);
                $$=fuzzy_query[3];
                real_length=4;
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
;


List_where:
            Param {
                $$=$1;
                field=$1;
            }
            | LEFTP Param {
                strcat($$," (");
                strcat($$,$2);
                field=$2;
            }
            | List_where EQUAL Param {
            	int len;
                char *str_result;
                len=strlen(field)+strlen($3)+15;//15 is the length of "%s > %f AND %s < %f"
                str_result=(char *)palloc(sizeof(char)*(len*2));
                $$=translate_fuzzy_preds(str_result,field,$3);
                pfree(str_result);
            }
            | List_where AND Param {
                strcat($$," AND ");
                strcat($$,$3);
                field=$3;
            }
            | List_where RIGHTP AND Param {
                strcat($$,") AND ");
                strcat($$,$4);
                field=$4;
            }
            | List_where OR Param {
                strcat($$," OR ");
                strcat($$,$3);
                field=$3;
            }
            | List_where RIGHTP OR Param {
                strcat($$,") OR ");
                strcat($$,$4);
                field=$4;
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

%%
void yyerror (char *s) {elog (ERROR, "%s\n", s);}

#include "scan.c"