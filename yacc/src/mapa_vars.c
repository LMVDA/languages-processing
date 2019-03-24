#include "mapa_vars.h"

//debug
#include <stdio.h>


// devolve um novo mapa de funções
MapaFunVars novo_mapa_fun_vars() {
    MapaFunVars m = (MapaFunVars) malloc(sizeof(M_MapaVars));
    m->funcoes = g_hash_table_new(g_str_hash, g_str_equal);
    return m;
}

// inserir função
void insere_funcao(MapaFunVars mapa, char* funcao, bool retornaAtom) {
    MapaVars vars = (MapaVars) malloc(sizeof(MapaVars));
    vars->vars = g_hash_table_new(g_str_hash, g_str_equal);
    vars->retornaAtom = retornaAtom;
    g_hash_table_insert(mapa->funcoes, funcao, vars);
}

// inserir variável 
void insere_variavel_simples(MapaFunVars mapa, char* funcao, char* var, int endereco) {
    MapaVars vars = g_hash_table_lookup(mapa->funcoes, funcao);

    InfoVar info = (InfoVar) malloc(sizeof(M_InfoVar));
    info->tipo = INTEIRO;
    info->endereco = endereco;

    g_hash_table_insert(vars->vars, var, info);
}

// inserir variável array
void insere_variavel_array(MapaFunVars mapa, char* funcao, char* var, int endereco, int tam) {
    MapaVars vars = g_hash_table_lookup(mapa->funcoes, funcao);

    InfoVar info = (InfoVar) malloc(sizeof(M_InfoVar));
    info->tipo = ARRAY;
    info->endereco = endereco;
    info->nrLinhas = tam;

    g_hash_table_insert(vars->vars, var, info);
}

// inserir variável matriz
void insere_variavel_matriz(MapaFunVars mapa, char* funcao, char* var, int endereco, int linhas, int colunas) {
    MapaVars vars = g_hash_table_lookup(mapa->funcoes, funcao);

    InfoVar info = (InfoVar) malloc(sizeof(M_InfoVar));
    info->tipo = MATRIZ;
    info->endereco = endereco;
    info->nrLinhas = linhas;
    info->nrColunas = colunas;

    g_hash_table_insert(vars->vars, var, info);
}

// testa se existe função
bool existe_funcao(MapaFunVars mapa, char* funcao) {
    return g_hash_table_contains(mapa->funcoes, funcao);
}

// testa se a funcao existe e retorna um atom (inteiro)
bool existe_funcao_com_retorno(MapaFunVars mapa, char* funcao) {
    bool res = false;
    MapaVars m = g_hash_table_lookup(mapa->funcoes, funcao);
    if(m != NULL) {
        res = m->retornaAtom;
    }
    return res;
}

// testa se existe variável
bool existe_variavel(MapaFunVars mapa, char* funcao, char* var) {
    bool res = false;
    MapaVars vars = g_hash_table_lookup(mapa->funcoes, funcao);
    if(vars != NULL) {
        res = g_hash_table_contains(vars->vars, var);
    }
    return res;
}

// devolve info de variável
InfoVar info_variavel(MapaFunVars mapa, char* funcao, char* var) {
    InfoVar info = NULL;
    MapaVars vars = g_hash_table_lookup(mapa->funcoes, funcao);
    if(var != NULL) {
        info = g_hash_table_lookup(vars->vars, var);
    }
    return info;
}


// // debug
// int main() {
//     MapaFunVars m = novo_mapa_fun_vars();

//     insere_funcao(m, "main", false);
//     insere_funcao(m, "soma", true);
//     insere_variavel_simples(m, "soma", "x", 4);
//     insere_variavel_simples(m, "soma", "y", 10);
//     insere_variavel_array(m, "soma", "z", 11, 20);
//     insere_variavel_matriz(m, "main", "y", 20, 3, 3);

//     printf("main T %d\n", existe_funcao(m, "main")); //sim
//     printf("soma T %d\n", existe_funcao(m, "soma")); //sim
//     printf("divide F %d\n", existe_funcao(m, "divide")); //nao

//     printf("main retorn F %d\n", existe_funcao_com_retorno(m, "main")); //nao
//     printf("soma retorn T %d\n", existe_funcao_com_retorno(m, "soma")); //sim

//     printf("main y T %d\n", existe_variavel(m, "main", "y")); //sim
//     printf("main x F %d\n", existe_variavel(m, "main", "x")); //nao
//     printf("soma x T %d\n", existe_variavel(m, "soma", "x")); //sim
//     printf("soma y T %d\n", existe_variavel(m, "soma", "y")); //sim
//     printf("soma z T %d\n", existe_variavel(m, "soma", "z")); //sim
//     printf("soma a F %d\n", existe_variavel(m, "soma", "a")); //nao
//     printf("divide x F %d\n", existe_variavel(m, "divide", "x")); //nao

//     ///// VER  G_BOOLEAN VS BOOL

//     InfoVar info1 = info_variavel(m, "main", "x");
//     if(info1 == NULL) { printf("info1 NULL\n");}
//     else { printf("info1 NOT null\n");}

//     InfoVar info2 = info_variavel(m, "main", "y");
//     if(info2 == NULL) { printf("info2 NULL\n");}
//     else { 
//         printf("info2 NOT null\n");
//         printf("Matriz t:%d e:%d l:%d c:%d\n", info2->tipo, info2->endereco, info2->nrLinhas, info2->nrColunas);
//     }

//     InfoVar info3 = info_variavel(m, "soma", "x");
//     if(info3 == NULL) { printf("info3 NULL\n");}
//     else { 
//         printf("info3 NOT null\n");
//         printf("Matriz t:%d e:%d l:%d c:%d\n", info3->tipo, info3->endereco, info3->nrLinhas, info3->nrColunas);
//     }

//     return 0;
// }