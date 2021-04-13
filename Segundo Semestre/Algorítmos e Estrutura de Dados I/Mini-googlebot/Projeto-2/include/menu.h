#ifndef _MENU_H_
#define _MENU_H_

#include "avl.h"

void imprime_menu_complexo();
void executa_programa();
void imprime_menu();
boolean cria_site_insere_na_lista(AVL *arvore, int codigo, char *nome,  char *url, int relevancia, char **pc, int n_pc);
void carrega_dados_csv(AVL *arvore);
LISTA_SITES *verificar_sites_para_sugestao(AVL *arvore, TRIE *sites);
void sugerir_sites(AVL *arvore);

#endif