
%option nodefault
%option noinput
%option nounput
%option noyywrap

n      		[0-9]+
integer		[+-]?{n}
real   		[+-]?({n}\.{n})
word			[A-Za-z\_\-\?\+\*\.]+
param			({integer}|{real}|{word})

%%

\(				{return LEFTP;}
\)				{return RIGHTP;}
\,				{return COMMA;}
\.\.			{return DOTDOT;}
\=				{return EQUAL;}
{param}		{
                    int token;
                    /* Is it a keyword? */
                    token = ScanKeyword(yytext);
                    if (token != 0)
                        return token;

                    yylval.text=(char *)palloc(strlen(yytext)*sizeof(char *));
                    strcpy(yylval.text,yytext);
                    return PARAMETER;
              }
[ \n]			/* discard spaces */
.         {return yytext[0];} /* alert parser of the garbage */
%%
