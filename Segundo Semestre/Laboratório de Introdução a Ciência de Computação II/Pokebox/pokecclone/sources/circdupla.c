#include "circdupla.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct no_ NO;

// Nó da lista: aponta para o nó anterior, o nó seguinte e armazena o item
struct no_{
    NO* proximo;
    NO* anterior;
    ITEM* item;
};

// Lista: contém o nó de início, o nó atual da lista e o tamanho dela
struct lista_{
    NO* inicio;
    int tamanho;
    NO* atual;
};

// Cria a lista;
LISTA* lista_criar(){
    LISTA* lista = malloc(sizeof(LISTA));
    if (lista){
        lista->inicio = NULL;
        lista->atual = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

// Adiciona uma caixa no começo da lista
void lista_inserir_inicio(LISTA* lista, ITEM* item){
    if (lista){
        NO* elemento = malloc(sizeof(NO));
        elemento->item = item;
        if (lista->inicio == NULL){
            elemento->proximo = elemento;
            elemento->anterior = elemento;
            lista->inicio = elemento;
            lista->atual = lista->inicio;
        }
        else{
            elemento->proximo = lista->inicio;
            elemento->anterior = lista->inicio->anterior;
            lista->inicio->anterior->proximo = elemento;
            lista->inicio->anterior = elemento;
            if (lista->atual == lista->inicio)
                lista->atual = elemento;
            lista->inicio = elemento;

        }
        lista->tamanho++;
    }
}

// Cria a lista com 3 caixas(itens) nulas
LISTA* lista_criar_3(){
    LISTA* lista = lista_criar();
    
    lista_inserir_inicio(lista, item_criar(NULL));
    lista_inserir_inicio(lista, item_criar(NULL));
    lista_inserir_inicio(lista, item_criar(NULL));
    return lista;
}

// Insere uma caixa no fim da lsita
void lista_inserir_fim(LISTA* lista, ITEM* item){
    if (lista){
        if (lista->inicio == NULL)
            lista_inserir_inicio(lista, item);
        else{
            NO* elemento = malloc(sizeof(NO));
            elemento->item = item;
            elemento->anterior = lista->inicio->anterior;
            elemento->proximo = lista->inicio;
            lista->inicio->anterior->proximo = elemento;
            lista->inicio->anterior = elemento;
        }
        lista->tamanho++;
    }
}

// Apaga a lista
void lista_apagar(LISTA** lista){
    NO* atual = (*lista)->inicio;
    for (int i = 0; i < (*lista)->tamanho; i++){
        NO* temp = atual->proximo;
        item_apagar(&atual->item);
        free(atual);
        atual = temp;
    }
    (*lista)->tamanho = 0;
    (*lista)->inicio = NULL;
    free(*lista);
    *lista = NULL;
}

// Movo o atual para a caixa seguinte
void lista_goto_direita(LISTA* lista){
    if (lista)
        lista->atual = lista->atual->proximo;
}

// Movo o atual para a caixa anterior
void lista_goto_esquerda(LISTA* lista){
    if (lista)
        lista->atual = lista->atual->anterior;
}

// Retorno a caixa atual
ITEM* lista_get_atual(LISTA* lista){
    if (lista)
        return lista->atual->item;
    return NULL;
}

// Removo caixa atual
void remover_elemento_atual(LISTA* lista){
    if (lista){
        if (lista->atual == lista->inicio)
            lista->inicio = lista->atual->proximo;

        lista->atual->anterior->proximo = lista->atual->proximo;
        lista->atual->proximo->anterior = lista->atual->anterior;
        NO* temp = lista->atual;
        lista->atual = lista->atual->proximo;
        item_apagar(&temp->item);
        free(temp);
        lista->tamanho--;
    }
}

// Adiciona pokémon na primeira posição vazia da caixa atual
// Caso não haja posição disponível na caixa atual, procura posição vazia na caixa seguinte
// OBS: caso a última caixa esteja cheia, cria-se uma nova caixa vazia e adiciona-se o pokémon nela
void opcao_3 (LISTA* lista, pokemon_t* pokemon){
    if (lista){
        boolean resposta = item_set_pkmn_atual(lista->atual->item, pokemon);
        if (resposta == TRUE)       // Tem espaço na caixa atual e o pokémon já foi adicionado
            return;
        NO* aux = lista->inicio;
        for (int i = 0; i < lista->tamanho; i++)
            aux = aux->proximo;
        if (lista->atual == aux){    // verifico se estou na última caixa
            lista_inserir_fim(lista, NULL);
            lista->atual = aux->proximo;
            item_set_pkmn_atual(lista->atual->item, pokemon);
        }
        else{
            lista->atual = lista->atual->proximo;
            item_set_pkmn_atual(lista->atual->item, pokemon);
        }
    }
}

// Adiciona um pokémon na posição indicada da caixa atual
void opcao_4 (LISTA* lista, pokemon_t* pokemon, int pos){
    if (lista)
        item_set_pkmn_pos(lista->atual->item, pokemon, pos);
}

// Remove o pokémon da posição indicada da caixa atual
void opcao_menos_4(LISTA* lista, int pos){
    if (lista)
        item_remove_pkmn_pos(lista->atual->item, pos);
}