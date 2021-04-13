/*
    Aluno: Bernardo Marques Costa
    nUSP: 11795551
*/
#ifndef _ITEM_H_
#define _ITEM_H_

typedef struct _item ITEM;

ITEM *item_criar(int chave);
void item_alterar_chave(ITEM *item, int chave);
int item_pegar_chave(ITEM *item);
void item_imprimir(ITEM *item);                
void item_deletar(ITEM **item);             

#endif