/*
    SCC0202 - ALGORITMOS E ESTRUTURAS DE DADOS I
    Docente: Rudinei Goularte 

    Aluno: Bernardo Marques Costa                    Número USP: 11795551
    Aluno: Fernando Henrique Paes Generich           Número USP: 11795342

    MINI GOOGLEBOT 
*/

#ifndef _AVL_H_
#define _AVL_H_

typedef struct _no NO;
typedef struct _avl AVL;

#include "website.h"
#include "palavras_chave.h"

AVL *avl_criar(void);
void avl_deletar(AVL **arvore);
int avl_altura(NO *no);
boolean avl_inserir_site(AVL *arvore, WEBSITE *site);
boolean avl_procurar_codigo(AVL *arvore, int codigo);
boolean avl_remover_site(AVL *arvore, int codigo);
WEBSITE *avl_buscar_site(AVL *arvore, int codigo);
boolean avl_vazia(AVL *arvore);
void avl_imprimir_em_ordem(AVL *arvore);
void avl_imprimir_pre_ordem(AVL *arvore);
int avl_num_sites(AVL *arvore);
LISTA_SITES *avl_buscar_palavra_chave(AVL *arvore, char *palavra_chave);

#endif

/*

In file included from ./include/util.h:8,
                 from ./include/trie.h:5,
                 from ./include/palavras_chave.h:5,
                 from ./source/palavras_chave.c:4:
./include/avl.h:31:1: error: unknown type name ‘LISTA_SITES’
 LISTA_SITES *avl_buscar_palavra_chave(AVL *arvore, char *palavra_chave);
 ^~~~~~~~~~~
./source/palavras_chave.c: In function ‘construir_trie_com_lista_sites’:
./source/palavras_chave.c:130:19: warning: ‘return’ with no value, in function returning non-void
     if(l == NULL) return;
                   ^~~~~~
./source/palavras_chave.c:129:7: note: declared here
 TRIE *construir_trie_com_lista_sites(LISTA_SITES *l) {
       ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
In file included from ./include/avl.h:15,
                 from ./include/util.h:8,
                 from ./include/trie.h:5,
                 from ./source/trie.c:5:
./include/palavras_chave.h:32:1: error: unknown type name ‘TRIE’; did you mean ‘TRUE’?
 TRIE *construir_trie_com_lista_sites(LISTA_SITES *l);
 ^~~~
 TRUE
make: *** [Makefile:12: compile] Error 1

*/