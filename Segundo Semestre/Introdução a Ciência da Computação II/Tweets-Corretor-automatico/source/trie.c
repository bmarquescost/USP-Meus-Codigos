/*
    Introdução a Ciência da Computação II
    Moacir Ponti 

    Aluno: Bernardo Marques Costa
    nUSP: 11795551

    Estrutura Trie que armazena caminhos para todas as strings existentes no dicionário
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

struct TrieNode {
    TRIENODE **children; // Vetor de filhos, com 26 filhos possíveis (número de letras do alfabeto)
    int string_end;      // Indicador do final da string
};

struct Trie {
    TRIENODE *root;      // Estrutura com a raiz inicial
};

static TRIENODE *_create_node(void) {
    TRIENODE *new_node = calloc(1,sizeof(TRIENODE));
    new_node->children = calloc(ALPHABET_SIZE, sizeof(TRIENODE));

    return new_node;
}

TRIE *trie_create(void) {
    TRIE *trie = calloc(1,sizeof(TRIE));
    trie->root = _create_node();
    return trie;
}

static void _recursive_trienode_delete(TRIENODE **root) {
    if(*root == NULL) return;
    for(int i = 0; i < ALPHABET_SIZE; ++i)
        _recursive_trienode_delete(&(*root)->children[i]);
    
    free((*root)->children);
    (*root)->children = NULL; 
    free(*root);
    *root = NULL;
}

void trie_delete(TRIE **deleted_trie) {
    _recursive_trienode_delete(&(*deleted_trie)->root);
    free(*deleted_trie);
    *deleted_trie = NULL;
}

/*
    Função privada, retorna o índice de cada caractere em relação ao vetor de nós
*/
static int _return_index_trie(char character) {
    if(character >= 'a' && character <= 'z')
        return character - 'a';
    if(character >= 'A' && character <= 'Z')
        return character - 'A'; 

    return -1;
}

/*
    Inserção de uma string na estrurura
*/
void trie_insert_string(TRIE *trie, const char *string) {
    int string_size = strlen(string);

    TRIENODE *current_node = trie->root;
    for(int i = 0; i < string_size; ++i) {
        int index = _return_index_trie(string[i]);
        if(current_node->children[index] == NULL) 
            current_node->children[index] = _create_node();
        current_node = current_node->children[index];
    }

    current_node->string_end = 1;
}

/*
    Verificação da existência de uma string na estrutura trie: 
    Para verificar se uma string existe, percorre um caminho nó a nó (cada nó correspondente a um caractere
    do alfabeto português), se existe tal caminho e se esta settado que é o fim da palavra, a string pertence
    ao dicionário.
*/
int trie_search_word(TRIE *trie, char *string) {
    int string_size = strlen(string);

    TRIENODE *current_node = trie->root;
    for(int i = 0; i < string_size; ++i) {
        int index = _return_index_trie(string[i]);
        if(current_node->children[index] == NULL)
            return 0;
        current_node = current_node->children[index];
    }

    return (current_node != NULL && current_node->string_end);
}
