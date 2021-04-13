// Bernardo Marques Costa - 11795551
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spotify.h"

 
/*    Retorna a posição no vetor da estrutura que armazena um determinado nome buscado     */
/*    o.b.s: retorna -1 caso não seja encontrado o nome dentro da lista buscada            */
int check_artist_index_in_list(SPOTIFY_LIST *spotify_list, char *artist_name, int num_artists){
    if(spotify_list  == NULL) 
        return -1;
    
    for(int i = 0; i < num_artists; ++i){
        if(!strcmp(spotify_list[i].artist_data->artist_name, artist_name))
            return i;    
    }
    
    return -1;
}

/* Constrói a lista de artistas do spotify, separando todas as faixas obtidas no CSV, de acordo com o artista (groupby) */
SPOTIFY_LIST *make_spotify_list(TRACK **track_list, int num_tracks, int *num_artists){
    SPOTIFY_LIST *new_spotify_list = NULL;
    
    for(int i = 0; i < num_tracks; ++i){
        char *aux_artist_name = track_list[i]->artist->artist_name;
        int index = check_artist_index_in_list(new_spotify_list, aux_artist_name, *num_artists);
        
        if(index == -1){
            new_spotify_list = realloc(new_spotify_list, (*num_artists + 1) * sizeof(SPOTIFY_LIST));
            new_spotify_list[*num_artists].all_tracks = calloc(1,sizeof(TRACK*));
            new_spotify_list[*num_artists].all_tracks[0] = track_list[i];
            new_spotify_list[*num_artists].artist_data = track_list[i]->artist;
            new_spotify_list[*num_artists].num_tracks = 1;
            ++(*num_artists);
        }
        
        else{
            int num_tracks = new_spotify_list[index].num_tracks;
            new_spotify_list[index].all_tracks = realloc(new_spotify_list[index].all_tracks, (num_tracks + 1) * sizeof(TRACK*));
            new_spotify_list[index].all_tracks[num_tracks] = track_list[i];
            ++(new_spotify_list[index].num_tracks);
        }
    }

    return new_spotify_list;
}


/* Printa a lista do spotify obtida */
void print_spotify_list(SPOTIFY_LIST *list, int n_artists, int n_tracks){
    printf("O Dataset contem %d Artistas e %d Musicas\n", n_artists, n_tracks);
    printf("Os artistas mais populares sao:\n");
    
    for (int i=0; i < n_artists; ++i)
        printf("(%d) Artista: %s, Musicas: %d musicas, Popularidade: %.2lf, Link: https://open.spotify.com/artist/%s\n", i+1, list[i].artist_data->artist_name, list[i].num_tracks, list[i].average_popularity, list[i].artist_data->artist_id);
}

/*  Contabiliza a média da popularidade de cada um dos artistas obtidos na lista */ 
void compute_average_popularity(SPOTIFY_LIST *list, int n_artists){
    double average = 0;
    for(int i = 0; i < n_artists; ++i){
        average = 0;
        for(int j = 0; j < list[i].num_tracks; ++j)
           average += list[i].all_tracks[j]->music->popularity;
        
        list[i].average_popularity = average/list[i].num_tracks;
    }
}

/* Conquista do merge sort (união ordenada dos vetores) */
void merge(SPOTIFY_LIST *list, int start, int middle, int end){
    SPOTIFY_LIST *aux_list = calloc(end - start + 1, sizeof(SPOTIFY_LIST));
    
    int i = start;
    int j = middle + 1;
    int k = 0;

    while(i <= middle && j <= end){
        if(list[i].average_popularity > list[j].average_popularity)
            aux_list[k++] = list[i++];
        else
            aux_list[k++] = list[j++];
    }

    while(i <= middle)
        aux_list[k++] = list[i++];
    while(j <= end)
        aux_list[k++] = list[j++];
    
    for(i = start, k = 0; i <= end; ++i, ++k)
        list[i] = aux_list[k];
    
    free(aux_list);
}

/* Divisão do merge sort (divisão dos vetores ate o caso base) */
void mergesort(SPOTIFY_LIST *list, int start, int end){
    if(end > start){
        int middle = start + (end - start)/2;

        mergesort(list, start, middle);
        mergesort(list, middle + 1, end);

        merge(list, start, middle, end);
    }
}

/* Chamada da função possibilitada na interface de usuário (arquivo .h) */
void sort_list_popularity(SPOTIFY_LIST *list, int n_artists){
    mergesort(list, 0, n_artists - 1);
}