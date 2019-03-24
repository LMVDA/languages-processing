#include "auxiliarGramatica.h"

void garanteExistenciaFuncao(char * funcao) {
	if (!existe_funcao(mapaFunVars, funcao)) {
		asprintf(&strErr, "A funcao %s nao existe ou nao esta declarada.", funcao);
		yyerror(strErr);
		exit(0);
	}
}

void garanteNaoRedeclaracaoFuncao(char * id) {
	if (existe_funcao(mapaFunVars, id)) {
		asprintf(&strErr, "A funcao %s ja esta declarada.", id);
		yyerror(strErr);
		exit(0);
	}
}

void garanteNaoRedeclaracaoVariavel(char * id) {
	if (existe_variavel(mapaFunVars, funcaoAtual, id)) {
		asprintf(&strErr, "A variavel %s ja esta declarada.", id);
		yyerror(strErr);
		exit(0);
	}
}

void garanteExistenciaVariavel(char * id) {
	if (!existe_variavel(mapaFunVars, funcaoAtual, id)) {
		asprintf(&strErr, "A variavel %s nao foi ainda declarada.", id);
		yyerror(strErr);
		exit(0);
	}
}

void validaTipoVariavel(char * id) {
	InfoVar info = info_variavel(mapaFunVars, funcaoAtual, id);

	if (info -> tipo != INTEIRO) {
		asprintf(&strErr, "A variavel %s nao pode ser acedida sem dimensoes.", id);
		yyerror(strErr);
		exit(0);
	}
}

void validaTipoEDimensoesArray(char * id, int tamanho) {
	InfoVar info = info_variavel(mapaFunVars, funcaoAtual, id);

	if (info -> tipo != ARRAY) {
		asprintf(&strErr, "A variavel %s nao e um array.", id);
		yyerror(strErr);
		exit(0);
	}

	if (tamanho < 0 || tamanho >= info -> nrLinhas) {
		asprintf(&strErr, "Dimensao do array %s errada.", id);
		yyerror(strErr);
		exit(0);
	}
}

void validaTipoEDimensoesMatriz(char * id, int linha, int coluna) {
	InfoVar info = info_variavel(mapaFunVars, funcaoAtual, id);

	if (info -> tipo != MATRIZ) {
		asprintf(&strErr, "A variavel %s nao e uma matriz.", id);
		yyerror(strErr);
		exit(0);
	}

	if (linha < 0 || linha >= info -> nrLinhas || coluna < 0 || coluna >= info -> nrColunas) {
		asprintf(&strErr, "Dimensoes da matriz %s erradas.", id);
		yyerror(strErr);
		exit(0);
	}
}

void garanteTamanhoArray(char * id, int tamanho) {
	if (tamanho < 0) {
		asprintf(&strErr, "Dimensao do array %s erradas.", id);
		yyerror(strErr);
		exit(0);
	}
}

void garanteTamanhoMatriz(char * id, int nLinhas, int nColunas) {
	if (nLinhas < 0 || nColunas < 0) {
		asprintf(&strErr, "Dimensoes da matriz %s erradas.", id);
		yyerror(strErr);
		exit(0);
	}
}

void garanteReturn() {
	if (!existe_funcao_com_retorno(mapaFunVars, funcaoAtual)) {
		asprintf(&strErr, "A funcao %s nao devolve valor.", funcaoAtual);
		yyerror(strErr);
		exit(0);
	}
}

void garanteNaoReturn() {
	if (existe_funcao_com_retorno(mapaFunVars, funcaoAtual)) {
		asprintf(&strErr, "A funcao %s tem de devolver valor.", funcaoAtual);
		yyerror(strErr);
		exit(0);
	}
}

void garanteFuncaoTemRetorno(char * nomeFuncao) {
	if (!existe_funcao_com_retorno(mapaFunVars, nomeFuncao)) {
		asprintf(&strErr, "A funcao %s tem de devolver valor.", nomeFuncao);
		yyerror(strErr);
		exit(0);
	}
}

GString * mergeGString(GString * s1, GString * s2) {
	return g_string_append(s1, s2 -> str);
}

GString * trataInicioPrograma(GString * funcoes, GString * funcaoStart) {
	return mergeGString(funcaoStart, funcoes);
}

GString * trataFuncoes(GString * funcoes, GString * funcao) {
	return mergeGString(funcoes, funcao);
}

GString * inicializaFuncoes() {
	return g_string_new(NULL);
}

