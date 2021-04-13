/*
    SCC0202 - ALGORITMOS E ESTRUTURAS DE DADOS I
    Docente: Rudinei Goularte 

    Aluno: Bernardo Marques Costa                    Número USP: 11795551
    Aluno: Fernando Henrique Paes Generich           Número USP: 11795342

    MINI GOOGLEBOT 
*/
#ifndef _WEBSITE_H_
#define _WEBSITE_H_

#define boolean int
#define TRUE 1
#define FALSE 0
#define ERRO -32000

typedef struct _website WEBSITE;

WEBSITE *website_criar();
boolean website_deletar(WEBSITE **site);

boolean website_insere_nome(WEBSITE *site, char *nome);
char *website_consulta_nome(WEBSITE *site);

boolean website_insere_url(WEBSITE *site, char *url);
char *website_consulta_url(WEBSITE *site);

boolean website_insere_relevancia(WEBSITE *site, int relevancia);
int website_consulta_relevancia(WEBSITE *site);

boolean website_insere_codigo(WEBSITE *site, int codigo);
int website_consulta_codigo(WEBSITE *site);

boolean website_insere_palavra_chave(WEBSITE *site, char *palavra_chave);
int website_consulta_num_palavras_chave(WEBSITE *site);

void mostrar_site(WEBSITE *site);


#endif