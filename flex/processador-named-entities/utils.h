#ifndef UTILS_H
#define UTILS_H 0

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* retiraWhitespace(char* s, int tam);
char* extraiAno(char* s, int pos);
void insereArvore(GTree* a, char* s);
int comparaAnos(char* ano1, char* ano2);
void ficheiroHtml(char* nomeFicheiro, GTree* pessoas, GTree* cidades, GTree* paises, GTree* datas);
void imprimirTreeConsola(GTree* t, char* titulo);

#endif