void trataFuncaoVoid(char * id) {
	garanteNaoRedeclaracaoFuncao(id);

	funcaoAtual = strdup(id);
	enderecoAtual = 0;

	insere_funcao(mapaFunVars, id, false);
}

void trataFuncaoComRetorno(char * id) {
	garanteNaoRedeclaracaoFuncao(id);

	funcaoAtual = strdup(id);
	enderecoAtual = 0;

	insere_funcao(mapaFunVars, id, true);
}

void trataFuncaoStart() {
	funcaoAtual = strdup("start");
	enderecoAtual = 0;

	insere_funcao(mapaFunVars, funcaoAtual, false);
}

GString * trataCorpoFuncaoStart(GString * body) {
	char * valorARetornar;
	asprintf(&valorARetornar, "pushi 0\n"
							  "start\n"
							  "%s"
							  "stop\n", body -> str);

	return g_string_new(valorARetornar);
}

GString * trataCorpoFuncaoVoid(char * id, GString * body) {
	char * valorARetornar;
	asprintf(&valorARetornar, "funcao_%s:\n"
							  "nop\n"
							  "%s"
							  "return\n", id, body -> str);

	return g_string_new(valorARetornar);
}

GString * trataCorpoFuncaoComRetorno(char * id, GString * body) {
	char * valorARetornar;
	asprintf(&valorARetornar, "funcao_%s:\n"
							  "nop\n"
							  "%s"
							  "return\n", id, body -> str);

	return g_string_new(valorARetornar);
}

GString * trataCorpo(GString * listaDeclaracoes, GString * body, char * ret) {
	GString * merged = mergeGString(listaDeclaracoes, body);
	return g_string_append(merged, ret);
}

GString * trataListaDeclaracoes(GString * listaDeclaracoes, GString * linhaDeclaracoes) {
	return mergeGString(listaDeclaracoes, linhaDeclaracoes);
}

GString * inicializaListaDeclaracoes() {
	return g_string_new(NULL);
}

GString * trataLinhaDeclaracoes(GString * declaracoes) {
	return declaracoes;
}

GString * trataDeclaracoes(GString * declaracoes, char * declaracao) {
	return g_string_append(declaracoes, declaracao);
}

GString * trataDeclaracao(char * declaracao) {
	return g_string_new(declaracao);
}

char * trataDeclaracaoVariavel(char * id) {
	// valida redeclaracao
	garanteNaoRedeclaracaoVariavel(id);
	// inicializar variavel
	insere_variavel_simples(mapaFunVars, funcaoAtual, id, enderecoAtual);
	enderecoAtual++;

	char * valorARetornar;
	asprintf(&valorARetornar, "pushi 0\n");

	return valorARetornar;
}

char * trataDeclaracaoAtribuicao(char * id, int num) {
	// valida redeclaracao
	garanteNaoRedeclaracaoVariavel(id);
	// inicializar variavel
	insere_variavel_simples(mapaFunVars, funcaoAtual, id, enderecoAtual);
	enderecoAtual++;

	char * valorARetornar;
	asprintf(&valorARetornar, "pushi %d\n", num);

	return valorARetornar;
}

char * trataDeclaracaoArray(char * id, int tamanho) {
	// valida redeclaracao
	garanteNaoRedeclaracaoVariavel(id);

	// valida tamanho
	garanteTamanhoArray(id, tamanho);
	// inicializar array
	insere_variavel_array(mapaFunVars, funcaoAtual, id, enderecoAtual, tamanho);
	enderecoAtual += tamanho;

	char * valorARetornar;
	asprintf(&valorARetornar, "pushn %d\n", tamanho);

	return valorARetornar;
}

char * trataDeclaracaoMatriz(char * id, int nLinhas, int nColunas) {
	// valida redeclaracao
	garanteNaoRedeclaracaoVariavel(id);

	// valida tamanho
	garanteTamanhoMatriz(id, nLinhas, nColunas);
	// inicializar matriz
	insere_variavel_matriz(mapaFunVars, funcaoAtual, id, enderecoAtual, nLinhas, nColunas);
	enderecoAtual += nLinhas * nColunas;

	char * valorARetornar;
	asprintf(&valorARetornar, "pushn %d\n", nLinhas * nColunas);

	return valorARetornar;
}

GString * trataInstrucoes(GString * instrucoes, char * instrucao) {
	// juntar instrucao a instrucoes
	return g_string_append(instrucoes, instrucao);
}

GString * inicializaInstrucoes() {
	return g_string_new(NULL);
}

char * trataInstrucaoCondicional(char * instrucao) {
	return instrucao;
}

char * trataInstrucaoCiclica(char * instrucao) {
	return instrucao;
}

