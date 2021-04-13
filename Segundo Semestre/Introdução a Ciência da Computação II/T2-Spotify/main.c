/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    BCC  - Bacharelado de Ciências de Computação
    Aluno: Bernardo Marques Costa
    Número USP: 11795551

    Trabalho 1: Sistema de Recomendação de Músicas Spotify 
*/ 

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "track.h"
#include "knn.h"
#include "sort.h"

int main(int argc, char *argv[]){
    
    // Obtendo o nome arquivo csv que será utilizado para o programa
    char *spotify_csv = readline(stdin);  

    // Leitura do arquivo csv
    int num_tracks = 0;
    char **csv_data = read_csv(spotify_csv, &num_tracks);

    // Obtendo o vetor de structs que armazenam todos os dados de cada track
    TRACK **track_list = calloc(num_tracks, sizeof(TRACK*));
    for(int i = 0; i < num_tracks; ++i)
        track_list[i] = return_track_from_csv_string(csv_data[i]);

    // Ordenando o vetor de structs de tracks
    quicksort(track_list, 0, num_tracks - 1);

    // Obtendo a matriz de dissimilaridades 
    DM *dissimilarity_matrix = create_matrix(track_list, num_tracks);

    // Recebendo os valores de Q - número de músicas que serão pesquisadas por similaridades
    //                         K - número de vizinhos, utilizado no algorítmo de KNN
    int Q, K;
    scanf("%d %d\n", &Q, &K);
    
    for(int i = 0; i < Q; ++i) {
        char *searched_id = readline(stdin); // Recebendo os valores dos IDs que serão procurados
        
        // Printando as K músicas mais próximas ao id requisitado
        print_most_similar_tracks(dissimilarity_matrix, searched_id, K, track_list); 
        free(searched_id);
    }

    // Liberando a memória das tracks e dos dados do csv
    for(int i = 0; i < num_tracks; ++i){
        free(csv_data[i]);
        track_destruct(&track_list[i]);
    }
    free(track_list);
    
    free(csv_data);
    
    free(spotify_csv);
    
    // Liberando a matriz de dissimilaridades
    dm_delete(&dissimilarity_matrix);
     
    return 0;
}