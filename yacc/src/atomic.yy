%{
	#include "auxiliarGramatica.h"

	int lineno = 1;

%}

%union{
	Variavel variavel;
	int valor;
    char *str;
    GString * codigo;
}

%token <str> START AT VOID ATOM RETURN LEQ GEQ DIF EQU AND OR ID STRING IF ELSE WHILE READ PRINT
%token <valor> NUM
%type <variavel> Var
%type <str> Declar Inst Condicional Ciclica Atribuicao Invocacao Leitura Escrita Condicao Exp Termo Fator Return
%type <codigo> Funcoes Funcao Start Body ListaDeclars LinhaDeclar Declars Insts

%%
Atomic			: Funcoes Start 				{ printf("%s", trataInicioPrograma($1, $2) -> str); }
				;

Funcoes			: Funcoes Funcao				{ $$ = trataFuncoes($1, $2); }
				|								{ $$ = inicializaFuncoes(); }
				;

Funcao			: VOID ID 						{ trataFuncaoVoid($2); }
							'('')' '{' Body '}'	{ $$ = trataCorpoFuncaoVoid($2, $7); }
				| ATOM ID 						{ trataFuncaoComRetorno($2); }
							'('')' '{' Body '}'	{ $$ = trataCorpoFuncaoComRetorno($2, $7); }
				;

Start 			: START 						{ trataFuncaoStart(); }
							'('')' '{' Body '}'	{ $$ = trataCorpoFuncaoStart($6); }

Body			: ListaDeclars Insts Return 	{ $$ = trataCorpo($1, $2, $3); }
				;
	  		
ListaDeclars 	: ListaDeclars LinhaDeclar 		{ $$ = trataListaDeclaracoes($1, $2); }
				| 								{ $$ = inicializaListaDeclaracoes(); }
				;

LinhaDeclar 	: ATOM Declars ';'				{ $$ = trataLinhaDeclaracoes($2); }
				;

Declars 		: Declars ',' Declar  			{ $$ = trataDeclaracoes($1, $3); }
				| Declar 						{ $$ = trataDeclaracao($1); }
				;

Declar 			: ID    						{ $$ = trataDeclaracaoVariavel($1); }
				| ID AT NUM 					{ $$ = trataDeclaracaoAtribuicao($1, $3); }
				| ID '[' NUM ']' 				{ $$ = trataDeclaracaoArray($1, $3); }
				| ID '[' NUM ']' '[' NUM ']'	{ $$ = trataDeclaracaoMatriz($1, $3, $6); }
				;


Insts 			: Insts Inst 					{ $$ = trataInstrucoes($1, $2); }
       			|			 					{ $$ = inicializaInstrucoes(); }
       			;

Inst 			: Condicional 					{ $$ = trataInstrucaoCondicional($1); }
      			| Ciclica	 					{ $$ = trataInstrucaoCiclica($1); }
      			| Atribuicao	 				{ $$ = trataInstrucaoAtribuicao($1); }
      			| Invocacao 					{ $$ = trataInstrucaoInvocacao($1); }
      			| Leitura 						{ $$ = trataInstrucaoLeitura($1); }
      			| Escrita 						{ $$ = trataInstrucaoEscrita($1); }
      			;

Condicional 	: IF '(' Condicao ')' '{' Insts '}' 					{ $$ = trataIf($3, $6); }
		 		| IF '(' Condicao ')' '{' Insts '}' ELSE '{' Insts '}' 	{ $$ = trataIfElse($3, $6, $10); }
		 		;


Ciclica 		: WHILE '(' Condicao ')' '{' Insts '}'					 { $$ = trataWhile($3, $6); }
				;

Atribuicao		: Var AT Exp ';'				{ $$ = trataAtribuicao($1, $3); }
				;


Invocacao 		: ID '(' ')' ';' 				{ $$ = trataInvocacao($1); }
				;

Leitura 		: Var AT READ '(' ')' ';'		{ $$ = trataLeitura($1); }
				;

Escrita 		: PRINT '(' Exp ')' ';'			{ $$ = trataEscritaExpressao($3); }
        		| PRINT '(' STRING ')' ';'		{ $$ = trataEscritaString($3); }
        		;

Condicao 		: Condicao AND Condicao 		{ $$ = trataCondicaoAnd($1, $3); }
				| Condicao OR Condicao 			{ $$ = trataCondicaoOr($1, $3); }
				| '(' Condicao ')'				{ $$ = trataCondicaoParenteses($2); }
				| '!' Condicao 					{ $$ = trataCondicaoNot($2); }
				| Exp '<' Exp 					{ $$ = trataCondicaoMenor($1, $3); }
				| Exp '>' Exp 					{ $$ = trataCondicaoMaior($1, $3); }
				| Exp LEQ Exp 					{ $$ = trataCondicaoMenorIgual($1, $3); }
				| Exp GEQ Exp 					{ $$ = trataCondicaoMaiorIgual($1, $3); }
				| Exp DIF Exp 					{ $$ = trataCondicaoDif($1, $3); }
				| Exp EQU Exp 					{ $$ = trataCondicaoIgual($1, $3); }
				| Exp 							{ $$ = trataCondicaoExp($1); }
				;

Exp 			: Termo 						{ $$ = trataExpTermo($1); }
     			| Exp '+' Termo 				{ $$ = trataExpSoma($1, $3); }
     			| Exp '-' Termo 				{ $$ = trataExpSub($1, $3); }
     			| '(' Exp ')'					{ $$ = trataExpParenteses($2); }
     			;

Termo 			: Fator 						{ $$ = trataTermoFator($1); }
				| Termo '*' Fator 				{ $$ = trataTermoMult($1, $3); }
				| Termo '/' Fator 				{ $$ = trataTermoDiv($1, $3); }
				| Termo '%' Fator 				{ $$ = trataTermoMod($1, $3); }
				| '(' Termo ')' 				{ $$ = trataTermoParenteses($2); }
				;

Fator 			: NUM			 				{ $$ = trataFatorNum($1); }
				| Var			 				{ $$ = trataFatorVar($1); }
				| ID '(' ')'			 		{ $$ = trataFatorInvocacao($1); }
				| READ '(' ')'					{ $$ = trataFatorLeitura(); }
				;

Var 			: ID 							{ trataIdentificadorVariavel(&$$, $1); }
				| ID '[' Exp ']' 				{ trataArray(&$$, $1, $3); }
				| ID '[' Exp ']' '[' Exp ']'	{ trataMatriz(&$$, $1, $3, $6); }

Return 			: RETURN Exp ';'				{ $$ = trataReturn($2); }
				| 							    { $$ = trataNaoReturn(); }
				;

%%

#include "lex.yy.c"

void yyerror(char *s) { 
  fprintf(stderr,"ERRO (linha %d):antes de '%s'\n\n%s",yylineno, yytext,s);
}

int main(){
	funcaoAtual = NULL;
	nrIf = 0;
	nrCiclo = 0;
	mapaFunVars = novo_mapa_fun_vars();
    yyparse();
    return 0;
}