char * trataInstrucaoAtribuicao(char * instrucao) {
	return instrucao;
}

char * trataInstrucaoInvocacao(char * instrucao) {
	return instrucao;
}

char * trataInstrucaoLeitura(char * instrucao) {
	return instrucao;
}

char * trataInstrucaoEscrita(char * instrucao) {
	return instrucao;
}

char * trataIf(char * cond, GString * instrucoesIf) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s"
							  "jz if_fim_%d\n"
							  "%s"
							  "if_fim_%d:\n", cond, nrIf, instrucoesIf -> str, nrIf); 

	nrIf++;

	return valorARetornar;
}

char * trataIfElse(char * cond, GString * instrucoesIf, GString * instrucoesElse) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s"
							  "jz else_%d\n"
							  "%s"
							  "jump if_fim_%d\n"
							  "else_%d:\n"
							  "%s"
							  "if_fim_%d:\n", cond, nrIf, instrucoesIf -> str, nrIf, nrIf, instrucoesElse -> str, nrIf); 

	nrCiclo++;

	return valorARetornar;
}

char * trataWhile(char * cond, GString * instrucoes) {
	char * valorARetornar;
	asprintf(&valorARetornar, "while_%d:\n"
							  "%s"
							  "jz while_fim_%d\n"
							  "%s"
							  "jump while_%d\n"
							  "while_fim_%d:\n", nrCiclo, cond, nrCiclo, instrucoes -> str, nrCiclo, nrCiclo); 

	nrCiclo++;

	return valorARetornar;
}

char * trataAtribuicao(Variavel variavel, char * exp) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s\n%s\n%s\n", variavel.carregarEndereco, exp, variavel.escrita);

	return valorARetornar;
}

char * trataInvocacao(char * nomeFuncao) {
	garanteExistenciaFuncao(nomeFuncao);

	char * valorARetornar;

	if (existe_funcao_com_retorno(mapaFunVars, nomeFuncao)) {
		asprintf(&valorARetornar, "pusha funcao_%s\ncall\nnop\npushg 0\n", nomeFuncao);
	}
	else {
		asprintf(&valorARetornar, "pusha funcao_%s\ncall\nnop\n", nomeFuncao);
	}
	

	return valorARetornar;
}

char * trataLeitura(Variavel variavel) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s"
							  "read\n"
							  "atoi\n"
							  "%s\n", variavel.carregarEndereco, variavel.escrita);

	return valorARetornar;
}

char * trataEscritaExpressao(char * exp) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s\nwritei\n", exp);

	return valorARetornar;
}

char * trataEscritaString(char * string) {
	char * valorARetornar;
	asprintf(&valorARetornar, "pushs %s\nwrites\n", string);

	return valorARetornar;
}

char * trataCondicaoAnd(char * condEsq, char * condDir) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s\n"
							  "%s\n"
							  "mul\n", condEsq, condDir);

	return valorARetornar;
}

char * trataCondicaoOr(char * condEsq, char * condDir) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s\n"
							  "%s\n"
							  "add\n", condEsq, condDir);

	return valorARetornar;
}

char * trataCondicaoParenteses(char * cond) {
	return cond;
}

char * trataCondicaoNot(char * cond) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s\npushi 1\nswap\nsub\n", cond);

	return valorARetornar;
}

char * trataCondicaoMenor(char * condEsq, char * condDir) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s\n%s\ninf\n", condEsq, condDir);

	return valorARetornar;
}

char * trataCondicaoMaior(char * condEsq, char * condDir) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s\n%s\nsup\n", condEsq, condDir);

	return valorARetornar;
}

char * trataCondicaoMenorIgual(char * condEsq, char * condDir) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s\n%s\ninfeq\n", condEsq, condDir);

	return valorARetornar;
}

char * trataCondicaoMaiorIgual(char * condEsq, char * condDir) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s\n%s\nsupeq\n", condEsq, condDir);

	return valorARetornar;
}

char * trataCondicaoDif(char * condEsq, char * condDir) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s\n%s\nequal\npushi 1\nswap\nsub\n", condEsq, condDir);

	return valorARetornar;
}

char * trataCondicaoIgual(char * condEsq, char * condDir) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s\n%s\nequal\n", condEsq, condDir);

	return valorARetornar;
}

char * trataCondicaoExp(char * exp) {
	return exp;
}

char * trataExpTermo(char * termo) {
	return termo;
}

char * trataExpSoma(char * expEsq, char * expDir) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s\n%s\nadd\n", expEsq, expDir);

	return valorARetornar;
}

