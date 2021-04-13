#ifndef _TRIE_H_
#define _TRIE_H_

#define ALPHABET_SIZE 26

typedef struct TrieNode TRIENODE;
typedef struct Trie TRIE;

TRIE *trie_create(void);
void trie_delete(TRIE **);
void trie_insert_string(TRIE *, const char *);
int trie_search_word(TRIE *, char *);


#endif