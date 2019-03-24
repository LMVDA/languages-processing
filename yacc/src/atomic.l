%{
	#include <string.h>
%}

%option noyywrap
%option yylineno

%%

[-*/;,\[\]=><!+\(\)\{\}%]	{ return yytext[0]; }
[-]?[0-9]+					{
								yylval.valor = atoi(yytext);
								return NUM;
							}

(?i:void)					{ return VOID; }
(?i:start)					{ return START; }
(?i:if)						{ return IF; }
(?i:else)					{ return ELSE; }
(?i:while)					{ return WHILE; }
(?i:atom)					{ return ATOM; }
(?i:read)					{ return READ; }
(?i:print)					{ return PRINT; }
(?i:return)					{ return RETURN; }
\<-							{ return AT; }
\<=							{ return LEQ; }
\>=							{ return GEQ; }
!=							{ return DIF; }
==							{ return EQU; }
&&							{ return AND; }
\|\|						{ return OR; }

[_a-zA-Z][_A-Za-zs0-9]*		{
								yylval.str = strdup(yytext);
								return ID;
							}

\"[^"]*\"					{
								yylval.str = strdup(yytext);
								return STRING;
							}

\/\/[^\n]*             		{ }
([ ]|\n|\t|\r)				{ }
.			    			{ fprintf(stderr, "Erro char invalido '%c' com codigo ASCII %d na linha %d\n",yytext[0],(int) yytext[0],yylineno); }

%%