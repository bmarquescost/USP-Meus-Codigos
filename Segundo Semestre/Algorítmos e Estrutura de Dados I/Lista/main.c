#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "listaEncadeada.h"

int main(int argc, char *argv[]){
    LISTA *lista_encadeada = NULL;
    
    lista_encadeada = lista_criar();
    int numero_indices;
    
    ITEM *item;
    printf("Digite o número de chaves que serão escritos na lista: ");
    scanf("%d", &numero_indices);
    printf("\n");
    
    for(int i = 0; i < numero_indices; ++i){
        item = item_criar(i);
        lista_inserir(lista_encadeada, item);
    }

    lista_imprimir(lista_encadeada);
    ITEM *new = lista_busca(lista_encadeada ,12);
    lista_inverter(lista_encadeada);
    printf("Item buscado possui chave: %d\n", item_get_chave(new));
    printf("Removido\n");
    lista_remover(lista_encadeada, 12);

    lista_imprimir(lista_encadeada);    
    lista_apagar(&lista_encadeada);


    return 0;
}