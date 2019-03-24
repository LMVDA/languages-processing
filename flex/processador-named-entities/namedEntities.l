%option noyywrap
%{
    #include <glib.h>
    #include <stdio.h>
    #include "utils.h"

    GTree* pessoas;
    GTree* cidades;
    GTree* paises;
    GTree* anos;
    char* aux;

%}

whitespace [ \t\r\n]
inicioComentario <!--
fimComentario -->
inicioTagEnamex \<ENAMEX{whitespace}+TYPE=
fimTagEnamex \<\/ENAMEX\>
conteudoTag [^<]*
inicioTagTimex \<TIMEX{whitespace}+TYPE=
fimTagTimex \<\/TIMEX\>
palavra [A-Za-z]+
digito [0-9]
ano {digito}{3,4}
dia {digito}{1,2}
mesNumerico {digito}{1,2}
mesExtenso {palavra}
data1 {dia}[- \/]{mesNumerico}[- \/]{ano}
data2 {dia}{whitespace}+de{whitespace}+{mesExtenso}{whitespace}+de{whitespace}+{ano}

%x COMENTARIO NOME CIDADE PAIS ANO

%%

<COMENTARIO>{fimComentario} {
    BEGIN INITIAL;
}

<COMENTARIO>.|\n {;
}



<NOME>{fimTagEnamex} {
    BEGIN INITIAL;
}

<NOME>{conteudoTag} {
    aux = retiraWhitespace(yytext, yyleng);
    insereArvore(pessoas, aux);
}



<CIDADE>{fimTagEnamex} {
    BEGIN INITIAL;
}

<CIDADE>{conteudoTag} {
    aux = retiraWhitespace(yytext, yyleng);
    insereArvore(cidades, aux);
}



<PAIS>{fimTagEnamex} {
    BEGIN INITIAL;
}

<PAIS>{conteudoTag} {
    aux = retiraWhitespace(yytext, yyleng);
    insereArvore(paises, aux);
}



<ANO>{fimTagTimex} {
    BEGIN INITIAL;
}


<ANO>{whitespace}*{data1}{whitespace}* {
    aux = retiraWhitespace(yytext, yyleng);
    aux = extraiAno(aux, 3);
    insereArvore(anos, aux);
}

<ANO>{whitespace}*{data2}{whitespace}* {
    aux = retiraWhitespace(yytext, yyleng);
    aux = extraiAno(aux, 5);
    insereArvore(anos, aux);
}

<ANO>{whitespace}*{ano}{whitespace}* {
    aux = retiraWhitespace(yytext, yyleng);
    aux = extraiAno(aux, 1);
    insereArvore(anos, aux);
}

<ANO>.|\n {;
}



{inicioComentario} {
    BEGIN COMENTARIO;
}

{inicioTagEnamex}\"PERSON\"\> {
    BEGIN NOME;
}

{inicioTagEnamex}\"NAME\"\> {
    BEGIN NOME;
}

{inicioTagEnamex}\"NAME\"{whitespace}+CERTEZA=\"\?\?\"\> {
    BEGIN NOME;
}

{inicioTagEnamex}\"CITY\"\> {
    BEGIN CIDADE;
}

{inicioTagEnamex}\"LOCATION\"\> {
    BEGIN CIDADE;
}

{inicioTagEnamex}\"COUNTRY\"\> {
    BEGIN PAIS;
}

\<ENAMEX\>{conteudoTag}{fimTagEnamex} {;
}

{inicioTagTimex}\"DATE\"\> {
    BEGIN ANO;
}


.|\n {;
}


%%



int main(int argc, char** argv) {
    if(argc != 3) {
        printf("ERRO: argumentos inválidos ou insuficientes!\n");
        printf("USE: ./namedEntities input.xml output.html\n");
        exit(1);
    }

    yyin = fopen(argv[1], "r");

    pessoas = g_tree_new((GCompareFunc) strcmp);
    cidades = g_tree_new((GCompareFunc) strcmp);
    paises = g_tree_new((GCompareFunc) strcmp);
    anos = g_tree_new((GCompareFunc) comparaAnos);

    yylex();

    ficheiroHtml(argv[2], pessoas, cidades, paises, anos);

    imprimirTreeConsola(pessoas, "Nome Pessoa");
    imprimirTreeConsola(cidades, "Cidade");
    imprimirTreeConsola(paises, "País");
    imprimirTreeConsola(anos, "Ano");

    return 0;
}
