#ifndef ITEM_H
    #define ITEM_H

    #define TRUE 1
    #define FALSE 0
    #define boolean int

    #include "pokebox.h"

    typedef struct item_ ITEM;

    ITEM* item_criar(pokemon_t** pokelist);
    boolean item_apagar(ITEM **item);
    pokemon_t** item_get_pokelist(ITEM* item);
    boolean item_set_chave (ITEM* item, pokemon_t** pokelist);
    boolean item_set_pkmn_atual(ITEM* item, pokemon_t* pokemon);
    void item_set_pkmn_pos(ITEM* item, pokemon_t* pokemon, int pos);
    void item_remove_pkmn_pos(ITEM* item, int pos);
    
#endif