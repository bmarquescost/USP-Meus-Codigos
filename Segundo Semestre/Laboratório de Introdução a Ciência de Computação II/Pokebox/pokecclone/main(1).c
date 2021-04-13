#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Util.h"
#include "PokeType.h"
#include "Pokemon.h"
#include "PokeBox.h"
#include "PokeDex.h"
#include "SaveManager.h"
#include "Moves.h"
#include "dll.h"

/*
     1 - Ir para a caixa à direita
    -1 - Ir para a caixa à esquerda
     2 - Adicionar uma nova caixa VAZIA ao final da lista
    -2 - Remover a caixa atual
     3 - Adicionar Pokémon na posição atual*
     4 - Adicionar Pokémon na posição indicada
    -4 - Remover Pokémon na posição indicada
     5 - Imprimir caixa atual*
     0 - Parar a leitura de entradas e terminar o programa
*/

enum options_positive {EXIT = 0, RIGHT_BOX, ADD_B0X, CURRENT_ADD_POKEMON, INDEX_ADD_POKEMON, PRINT_CURRENT_BOX};
enum option_negative {INDEX_REMOVE_POKEMON = -4, REMOVE_CURRENT_BOX = -2, LEFT_BOX};

int main(int argc, char *argv[]) {
    
    POKELIST *pl = pokelist_create();
    
    srand(time(NULL));
    int totalPkmn = 0;

    pokemon_t** pkdex = readPkDex(&totalPkmn);

    int command;
    int national_dex;
    do {
        scanf("%d", &command);
        
        if(command == RIGHT_BOX) 
            pokelist_right_pokebox(pl);
        
        else if(command == LEFT_BOX)
            pokelist_left_pokebox(pl);
        
        else if(command == ADD_B0X)
            pokelist_insert_box_at_end(pl);
        
        else if(command == REMOVE_CURRENT_BOX)
            pokelist_remove_box(pl);        
        
        else if(command == CURRENT_ADD_POKEMON) {
            scanf("%d", &national_dex);
            pokelist_insert_pokemon_current_box(pl, pkdex[national_dex]);
        }

        else if(command == INDEX_ADD_POKEMON) {
            int pokebox_slot;
            scanf("%d", &national_dex);
            scanf("%d", &pokebox_slot);
            pokelist_insert_pokemon_indexed(pl, pkdex[national_dex], pokebox_slot);
        }
        
        else if(command == INDEX_REMOVE_POKEMON) {
            int pokebox_slot;
            scanf("%d", &pokebox_slot);
            pokelist_remove_pokemon_indexed(pl, pokebox_slot);
        }
        
        else if(command == PRINT_CURRENT_BOX) 
            pokelist_print_box(pl);

    } while(command != EXIT);

    pokelist_delete(&pl);
    
    for(int i = 0; i < totalPkmn; ++i)
        free(pkdex[i]);
    free(pkdex);

    return 0;
}
