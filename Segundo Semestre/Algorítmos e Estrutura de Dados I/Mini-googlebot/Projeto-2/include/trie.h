#ifndef _TRIE_H_
#define _TRIE_H_


#define ALFABETO 26
typedef struct _trie TRIE;
typedef struct _no NO;

#include "util.h"

TRIE *trie_criar(void);
void trie_deletar(TRIE **trie_deletada);
void trie_inserir_palavra(TRIE *trie, const char *palavra);
boolean trie_procurar_palavra(TRIE *trie, char *palavra);

#endif