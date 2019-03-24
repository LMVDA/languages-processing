#include "avl.h"

typedef struct listaVerbos{
    char *nome;
    int ocorrencias;
} *VERBO;

char* minusculas( char *t );

void incrementaOcorrencias(VERBO verb, int num);

void insereVerbo( char *v , AVL lista );

void freeVerbo( VERBO verb );

VERBO newVerb(char *nome, int ocorrencias);

int comparaVerbos (const void *a, const void *b, void *p);

void freeVerbAVL(void *avl_item, void *avl_param);

void geraListaVerbos(AVL avl);