char * trataExpSub(char * expEsq, char * expDir) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s\n%s\nsub\n", expEsq, expDir);

	return valorARetornar;
}

char * trataExpParenteses(char * exp) {
	return exp;
}

char * trataTermoFator(char * fator) {
	return fator;
}

char * trataTermoMult(char * termoEsq, char * termoDir) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s\n%s\nmul\n", termoEsq, termoDir);

	return valorARetornar;
}

char * trataTermoDiv(char * termoEsq, char * termoDir) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s\n%s\ndiv\n", termoEsq, termoDir);

	return valorARetornar;
}

char * trataTermoMod(char * termoEsq, char * termoDir) {
	char * valorARetornar;
	asprintf(&valorARetornar, "%s\n%s\nmod\n", termoEsq, termoDir);

	return valorARetornar;
}

char * trataTermoParenteses(char * termo) {
	return termo;
}

char * trataFatorNum(int numero) {
	char * valorARetornar;
	asprintf(&valorARetornar, "pushi %d", numero);

	return valorARetornar;
}

char * trataFatorVar(Variavel variavel) {
	return variavel.leitura;
}

char * trataFatorInvocacao(char * nomeFuncao) {
	garanteExistenciaFuncao(nomeFuncao);
	garanteFuncaoTemRetorno(nomeFuncao);

	char * valorARetornar;

	asprintf(&valorARetornar, "pusha funcao_%s\ncall\nnop\npushg 0\n", nomeFuncao);

	return valorARetornar;
}

char * trataFatorLeitura() {
	char * valorARetornar;
	asprintf(&valorARetornar, "read\natoi\n");

	return valorARetornar;
}

void trataIdentificadorVariavel(Variavel * variavel, char * id) {
	garanteExistenciaVariavel(id);
	validaTipoVariavel(id);
	
	InfoVar info = info_variavel(mapaFunVars, funcaoAtual, id);
	int endereco = info -> endereco;

	// assembly ler
	asprintf(&(variavel -> leitura), "pushl %d", endereco);

	// assembly escrever
	variavel -> carregarEndereco = "";

	asprintf(&(variavel -> escrita), "storel %d", endereco);
}

void trataArray(Variavel * variavel, char * id, char * posicao) {
	// valida se id existe
	garanteExistenciaVariavel(id);

	int pos = atoi(posicao);

	// valida tamanho
	validaTipoEDimensoesArray(id, pos);

	InfoVar info = info_variavel(mapaFunVars, funcaoAtual, id);
	int endereco = info -> endereco;

	// assembly ler
	asprintf(&(variavel -> leitura), "pushfp\n"
									 "pushi %d\n"
								  	 "padd\n"
								  	 "%s"
								  	 "loadn", endereco, posicao);

	// assembly escrever
	asprintf(&(variavel -> carregarEndereco), "pushfp\n"
										   	  "pushi %d\n"
										   	  "padd\n"
										   	  "%s", endereco, posicao);

	asprintf(&(variavel -> escrita), "storen");
}

void trataMatriz(Variavel * variavel, char * id, char * linha, char * coluna) {
	// valida se existe id
	garanteExistenciaVariavel(id);

	int nLinha = atoi(linha);
	int nColuna = atoi(coluna);

	// valida tamanhos
	validaTipoEDimensoesMatriz(id, nLinha, nColuna);

	// ir buscar endereço e número de colunas
	InfoVar info = info_variavel(mapaFunVars, funcaoAtual, id);
	int endereco = info -> endereco;
	int nColunas = info -> nrColunas;

	// assembly ler
	asprintf(&(variavel -> leitura), "pushfp\n"
									 "pushi %d\n"
								  	 "padd\n"
								 	 "%s"
								 	 "pushi %d\n"
								 	 "mul\n"
								 	 "%s"
								 	 "add\n"
								 	 "loadn", endereco, linha, nColunas, coluna);

	// assembly escrever
	asprintf(&(variavel -> carregarEndereco), "pushfp\n"
										 	  "pushi %d\n"
										 	  "padd\n"
										 	  "%s"
										 	  "pushi %d\n"
										 	  "mul\n"
										 	  "%s"
										 	  "add\n", endereco, linha, nColunas, coluna);

	asprintf(&(variavel -> escrita), "storen");
}

char * trataReturn(char * exp) {
	garanteReturn();

	char * valorARetornar;
	asprintf(&valorARetornar, "%s\nstoreg 0\n", exp);

	return valorARetornar;
}

char * trataNaoReturn() {
	garanteNaoReturn();

	return "";
}