/*
############################################################
#                                                          #
#             Made by: Leonardo Tórtoro Pereira            #
#                   leonardop@usp.br                       #
#                                                          #
#      “you have something called "determination."         #
#       so as long as you hold on...                       #
#       so as long as you do what's in your heart...       #
#       i believe you can do the right thing.”             #
#                                                          #
#                   'll0MMMMMMMMMMMMMOll'                  #
#                 .OMMMMMMMMMMMMMMMMMMM0l'                 #
#                'OMMMMMMMMMMMMMMMMMMMMMM0'                #
#               '0MMMMMMMMMMMMMMMMMMMMMMMM0'               #
#              '0MMMMMMMMMMMMMMMMMMMMMMMMMM0'              #
#              lMMMMMMMMMMMMMMMMMMMMMMMMMMMMl              #
#              0MMMMMMMMMMMMMMMMMMMMMMMMMMMM0              #
#              MMMMMMMMMMMMMMMMMMMMMMMMMMMMMM              #
#              MMMMMMMMMMMMMMMMMMMMMMMMMMMMMM              #
#              MMMM0lllllOMMMMMMMM0lllll0MMMM              #
#              MM0l'     .OMMMMMM0'     'l0MM              #
#              M0'        lMMMMMMl        '0M              #
#              Ml    'l'  lMMMMMMl  'l'    lM              #
#              Ml    lMl  lMMMMMMl  lMl    lM              #
#              00'   'l' '0M0ll0M0' 'l'   '00              #
#              lM0l'     lMMl  lMMl     'l0Ml              #
#              '0MM0lll''0M0'  '0M0''lll0MM0'              #
#               lMMMM0ll0MMl    lMM0ll0MMMMl               #
#              '0MM000l0MMMl    lMMM0lOO0MMO.              #
#              lMM0'lMMMMMMOllll0MMMMMMl'0MMl              #
#              lM0' 'l0MMMMMMMMMMMMMM0l' '0Ml              #
#              lM0l' 'llllllllllllllll' 'l0Ml              #
#              lMMMl ll              ll lMMMl              #
#              '0MM0'll'l''l''lll''l'll'0MM0'              #
#               lMMM0l'lMllMllMMMllMl'l0MMMl               #
#               '0MMMO''0llMllMMMll0''0MMM0'               #
#                '0MMM0ll''l''lll''ll0MMM0'                #
#                 'l0MMM0llllllllll0MMMOl'                 #
#                   'l0MMMMMMMMMMMMMM0l'                   #
#                     lMMMMMMMMMMMMMMl                     #
#                                                          #
############################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Utils.h"
#include "poketype.h"
#include "pokemon.h"
#include "pokebox.h"
#include "pokedex.h"
#include "savemanager.h"
#include "moves.h"
#include "circdupla.h"
#include "item.h"

int main()
{
    pokemon_t** pkdex = NULL;
    srand(time(NULL));
    int totalPkmn = 0;

    pkdex = readPkDex(&totalPkmn);   

    // Crio a lista com 3 caixas nulas
    LISTA* lista = lista_criar_3();
    
    if (!lista){
        printf("Erro ao criar lista de pokeboxes\n");
        exit(1);
    }

    do{
        int option; scanf("%d", &option);
        if (option == 0) break;
        int pokemon = 0, posicao = 0;
        switch(option){
            case 1:
                // Ir para a caixa à direita
                lista_goto_direita(lista);
                break;
            case -1:
                // Ir para caixa à esquerda
                lista_goto_esquerda(lista);
                break;
            case 2:
                // Inserir caixa vazia no fim da lista
                lista_inserir_fim(lista, NULL);
                break;
            case -2:
                // Remove a caixa atual
                remover_elemento_atual(lista);
                break;
            case 3:
                // Adiciona pokémon na primeira posição vazia da caixa atual
                // Caso não haja posição disponível na caixa atual, procura posição vazia na caixa seguinte
                // OBS: caso a última caixa esteja cheia, cria-se uma nova caixa vazia e adiciona-se o pokémon nela
                scanf("%d\n", &pokemon);
                opcao_3(lista, pkdex[pokemon]);
                break;
            case 4:
                // Adiciona pokémon na posição indicada da caixa atual
                scanf("%d\n", &pokemon);
                scanf("%d\n", &posicao);
                opcao_4(lista, pkdex[pokemon], posicao);
                break;
            case -4:
                // Remove pokémon na posição indicada da caixa atual
                scanf("%d\n", &posicao);
                opcao_menos_4(lista, posicao);
                break;
            case 5:
                // Imprime a caixa atual
                printBox(item_get_pokelist(lista_get_atual(lista)));
                break;
            default:
                printf("Digite um comando válido!\n");
                break;
        }
    } while(1);

    for(int i = 0; i < totalPkmn; ++i)
        free(pkdex[i]);
    free(pkdex);

    // Apago a lista
    lista_apagar(&lista);
}