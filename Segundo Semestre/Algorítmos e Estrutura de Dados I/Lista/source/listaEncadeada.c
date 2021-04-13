#include <stdio.h>
#include <stdlib.h>

#include "listaEncadeada.h"
#include "item.h"

typedef struct _no NO;

struct _no {
    ITEM *item; 
    NO *proximo;
};


struct _lista {
    NO* inicio;    
    int num_nos;
};


LISTA *lista_criar(void) {
    LISTA *nova_lista = calloc(1, sizeof(LISTA));
   
    nova_lista->inicio = NULL;
    nova_lista->num_nos = 0;
    
    return nova_lista;
}

void lista_apagar(LISTA **lista) {
    if(lista == NULL){
        printf("Erro ao apagar lista (lista inexistente).\n");
        return;
    }
    if(*lista == NULL) {
        free((*lista));
        return;
    }
    else {
        NO *no_apagado = (*lista)->inicio;
        
        while(no_apagado != NULL) {
            (*lista)->inicio = no_apagado->proximo;
            item_apagar(&no_apagado->item);
            no_apagado->proximo = NULL;
            free(no_apagado);
            
            no_apagado = (*lista)->inicio;
        }
        free(*lista);
    }
}

NO *criar_no(ITEM *item) {
    
    NO *no_novo = calloc(1,sizeof(NO));
    no_novo->item = item;
    no_novo->proximo = NULL;
    
    return no_novo;
}

boolean lista_inserir(LISTA *lista, ITEM *item) {
    if(lista == NULL || item == NULL) {
        printf("Erro ao inserir item na lista (item ou lista inexistente).\n");
        return FALSE;
    }

    NO *no_novo = criar_no(item); 
    
    if(lista->num_nos == 0) {
        lista->inicio = no_novo;
        ++lista->num_nos;
        return TRUE;
    }

    else {
        NO *anterior = NULL;
        NO *atual = lista->inicio;
        
        int chave_item = item_get_chave(item);
        int chave_atual = item_get_chave(atual->item);
        
        while(atual != NULL && chave_item > chave_atual) {
            chave_atual = item_get_chave(atual->item);
            anterior = atual;
            atual = atual->proximo;
        }

        if(atual == lista->inicio) {
            no_novo->proximo = lista->inicio;
            lista->inicio = no_novo;
        }

        else {
            no_novo->proximo = anterior->proximo;
            anterior->proximo = no_novo;
        }
        ++lista->num_nos;
    }

    return TRUE;
}

boolean lista_remover(LISTA *lista, int chave) {
    if(lista == NULL) {
        printf("Erro ao remover nó de uma lista (lista inexistente).\n");
        return FALSE;
    }
    
    NO *no_atual = lista->inicio;
    NO *no_anterior = NULL;
    
    int chave_no = item_get_chave(no_atual->item);

    while(no_atual != NULL) {
        chave_no = item_get_chave(no_atual->item);        
        
        if(chave_no == chave) {
            if(no_anterior != NULL) no_anterior->proximo = no_atual->proximo;
            else lista->inicio = no_atual->proximo;
            
            item_apagar(&no_atual->item);
            free(no_atual);   
            --lista->num_nos;
            return TRUE; 
        }

        no_anterior = no_atual;
        no_atual = no_atual->proximo;
    }
    return FALSE;
}   

ITEM *lista_busca(LISTA *lista, int chave) {
    if(lista == NULL) {
        printf("Erro ao buscar chave em lista (lista vazia).\n");
        return NULL;
    }
    NO *auxiliar = lista->inicio;
    int chave_no;
    while(auxiliar != NULL){
        chave_no = item_get_chave(auxiliar->item);
        if(chave_no == chave) break;
        auxiliar = auxiliar->proximo;
    }

    return auxiliar->item;
}   

int lista_tamanho(LISTA *lista){
    if(lista == NULL) {
        printf("Erro ao ler tamanho da lista (lista inexistente).\n");
        return ERRO;
    }

    return lista->num_nos;
}

boolean lista_vazia(LISTA *lista){
    if(lista == NULL) {
        printf("Erro ao verificar se a lista está vazia (lista inexistente).\n");
        return FALSE;
    }
    return  lista->num_nos == 0;
}

boolean lista_cheia(LISTA *lista){
    return FALSE; // Nunca é uma lista cheia, já que é alocada dinamicamente
}

void lista_inverter(LISTA *lista){
    if(lista == NULL) {
        printf("Erro ao inverter lista (lista inexistente).\n");
        return;
    }

    NO *anterior = lista->inicio;
    NO *atual = anterior->proximo;

    NO *auxiliar;

    while(atual != NULL) {
        auxiliar = anterior;
        anterior = atual;
        atual = atual->proximo;
        anterior->proximo = auxiliar;
    }
    lista->inicio->proximo = NULL;
    lista->inicio = anterior;
}

void lista_imprimir(LISTA *lista){
    if(lista == NULL) {
        printf("Error ao imprimir lista (lista vazia).\n");
    }
    
    NO *no_auxiliar = lista->inicio;
    int chave;
    int contador = 0;

    while(no_auxiliar != NULL) {
        chave = item_get_chave(no_auxiliar->item);
        printf("Chave[%d]: %d\n", contador, chave);
        ++contador;
        no_auxiliar = no_auxiliar->proximo;
    }
    printf("\n");
}