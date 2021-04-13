// Bernardo Marques Costa - 11795551
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "track.h"
#include "knn.h"
#include "sort.h"

/*
    Função euclidian_distance:
    Parâmetros: first - primeira track
                second - segunda track
    É feito o cálculo da distancia euclidiana entre os atributos das tracks 'first' e 'second'
    O calculo é feito por:
        sqrt((x2-x1)^2 + (y2-y1)^2 ... + (z2-z1)^2)
    Além, cada célula possoui o id da segunda track, para que após a ordenação de cada linha da matriz com o radixsort, não percamos
    a referência do id da música referente à essa distancia da célula
   
    O.B.S: a ordem das linhas permanece igual, já que o que é ordenado são as colunas, assim, a referencia é feita as músicas
           de cada coluna
*/
static CELL euclidian_distance(TRACK *first, TRACK *second) {
    CELL new_cell;

    double acousticness_dist = (first->attributes->acousticness - second->attributes->acousticness) * (first->attributes->acousticness - second->attributes->acousticness);
    double danceability_dist = (first->attributes->danceability - second->attributes->danceability) * (first->attributes->danceability - second->attributes->danceability);
    double energy_dist = (first->attributes->energy - second->attributes->energy) * (first->attributes->energy - second->attributes->energy);
    double instrumentalness_dist = (first->attributes->instrumentalness - second->attributes->instrumentalness) * (first->attributes->instrumentalness - second->attributes->instrumentalness);
    double liveness_dist = (first->attributes->liveness - second->attributes->liveness) * (first->attributes->liveness - second->attributes->liveness);
    double loudness_dist = (first->attributes->loudness - second->attributes->loudness) * (first->attributes->loudness - second->attributes->loudness);
    double speechiness_dist = (first->attributes->speechiness - second->attributes->speechiness) * (first->attributes->speechiness - second->attributes->speechiness);
    double tempo_dist = (first->attributes->tempo - second->attributes->tempo) * (first->attributes->tempo - second->attributes->tempo);
    double time_sig_dist = (first->attributes->time_signature - second->attributes->time_signature) * (first->attributes->time_signature - second->attributes->time_signature);

    new_cell.distance = sqrt(acousticness_dist + danceability_dist + energy_dist + instrumentalness_dist + liveness_dist + loudness_dist + speechiness_dist + tempo_dist + time_sig_dist);
    new_cell.id = second->music->track_id;

    return new_cell;
}

/*
    Função create_matrix:
    Parâmetros: track_list - lista de tracks, contendo todas as musicas e seus dados
                num_tracks - número total de tracks obtido no arquivo csv passado
    Retorna a matriz de dissimilaridade construida
*/
DM *create_matrix(TRACK **track_list, int num_tracks) {
    
    DM *dissimilarity_matrix = calloc(1, sizeof(DM));
    dissimilarity_matrix->values = calloc(num_tracks, sizeof(CELL *));

    for(int i = 0; i < num_tracks; ++i) {
        dissimilarity_matrix->values[i] = calloc(num_tracks, sizeof(CELL));
        for(int j = 0; j < num_tracks; ++j)
            dissimilarity_matrix->values[i][j] = euclidian_distance(track_list[i], track_list[j]);
    }

    dissimilarity_matrix->size = num_tracks;

    return dissimilarity_matrix;
}

/*
    Função dm_delete:
    Parâmetros: dm - recebe o endereço da matriz de dissimilaridade
    Libera a memória utilizada pelo programa em relação a matriz de dissimilaridade e suas células
*/
void dm_delete(DM **dm) {
    if(*dm == NULL) return;
    
    int n = (*dm)->size;
    for(int i = 0; i < n; ++i)
        // Como as celulas correspondem a double e char * que serão ponteiros liberados posteriormente, 
        // podemos apenas deletar as referencias
        free((*dm)->values[i]); 
    
    free((*dm)->values);
    (*dm)->values = NULL;
    
    free(*dm);
    *dm = NULL;
}

/*
    Função print_most_similar_tracks:
    Parâmetros: dm - matriz de dissimilaridade
                id - track_id da música que deseja analisar a busca por similaridade
                K - número de vizinhos próximos
                tracks - lista de todas as tracks contidas no arquivo csv (está ordenada em relação ao id)
*/
void print_most_similar_tracks(DM *dm, char *id, int K, TRACK **tracks) {
    
    // Obtendo o índice na lista da música que desejamos verificar as K músicas mais similares
    int index_initial = track_binary_search(tracks, id, 0, dm->size - 1);
    
    // Caso tal id não exita na lista
    if(index_initial == -1) {
        printf("Não existe\n");
        return; 
    } 

    // Ordenando a linha buscada na matriz, ordenação das colunas de acordo com a distancia da linha à da coluna de maneira crescente
    radixsort256(dm->values[index_initial], dm->size);
    
    printf("----As %d musicas mais parecidas com %s sao:\n", K, tracks[index_initial]->music->track_name);
    
    // Iterando entre as K primeiras coluans da matriz de dissimilaridade em relação a linha analisada 
    for (int i = 0; i < K; ++i){
        // Obtendo o índice na lista de tracks o id da i-esima coluna da matriz de dissimilaridade em relação a 
        // linha (a linha representa a música que estamos procurando os vizinhos mais próximos) 
        int index = track_binary_search(tracks, dm->values[index_initial][i].id, 0, dm->size - 1);

        printf("\t(%d)Artista: %s\n", i, tracks[index]->artist->artist_name);
        printf("\t\tMusica: %s\n", tracks[index]->music->track_name);
        printf("\t\tDissimilaridade: %lf\n", dm->values[index_initial][i].distance);
        printf("\t\tLink: https://open.spotify.com/track/%s\n", tracks[index]->music->track_id);
    }
    printf("\n");   
}