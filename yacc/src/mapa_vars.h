#ifndef MAPA_VARS_H
#define MAPA_VARS_H

#include <glib.h>
#include <stdlib.h>
#include <stdbool.h>

// tipos de variáveis
typedef enum e_tipo {
    INTEIRO,
    ARRAY,
    MATRIZ
} TIPO_VAR;

// informação para cada variável
typedef struct s_info_var {
    TIPO_VAR tipo;
    int endereco;
    int nrLinhas;
    int nrColunas;
} * InfoVar, M_InfoVar;

// mapa de variáveis de uma função para info
typedef struct s_mapa_vars {
    GHashTable* vars;
    bool retornaAtom;
} * MapaVars, M_MapaVars;


// mapa de funções, cada uma com um mapa de variáveis para info
typedef struct s_mapa_func_vars {
    GHashTable* funcoes;
} * MapaFunVars, M_MapaFuncVars;


// API

// devolve um novo mapa de funções
MapaFunVars novo_mapa_fun_vars();

// inserir função
void insere_funcao(MapaFunVars mapa, char* funcao, bool retornaAtom);

// inserir variável simples
void insere_variavel_simples(MapaFunVars mapa, char* funcao, char* var, int endereco);

// inserir variável array
void insere_variavel_array(MapaFunVars mapa, char* funcao, char* var, int endereco, int tam);

// inserir variável matriz
void insere_variavel_matriz(MapaFunVars mapa, char* funcao, char* var, int endereco, int linhas, int colunas);

// testa se existe função
bool existe_funcao(MapaFunVars mapa, char* funcao);

// testa se a funcao existe e retorna um atom (inteiro)
bool existe_funcao_com_retorno(MapaFunVars mapa, char* funcao);

// testa se existe variável
bool existe_variavel(MapaFunVars mapa, char* funcao, char* var);

// devolve info de variável
InfoVar info_variavel(MapaFunVars mapa, char* funcao, char* var);


#endif