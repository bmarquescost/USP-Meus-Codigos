#ifndef _PALAVRAS_CHAVE_H_
#define _PALAVRAS_CHAVE_H_

typedef struct _lista_sites LISTA_SITES;
typedef struct _sugestoes SUGESTOES;
typedef struct _mesmas_palavra_chave MSM_PALAVRA;

#include "website.h"
#include "trie.h"

LISTA_SITES *lista_sites_criar(void);
void lista_sites_deletar(LISTA_SITES **sites);
void lista_sites_inserir_site(LISTA_SITES *sites_encontrados, WEBSITE *site);
void lista_sites_ordenar(LISTA_SITES *lista_sites);
void printar_lista_encontrada(LISTA_SITES *sites_encontrados);
int lista_sites_consulta_num_sites(LISTA_SITES *l);


// PRIMEIRA FUNÇÃO 
MSM_PALAVRA *msm_palavra_chave_criar(void);
void msm_palavra_chave_deletar(MSM_PALAVRA **sites_encontrados);

void msm_palavra_chave_alterar_palavra(MSM_PALAVRA *lista, char *palavra_chave);

void msm_palavra_chave_inserir_site(MSM_PALAVRA *palavra_chave, WEBSITE *site_encontrado);
void msm_palavra_chave_ordenar(MSM_PALAVRA *sites_encontrados);

// Segunda função
TRIE *construir_trie_com_lista_sites(LISTA_SITES *l);


#endif
