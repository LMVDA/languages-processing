#ifndef AUXILIAR_GRAMATICA_H
#define AUXILIAR_GRAMATICA_H

#include "mapa_vars.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdio.h>

// Estrutura representa o valor de retorno da produção variável
typedef struct sVariavel {
	char * leitura;
	char * carregarEndereco;
	char * escrita;
} Variavel;

// Variáveis globais de utilizacao da gramatica
MapaFunVars mapaFunVars;
char * funcaoAtual;
char * strErr;
int nrIf;
int nrCiclo;
int enderecoAtual;

// Definicao necessaria para o compilador reconhecer
int yylex();
void yyerror(char *s);

// Função auxiliar para fazer merge de duas strings
GString * mergeGString(GString * s1, GString * s2);

// Funções que tratam cada uma das produções
void garanteExistenciaFuncao(char * funcao);
void garanteNaoRedeclaracaoFuncao(char * id);
void garanteNaoRedeclaracaoVariavel(char * id);
void garanteExistenciaVariavel(char * id);
void validaTipoVariavel(char * id);
void validaTipoEDimensoesArray(char * id, int tamanho);
void validaTipoEDimensoesMatriz(char * id, int linha, int coluna);
void garanteTamanhoArray(char * id, int tamanho);
void garanteTamanhoMatriz(char * id, int nLinhas, int nColunas);
void garanteReturn();
void garanteNaoReturn();
void garanteFuncaoTemRetorno(char * nomeFuncao);
GString * trataInicioPrograma(GString * funcoes, GString * funcaoStart);
GString * trataFuncoes(GString * funcoes, GString * funcao);
GString * inicializaFuncoes();
void trataFuncaoVoid(char * id);
void trataFuncaoComRetorno(char * id);
void trataFuncaoStart();
GString * trataCorpoFuncaoStart(GString * body);
GString * trataCorpoFuncaoVoid(char * id, GString * body);
GString * trataCorpoFuncaoComRetorno(char * id, GString * body);
GString * trataCorpo(GString * listaDeclaracoes, GString * body, char * ret);
GString * trataListaDeclaracoes(GString * listaDeclaracoes, GString * linhaDeclaracoes);
GString * inicializaListaDeclaracoes();
GString * trataLinhaDeclaracoes(GString * declaracoes);
GString * trataDeclaracoes(GString * declaracoes, char * declaracao);
GString * trataDeclaracao(char * declaracao);
char * trataDeclaracaoVariavel(char * id);
char * trataDeclaracaoAtribuicao(char * id, int num);
char * trataDeclaracaoArray(char * id, int tamanho);
char * trataDeclaracaoMatriz(char * id, int nLinhas, int nColunas);
GString * trataInstrucoes(GString * instrucoes, char * instrucao);
GString * inicializaInstrucoes();
char * trataInstrucaoCondicional(char * instrucao);
char * trataInstrucaoCiclica(char * instrucao);
char * trataInstrucaoAtribuicao(char * instrucao);
char * trataInstrucaoInvocacao(char * instrucao);
char * trataInstrucaoLeitura(char * instrucao);
char * trataInstrucaoEscrita(char * instrucao);
char * trataIf(char * cond, GString * instrucoesIf);
char * trataIfElse(char * cond, GString * instrucoesIf, GString * instrucoesElse);
char * trataWhile(char * cond, GString * instrucoes);
char * trataAtribuicao(Variavel variavel, char * exp);
char * trataInvocacao(char * nomeFuncao);
char * trataLeitura(Variavel variavel);
char * trataEscritaExpressao(char * exp);
char * trataEscritaString(char * string);
char * trataCondicaoAnd(char * condEsq, char * condDir);
char * trataCondicaoOr(char * condEsq, char * condDir);
char * trataCondicaoParenteses(char * cond);
char * trataCondicaoNot(char * cond);
char * trataCondicaoMenor(char * condEsq, char * condDir);
char * trataCondicaoMaior(char * condEsq, char * condDir);
char * trataCondicaoMenorIgual(char * condEsq, char * condDir);
char * trataCondicaoMaiorIgual(char * condEsq, char * condDir);
char * trataCondicaoDif(char * condEsq, char * condDir);
char * trataCondicaoIgual(char * condEsq, char * condDir);
char * trataCondicaoExp(char * exp);
char * trataExpTermo(char * termo);
char * trataExpSoma(char * expEsq, char * expDir);
char * trataExpSub(char * expEsq, char * expDir);
char * trataExpParenteses(char * exp);
char * trataTermoFator(char * fator);
char * trataTermoMult(char * termoEsq, char * termoDir);
char * trataTermoDiv(char * termoEsq, char * termoDir);
char * trataTermoMod(char * termoEsq, char * termoDir);
char * trataTermoParenteses(char * termo);
char * trataFatorNum(int numero);
char * trataFatorVar(Variavel variavel);
char * trataFatorInvocacao(char * nomeFuncao);
char * trataFatorLeitura();
void trataIdentificadorVariavel(Variavel * variavel, char * id);
void trataArray(Variavel * variavel, char * id, char * posicao);
void trataMatriz(Variavel * variavel, char * id, char * linha, char * coluna);
char * trataReturn(char * exp);
char * trataNaoReturn();
#endif