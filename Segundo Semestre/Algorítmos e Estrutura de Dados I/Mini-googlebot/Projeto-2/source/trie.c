#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

struct _no {
    NO **nos_filhos;      // Vetor de filhos, com 26 filhos possíveis (números de letras do alfabeto) 
    boolean indicador_final;  // Indicador do final da string
};

struct _trie {
    NO *raiz;   // Estrutura inicial com raiz inicial
};

static NO *_trie_criar_no(void) {
    NO *novo_no = calloc(1, sizeof(NO));
    novo_no->nos_filhos = calloc(ALFABETO, sizeof(NO));

    return novo_no;
}

TRIE *trie_criar(void) {
    TRIE *nova_trie = calloc(1, sizeof(TRIE));
    nova_trie->raiz = _trie_criar_no();

    return nova_trie;
}

static void _trie_deletar_recursiva(NO **raiz) {
    if(*raiz == NULL) return;

    for(int i = 0; i < ALFABETO; ++i)
        _trie_deletar_recursiva(&(*raiz)->nos_filhos[i]);
    
    free((*raiz)->nos_filhos);
    (*raiz)->nos_filhos = NULL;
    free(*raiz);
    *raiz = NULL;
}

void trie_deletar(TRIE **trie_deletada) {
    if(*trie_deletada == NULL)
        return;
    _trie_deletar_recursiva(&(*trie_deletada)->raiz);
    
    free(*trie_deletada);
    *trie_deletada = NULL;
}

/*
    Função privada, retorna o índice de cada caractere em relação ao vetor de nós
*/
static int _retornar_indice_trie(char caractere) {
    if(caractere >= 'a' && caractere <= 'z')
        return caractere - 'a';
    if(caractere >= 'A' && caractere <= 'Z')
        return caractere - 'A';
    
    return -1;
}

/*
    Inserção de uma string na estrurura
*/
void trie_inserir_palavra(TRIE *trie, const char *palavra) {
    int tamanho_string = strlen(palavra);

    NO *no_atual = trie->raiz;
    for(int i = 0; i < tamanho_string; ++i) {
        int indice = _retornar_indice_trie(palavra[i]);
       
        if(indice != -1) {
            if(no_atual->nos_filhos[indice] == NULL)
                no_atual->nos_filhos[indice] = _trie_criar_no();
            no_atual = no_atual->nos_filhos[indice];
        }
    }
    no_atual->indicador_final = TRUE;
}

/*
    Verificação da existência de uma string na estrutura trie: 
    Para verificar se uma string existe, percorre um caminho nó a nó (cada nó correspondente a um caractere
    do alfabeto português), se existe tal caminho e se esta settado que é o fim da palavra, a string pertence
    ao dicionário.
*/
boolean trie_procurar_palavra(TRIE *trie, char *palavra) {
    int tamanho_string = strlen(palavra);

    NO *no_atual = trie->raiz;
    for(int i = 0; i < tamanho_string; ++i) {
        int indice = _retornar_indice_trie(palavra[i]);

        if(indice != -1) {
            if(no_atual->nos_filhos[indice] == NULL)
                return FALSE;
            no_atual = no_atual->nos_filhos[indice];
        }
    }

    return (no_atual != NULL && no_atual->indicador_final);
}