#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module.h"
#include "avl.h"


char* minusculas( char *t ){

	int i;

	for( i=0; t[i]!='\0'; i++ ){
		t[i] = tolower( t[i] );
	}

	return t;
}


void incrementaOcorrencias(VERBO verb, int num){
    
    if(verb != NULL){
        verb -> ocorrencias++;
    }
}


void insereVerbo( char *v , AVL lista ){

	VERBO new = newVerb(v, 1);
	VERBO encontrou;

	if(( encontrou = avl_find(lista, new)) != NULL ){
    	incrementaOcorrencias(encontrou, 1);
		freeVerbo(new);
	}
	else{
		avl_insert(lista, new);
	}

}


void freeVerbo( VERBO verb ){

    if(verb!=NULL) free(verb -> nome);
    free(verb);

}



VERBO newVerb(char *nome, int ocorrencias){

    VERBO novoVerbo = (VERBO) malloc(sizeof(struct listaVerbos));
    
    if(novoVerbo != NULL){
        novoVerbo -> nome = strdup(nome);
        novoVerbo -> ocorrencias = ocorrencias;
    }
    
    return novoVerbo;
}


int comparaVerbos (const void *a, const void *b, void *p){

	int res;

	res = strcmp( ( (VERBO) a)->nome, ( (VERBO) b)->nome );

	return res;
}


void freeVerbAVL(void *avl_item, void *avl_param){
    if(avl_item!=NULL) free(((VERBO) avl_item)->nome);
    free(avl_item);
}


void geraListaVerbos(AVL avl){

	VERBO verb;
	ITERADOR it = avl_new_it(avl);

	FILE * ficheiro = fopen("verbos.html", "w"); // w -> writing

	fprintf(ficheiro, "<!DOCTYPE html>\n");
    fprintf(ficheiro, "<html>\n");

    fprintf(ficheiro, "<head>\n");
    fprintf(ficheiro, "<title> Lista de Verbos e Suas Ocorrencias </title>\n"); // titulo
    fprintf(ficheiro, "</head>\n");

    fprintf(ficheiro, "<body>\n");

	fprintf(ficheiro, "<h1> Lista de Verbos e Suas Ocorrencias </h1>\n");

	fprintf(ficheiro, "<table style=\"width:50%%\">\n"); //tabela

	fprintf(ficheiro, "<tr style=\"text-align:center;\">\n"); //linha com titulos da tabela
	fprintf(ficheiro, "<th> Verbos </th>\n");
	fprintf(ficheiro, "<th> Ocorrencias </th>\n");
	fprintf(ficheiro, "</tr>\n"); 

	while ( (verb = (VERBO) avl_t_next(it)) != NULL ) {

		fprintf(ficheiro, "<tr style=\"text-align:center;\">\n"); //nova linha

		fprintf(ficheiro, "%s%s%s\n", "<td>", verb->nome, "</td>"); //fprintf(FILE *fp, "format", args)
        fprintf(ficheiro, "%s%d%s\n", "<td>", verb->ocorrencias, "</td>");
        
		fprintf(ficheiro, "</tr>\n"); 

	}

	fprintf(ficheiro, "</table>\n");

    fprintf(ficheiro, "</body>\n");

    fprintf(ficheiro, "</html>\n");

    fclose(ficheiro);

    avl_t_free(it);
}
