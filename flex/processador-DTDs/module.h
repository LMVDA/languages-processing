#ifndef MODULE_H
#define MODULE_H 0

#include <ctype.h>
#include <glib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char elementName[258];
typedef struct sElemento {
	char * nome;
	GSequence * dependencias;
	GSequence * atributos;
} Elemento;

typedef struct sPrintAuxiliar {
	FILE * ficheiro;
	char * nomeElemento;
} PrintAuxiliar;

gint compararChave ( gconstpointer a, gconstpointer b, gpointer user_data);
void freeElemento(gpointer elemento) ;
void freeChave (gpointer chave);
Elemento * inicializaElemento(char * nome);
Elemento * insereElemento(GTree * elementos, char * nome);
void insereDependencia(Elemento * elementoActual, char * dependencia);
void insereAtributo(Elemento * elementoActual, char * atributo);
void printAtrOrDep(gpointer str, gpointer userdata);
gboolean printElemento(gpointer key, gpointer elemento, gpointer userdata);
PrintAuxiliar * inicializaPrintAuxiliar(char * nomeElemento, FILE * ficheiro);
void freePrintAuxiliar(PrintAuxiliar * printDependencia);
void printDependencia(gpointer dependencia, gpointer userdata);
gboolean printElementoGrafo(gpointer key, gpointer elemento, gpointer userdata);
void gerarDependencias(GTree * elementos, char * nomeFicheiro, char * nomeElemento);
void gerarDependenciasGlobais(GTree * elementos, char * nomeFicheiro);

#endif