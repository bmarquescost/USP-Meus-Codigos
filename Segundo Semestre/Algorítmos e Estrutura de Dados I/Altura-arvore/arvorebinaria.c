#include <stdio.h>
#include <stdlib.h>
#include "arvorebinaria.h"

typedef struct _no NO;
struct _no {
    NO *esquerda;
    NO *direita;
    int item; // para facilitar a implementação
};

struct _arvore_bin {
    NO *raiz;
};

ARVORE_BIN *criar_arvore(void) {
    ARVORE_BIN *nova_arvore = calloc(1,sizeof(ARVORE_BIN));
    
    if(nova_arvore != NULL) 
        nova_arvore->raiz = NULL;

    return nova_arvore;
}

NO *_criar_novo_no(int item) {
    NO *novo_no = malloc(sizeof(NO));
    novo_no->item = item;
    novo_no->direita = NULL;
    novo_no->esquerda = NULL;
    return novo_no;
}

void _apagar_nos(NO **raiz) {
    if(*raiz != NULL) {
        _apagar_nos(&(*raiz)->esquerda);
        _apagar_nos(&(*raiz)->direita);
        free(*raiz);
        *raiz = NULL;
    }
}

void apagar_arvore_binaria(ARVORE_BIN **arvore) {
    if(*arvore == NULL) return;
    _apagar_nos(&(*arvore)->raiz);
    free(*arvore);
    *arvore = NULL;
}

NO *_inserir_no_recursivo(NO *raiz, int item, int lado, int chave) {
    if(raiz != NULL) {
        raiz->esquerda = _inserir_no_recursivo(raiz->esquerda, item, lado, chave);
        raiz->direita = _inserir_no_recursivo(raiz->direita, item, lado, chave);
        if(chave == raiz->item) {
            if(lado == INSERIR_ESQUERDA)
                raiz->esquerda = _criar_novo_no(item);
            else if(lado == INSERIR_DIREITA)
                raiz->direita = _criar_novo_no(item);
        }
    }
    
    return raiz;
}

int arvore_inserir(ARVORE_BIN *arvore, int item, int lado, int chave_pai) {
    if(arvore->raiz == NULL)
        return (arvore->raiz = _criar_novo_no(item)) != NULL;
    else 
        return (arvore->raiz = _inserir_no_recursivo(arvore->raiz, item, lado, chave_pai)) != NULL;
}

int _altura_recursiva(NO *raiz) {
    if(raiz != NULL) {
        int altura_esquerda = _altura_recursiva(raiz->esquerda) + 1;
        int altura_direita = _altura_recursiva(raiz->direita) + 1;
        
        if(altura_esquerda > altura_direita) 
            return altura_esquerda;
        else 
            return altura_direita;
    } 

    return 0;
}

int altura_da_arvore(ARVORE_BIN *arvore) {
    if(arvore == NULL) return 0;

    return _altura_recursiva(arvore->raiz);
}

int _nos_arvore_recursiva(NO *raiz) {
    if(raiz != NULL) {
        int nos_esquerda = _nos_arvore_recursiva(raiz->esquerda);
        int nos_direita = _nos_arvore_recursiva(raiz->direita);

        return nos_esquerda + nos_direita + 1;
    }

    return 0;
}

int nos_da_arvore(ARVORE_BIN *arvore) {
    if(arvore == NULL) return 0;
    return _nos_arvore_recursiva(arvore->raiz);
}

void imprimir_arvore(NO *raiz) {
	if(raiz != NULL) {
		printf("%d", raiz->item);
        printf("(");
		imprimir_arvore(raiz->esquerda);
		printf(",");
		imprimir_arvore(raiz->direita);
		printf(")");
	}
	else printf("null");
}

void arvore_imprimir(ARVORE_BIN *a) {
    imprimir_arvore(a->raiz);
}