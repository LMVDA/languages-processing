%{

	#include <stdio.h>
	#include <string.h>
	#include <ctype.h>
    #include "avl.h"
    #include "module.h"

	AVL lista;
	char* verbo;

%}

modalVerb 	?i:(can|could|may|might|must|shall|will|should|would)
pronoun 	?i:(i|you|he|she|it|we|you|they)
question	?i:("do"|does|did)

%x FRASE
%x GUARDAR

%% 

{modalVerb}						{	BEGIN FRASE; }

\ to 							{	BEGIN GUARDAR; }

{question}\ {pronoun}			{ 	BEGIN GUARDAR; }

<FRASE>\ {pronoun}			 	{	BEGIN GUARDAR; }

<FRASE>\ "not"					{	BEGIN GUARDAR; }

<FRASE>\ [a-zA-Z]+				{	verbo = strdup(yytext);
									verbo[strlen(verbo)] = '\0';
									minusculas(verbo);
									insereVerbo(verbo, lista);

	            			 		BEGIN INITIAL; }

<GUARDAR>\ [a-zA-Z]+			{ 	verbo = strdup(yytext);
									verbo[strlen(verbo)] = '\0';
									minusculas(verbo);
									insereVerbo(verbo, lista);

	            			 		BEGIN INITIAL; }

.|\n    						{;}

%%

int yywrap(){

    return 1;
}

int main(int argc, char **argv){

	lista = avl_create(comparaVerbos, NULL, NULL); //creates an AVL tree , needs to know how to compare two nodes in the tree

	if(argc>=2){
        yyin=fopen(argv[1], "r");
    }
    yylex();

	geraListaVerbos(lista);

	return 0;
}