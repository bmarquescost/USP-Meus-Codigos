#include <stdio.h>
#include <stdlib.h>

#include "item.h"

struct _item {
    int chave;
};


ITEM *item_criar(int chave) {
    ITEM *novo_item = calloc(1, sizeof(ITEM));
    novo_item->chave = chave;
    return novo_item;
}

boolean item_apagar(ITEM **item) {
    if(item == NULL) return FALSE;
    if(*item == NULL) return FALSE;
    else
        free(*item);
    return TRUE;
}

int item_get_chave(ITEM *item) {
    if(item == NULL){
        printf("Erro ao obter chave (item inexistente).\n");
        return ERRO;
    }
    else return item->chave;

}

boolean item_set_chave(ITEM *item, int n) {
    if(item == NULL){
        printf("Erro ao alterar valor da chave (item inexistente).\n");
        return FALSE;
    }
    item->chave = n;
    return TRUE;
}