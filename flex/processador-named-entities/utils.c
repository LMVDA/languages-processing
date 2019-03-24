#include "utils.h"

char* extraiAno(char* s, int pos) {
    int i = 0;
    char * tok = strtok(s, "-/ ");
    i++;
    while(i < pos) {
        tok = strtok(NULL, "-/ ");
        i++;
    }
    return tok;
}


char* retiraWhitespace(char* s, int tam) {
    int i = 0;
    s[tam] = '\0';
    char* s2 = strdup(s);
    char* tok2 = strtok(s,"\t\r\n ");
    while(tok2 != NULL) {
        strcpy(s2+i, tok2);
        i += strlen(tok2);
        s2[i] = ' ';
        i++;
        tok2 = strtok(NULL, "\t\r\n ");
    }
    s2[i-1] = '\0';
    return s2;
}


void insereArvore(GTree* a, char* s) {
    int * contador;
    gpointer valor = g_tree_lookup(a,s);
    if(valor != NULL) {
        contador = (int*) valor;
        *contador = *contador + 1;
    }
    else {
        contador = (int*) malloc(sizeof(int));
        *contador = 1;
    }
    g_tree_insert(a, s, (gpointer) contador);
}


int imprimir_nodos(gpointer key, gpointer value, gpointer data) {
    int * contador = (int*) value;
    printf("%40s | %d\n", (char*) key, *contador);
    return FALSE; // se fizer return TRUE, o ciclo pára aqui
}

int imprimir_html(gpointer key, gpointer value, gpointer fp) {
    fprintf(fp, "    <li>%s</li>\n", (char*) key );
    return FALSE; // se fizer return TRUE, o ciclo pára aqui
}

int minTree(gpointer key, gpointer value, gpointer min) {
    char ** m = (char**) min;
    *m = (char *) key;
    return TRUE;
}

int maxTree(gpointer key, gpointer value, gpointer max) {
    char ** m = (char**) max;
    *m = (char *) key;
    return FALSE;
}

int imprimir_locais_mapa(gpointer key, gpointer value, gpointer fp) {
    fprintf(fp, "paises.push('%s') \n", (char*) key);
    return FALSE;

}

int comparaAnos(char* ano1, char* ano2) {
    int a1 = atoi(ano1);
    int a2 = atoi(ano2);

    return a1-a2;
}


void ficheiroHtml(char* nomeFicheiro, GTree* pessoas, GTree* cidades, GTree* paises, GTree* datas){
    // criar ficheiro
    FILE *  fp = fopen(nomeFicheiro,"w");

    // cabeçalho
    fprintf(fp, "<html>\n" );
    fprintf(fp,"<head><title>ENAMEX</title>");
    fprintf(fp, "<meta charset=\"utf-8\">");
    fprintf(fp, "<link type=\"text/css\" rel=\"stylesheet\" href=\"style.css\">");
    fprintf(fp, "<script type=\"text/javascript\" src=\"mapa.js\"></script>");
    fprintf(fp, "<script async defer src=\"https://maps.googleapis.com/maps/api/js?key=AIzaSyAfOWF0pLA5GiHHXFit1vwK72CCrLRFTgI\"></script>" );
    fprintf(fp, "<script> paises = [];\n");
    g_tree_foreach(cidades, imprimir_locais_mapa, fp);
    g_tree_foreach(paises, imprimir_locais_mapa, fp);
    fprintf(fp, "</script>");
    fprintf(fp,"</head>\n");
    fprintf(fp,"<body onload=\"initMap()\">\n");
    fprintf(fp,"<h1>Named Entities</h1>\n");
    fprintf(fp,"<div class=\"col-group\">\n");

    // pessoas
    fprintf(fp,"<div id=\"pessoas\">");
    fprintf(fp,"<h2>Pessoas</h2>");
    fprintf(fp,"  <ul>");
    g_tree_foreach(pessoas, imprimir_html, fp);
    fprintf(fp,"  </ul>");
    fprintf(fp,"</div>\n");

    // Países
    fprintf(fp,"<div id=\"paises\">");
    fprintf(fp,"<h2>Paises</h2>");
    fprintf(fp,"  <ul>");
    g_tree_foreach(paises, imprimir_html, fp);
    fprintf(fp,"  </ul>");
    fprintf(fp,"</div>\n");

    // Cidades
    fprintf(fp,"<div id=\"cidades\">");
    fprintf(fp,"<h2>Cidades</h2>");
    fprintf(fp,"  <ul>");
    g_tree_foreach(cidades, imprimir_html, fp);
    fprintf(fp,"  </ul>");
    fprintf(fp,"</div>\n");

    // Min/Max anos
    char *min, *max;
    g_tree_foreach(datas, minTree, &min);
    g_tree_foreach(datas, maxTree, &max);
    fprintf(fp,"<div id=\"anos\">");
    fprintf(fp,"<h2>Menor Ano: %s</h2>", min);
    fprintf(fp,"<h2>Maior Ano: %s</h2>", max);
    fprintf(fp,"</div>\n");
    fprintf(fp,"</div>\n");

    // Mapa
    fprintf(fp, "<div id=\"map\"></div>\n");

    fprintf(fp,"</body>");
    fprintf(fp,"</html>");
    fclose(fp);
}

void imprimirTreeConsola(GTree* t, char* titulo) {
    printf("\n\n%40s | %s\n", titulo, "Ocorrências");
    printf("----------------------------------------------------------------------\n");
    g_tree_foreach(t, imprimir_nodos, NULL);
    int total = g_tree_nnodes (t);
    printf("----------------------------------------------------------------------\n");
    printf("%40s | %d\n", "Total Único", total);
}

// void imprimirDadosConsola() {
//     printf("\n\n%40s | %s\n", "Nome Pessoa", "Ocorrências");
//     printf("----------------------------------------------------------------------\n");
//     g_tree_foreach(pessoas, imprimir_nodos, NULL);
//     int nrPessoas = g_tree_nnodes (pessoas);
//     printf("----------------------------------------------------------------------\n");
//     printf("%40s | %d\n", "Total Único", nrPessoas);

//     printf("\n\n%40s | %s\n", "Cidade", "Ocorrências");
//     printf("----------------------------------------------------------------------\n");
//     g_tree_foreach(cidades, imprimir_nodos, NULL);
//     int nrCidades = g_tree_nnodes (cidades);
//     printf("----------------------------------------------------------------------\n");
//     printf("%40s | %d\n", "Total Único", nrCidades);

//     printf("\n\n%40s | %s\n", "País", "Ocorrências");
//     printf("----------------------------------------------------------------------\n");
//     g_tree_foreach(paises, imprimir_nodos, NULL);
//     int nrPaises = g_tree_nnodes (paises);
//     printf("----------------------------------------------------------------------\n");
//     printf("%40s | %d\n", "Total Único", nrPaises);

//     printf("\n\n%40s | %s\n", "Ano", "Ocorrências");
//     printf("----------------------------------------------------------------------\n");
//     g_tree_foreach(datas, imprimir_nodos, NULL);
//     int nrDatas = g_tree_nnodes (datas);
//     printf("----------------------------------------------------------------------\n");
//     printf("%40s | %d\n", "Total Único", nrDatas);
// }
