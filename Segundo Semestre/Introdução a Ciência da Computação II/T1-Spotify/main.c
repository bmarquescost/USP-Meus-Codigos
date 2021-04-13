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
#include "spotify.h"


int main(int argc, char *argv[]){
    
    char *spotify_csv = readline(stdin);

    // Leitura do arquivo csv
    int num_tracks = 0;
    char **csv_data = read_csv(spotify_csv, &num_tracks);

    // Obtendo o vetor de structs que armazenam todos os dados de cada track
    TRACK **track_list = calloc(num_tracks, sizeof(TRACK*));
    for(int i = 0; i < num_tracks; ++i)
        track_list[i] = return_track_from_csv_string(csv_data[i]);
    
    // Preenchendo a lista de artistas, cada um com suas músicas e dados obtidos pelo spotify
    int num_artists = 0;
    SPOTIFY_LIST *spotify_artist_list = make_spotify_list(track_list, num_tracks, &num_artists);

    // Computando a média da popularidade de cada um dos artistas da lista
    compute_average_popularity(spotify_artist_list, num_artists);

    // Merge sort, ordenando a lista dos artistas considerando a média da popularidade
    sort_list_popularity(spotify_artist_list, num_artists);

    // Imprimindo a lista dos artistas com a fomatação desejada
    print_spotify_list(spotify_artist_list, num_artists, num_tracks);


    /* Liberando a memória da lista spotify criada. */
    // o.b.s: a lista e as tracks compartilham ponteiros, por isso não é necessário liberar a memória de todo
    //   os campos da lista. 
    for(int i = 0; i < num_artists; ++i)
        free(spotify_artist_list[i].all_tracks);
    free(spotify_artist_list);

    /* Liberando a memória das tracks e dos dados do csv */
    for(int i = 0; i < num_tracks; ++i){
        free(csv_data[i]);
        track_destruct(&track_list[i]);
    }

    free(track_list);
    free(csv_data);

    free(spotify_csv);

    return 0;
}