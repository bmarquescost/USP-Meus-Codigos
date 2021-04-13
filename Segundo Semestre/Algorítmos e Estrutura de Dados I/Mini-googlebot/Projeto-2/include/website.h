#ifndef _WEBSITE_H_
#define _WEBSITE_H_

#define boolean int
#define TRUE 1
#define FALSE 0

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
char **website_consulta_palavras_chave(WEBSITE *site);

boolean verifica_palavra_chave(WEBSITE *website, char *palavra_chave);

void mostrar_site(WEBSITE *site);


#endif