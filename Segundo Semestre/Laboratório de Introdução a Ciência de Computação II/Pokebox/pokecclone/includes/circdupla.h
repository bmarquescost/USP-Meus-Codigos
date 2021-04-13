// Lista Circular Duplamente Encadeada

#ifndef CIRCDUPLA_H
    #define CIRCDUPLA_H

    #include "item.h"

    typedef struct lista_ LISTA;

    LISTA* lista_criar_3();
    void lista_inserir_fim(LISTA* lista, ITEM* item);
    boolean lista_vazia(LISTA* lista);
    void lista_apagar(LISTA** lista);
    ITEM* lista_get_atual(LISTA* lista);
    void lista_goto_direita(LISTA* lista);
    void lista_goto_esquerda(LISTA* lista);
    void remover_elemento_atual(LISTA* lista);
    void opcao_3 (LISTA* lista, pokemon_t* pokemon);
    void opcao_4 (LISTA* lista, pokemon_t* pokemon, int pos);
    void opcao_menos_4(LISTA* lista, int pos);

#endif