#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include "pokebox.h"


// O item contém a caixa(vetor de 9 pokémons) e a posição atual no vetor
struct item_{
    pokemon_t** pokelist;
    int posAtual;
};

ITEM* item_criar(pokemon_t** pokelist){
    ITEM *item = (ITEM *) malloc (sizeof(ITEM));

    if (item != NULL){
        item->pokelist = malloc(BOXSIZE*sizeof(pokemon_t*));
        for (int i = 0; i < BOXSIZE; i++)
            item->pokelist[i] = NULL;
        item->posAtual = 0;
    }
    return item;
}

boolean item_apagar(ITEM **item){
    if (*item != NULL){
        free((*item)->pokelist);
        (*item)->pokelist = NULL;
        free(*item);
        *item = NULL;
        return TRUE;
    }
    return FALSE;
}

// Retorna o vetor de pokémons, dado um item
pokemon_t** item_get_pokelist (ITEM *item){
    if (item != NULL)
        return item->pokelist;
    else{
        printf("\nERRO: item_get_pokelist\n");
        exit(1);
    }
}

// Diz se o vetor de pokémons está cheio
boolean pokelist_cheia(ITEM* item){
    for (int i = 0; i < BOXSIZE; i++){
        if (item->pokelist[i] == NULL)
            return FALSE;
    }
    return TRUE;
}

// Retorna verdadeiro caso consiga adicionar um pokémon na primeira posição vazia que encontrar ou retorna falso caso o vetor esteja cheio
boolean item_set_pkmn_atual(ITEM* item, pokemon_t* pokemon){
    if (pokelist_cheia(item) == TRUE)
        return FALSE;
    int i = 0;
    while(item->pokelist[i] != NULL)
        i++;
    item->posAtual = i;
    item->pokelist[item->posAtual] = pokemon;
    return TRUE;
}

// Adiciona um pokémon na posição escolhida do vetor
void item_set_pkmn_pos(ITEM* item, pokemon_t* pokemon, int pos){
    item->pokelist[pos] = pokemon;
}

// Remove o pokémon da posição escolhida do vetor
void item_remove_pkmn_pos(ITEM* item, int pos){
    item->pokelist[pos] = NULL;
}