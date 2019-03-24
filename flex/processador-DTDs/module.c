#include "module.h"

gint compararChave ( gconstpointer a, gconstpointer b, gpointer user_data){
	const char * ca = (char*) a;
	const char * cb = (char*) b;

	return strcmp(ca,cb);
}

void freeElemento(gpointer elemento) {
	Elemento * e = (Elemento*) elemento;

	free( e->nome );
	if (e->dependencias != NULL) g_sequence_free( e->dependencias );
	if (e->atributos != NULL) g_sequence_free( e->atributos );

	free(e);
}

void freeChave (gpointer chave){
	free( chave );
}

Elemento * inicializaElemento(char * nome) {
	Elemento * elemento = (Elemento*) malloc(sizeof(Elemento));

	elemento->nome = strdup(nome);
	elemento->dependencias = g_sequence_new(freeChave);
	elemento->atributos = g_sequence_new(freeChave);

	return elemento;
}

Elemento * insereElemento(GTree * elementos, char * nome) {
	Elemento * elemento = (Elemento*) g_tree_lookup( elementos, nome );

	if (elemento == NULL) {
		elemento = inicializaElemento(nome);

		g_tree_insert( elementos, strdup( nome ), elemento );
	}

	return elemento;
}

void insereDependencia(Elemento * elementoActual, char * dependencia) {
	char * dep = (char*) g_sequence_lookup( elementoActual -> dependencias, dependencia, compararChave, NULL );

	if (dep == NULL) {
		g_sequence_insert_sorted( elementoActual -> dependencias, strdup( dependencia ), compararChave, NULL );
	}	
}

void insereAtributo(Elemento * elementoActual, char * atributo) {
	char * att = (char*) g_sequence_lookup( elementoActual -> atributos, atributo, compararChave, NULL );

	if (att == NULL) {
		g_sequence_insert_sorted( elementoActual -> atributos, strdup( atributo ), compararChave, NULL );
	}	
}

void printAtrOrDep(gpointer str, gpointer userdata){
	char * s = (char*) str;
	int * i = (int *) userdata;
	int nrActual = *i;

	if (nrActual > 0) printf(", ");
	printf("%s", s);

	nrActual++;
	*i = nrActual;
}

gboolean printElemento(gpointer key, gpointer elemento, gpointer userdata){
	Elemento * e = (Elemento*) elemento;
	int n;
	gboolean nrDependencias = g_sequence_get_length(e -> dependencias);
	gboolean nrAtributos = g_sequence_get_length(e -> atributos);

	printf(":: Elemento %s ::\n", e->nome);

	if (nrAtributos > 0) {
		n = 0;
		printf("\t%d Atributo(s): ", nrAtributos);
		g_sequence_foreach( e->atributos, printAtrOrDep, &n );
		printf("\n");
	}
	else {
		printf("\t%d Atributos\n", nrAtributos);
	}

	if (nrDependencias > 0) {
		n = 0;
		printf("\t%d Dependencia(s): ", nrDependencias);
		g_sequence_foreach( e->dependencias, printAtrOrDep, &n );
		printf("\n");
	}
	else {
		printf("\t%d Dependencias\n", nrDependencias);
	}

	return FALSE;
}

PrintAuxiliar * inicializaPrintAuxiliar(char * nomeElemento, FILE * ficheiro) {
	PrintAuxiliar * pAux = (PrintAuxiliar*) malloc(sizeof(PrintAuxiliar));

	pAux->nomeElemento = strdup(nomeElemento);
	pAux->ficheiro = ficheiro;

	return pAux;
}

void freePrintAuxiliar(PrintAuxiliar * printDependencia) {
	free( printDependencia->nomeElemento );

	free(printDependencia);
}

void printDependencia(gpointer dependencia, gpointer userdata){
	char * d = (char *) dependencia;
	PrintAuxiliar * pAux = (PrintAuxiliar *) userdata;

	fprintf(pAux->ficheiro,"\t%s -> %s;\n", pAux->nomeElemento, d);
}

gboolean printElementoGrafo(gpointer key, gpointer elemento, gpointer userdata){
	Elemento * e = (Elemento*) elemento;
	PrintAuxiliar * pAux = (PrintAuxiliar *) userdata;
	char * cores[] = { "white", "yellow", "orange", "orangered", "red", "red4" };
	int numeroNodos;

	PrintAuxiliar * pAuxE = inicializaPrintAuxiliar(e->nome, pAux->ficheiro);

	g_sequence_foreach( e->dependencias, printDependencia, pAuxE);
	numeroNodos = g_sequence_get_length(e->dependencias);

	fprintf(pAux->ficheiro,"\t\"%s\" [style=filled, fillcolor=%s];\n",e->nome,cores[MIN(numeroNodos,5)]);

	freePrintAuxiliar(pAuxE);

	return FALSE;
}

void gerarDependencias(GTree * elementos, char * nomeFicheiro, char * nomeElemento) {
	Elemento * elemento = (Elemento*) g_tree_lookup( elementos, nomeElemento );

	if (elemento != NULL) {
		FILE * dotFile = fopen(nomeFicheiro, "w+");
		
		fprintf(dotFile,"digraph dependencies {\n");

		PrintAuxiliar * pAux = inicializaPrintAuxiliar(nomeElemento, dotFile);

		g_sequence_foreach( elemento->dependencias, printDependencia, pAux);

		freePrintAuxiliar(pAux);

		fprintf(dotFile,"}");
		fclose(dotFile);
	}
	else {
		printf("Erro ::: Elemento não reconhecido.\n");
	}
}

void gerarDependenciasGlobais(GTree * elementos, char * nomeFicheiro) {

	FILE * dotFile = fopen(nomeFicheiro, "w+");
	
	fprintf(dotFile,"digraph dependencies {\n");

	PrintAuxiliar * pAux = inicializaPrintAuxiliar("", dotFile);

	g_tree_foreach( elementos, printElementoGrafo, pAux);

	freePrintAuxiliar(pAux);

	fprintf(dotFile,"}");
	fclose(dotFile);
}