/*
    Aluno: Bernardo Marques Costa
    nUSP: 11795551
*/
#include <stdio.h>
#include <stdlib.h>

#include "item.h"

struct _item {
    int chave;
};

ITEM *item_criar(int chave) {
    ITEM *novo_item = calloc(1,sizeof(ITEM));
    novo_item->chave = chave;
    return novo_item;
}

void item_alterar_chave(ITEM *item, int chave) {
    if(item != NULL)
        item->chave = chave;
}

int item_pegar_chave(ITEM *item) {
    if(item != NULL) 
        return item->chave;
    return -32000;
}

void item_imprimir(ITEM *item) {
    if(item != NULL)
        printf("%d", item->chave);
}


void item_deletar(ITEM **item) {
    if(*item  != NULL) {
        free(*item);
        *item = NULL;
    }
}