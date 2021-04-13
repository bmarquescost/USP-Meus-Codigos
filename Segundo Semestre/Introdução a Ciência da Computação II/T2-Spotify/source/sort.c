// Bernardo Marques Costa - 11795551
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "track.h"
#include "knn.h"

/*
    Função random_pivot:
    Parâmetros: low - início
                high - final
    Retorna um inteiro correspondente a um índice aleatório no vetor, possibilitando uma maior eficiência para
    o algoritmo quicksort
*/
static int random_pivot(int low, int high) {
    return (int) (rand() % (high - low)) + low;
}

/*
    Função quicksort
    Parâmetros: v - vetor de TRACKS
                start - inicio do vetor
                end - final do vetor
    Realiza recursivamente a ordenação de forma crescente por track_id o vetor de TRACKS
*/
void quicksort(TRACK **v, int start, int end) {
    if(start >= end) return;

    // Recebendo um pivo aleatório
    int pivot = random_pivot(start, end);
    
    TRACK *tmp = v[pivot];
    v[pivot] = v[start];
    v[start] = tmp;

    pivot = start;
    int i = start + 1;
    int j = end;

    while(i <= j) {
        while(i <= end && strcmp(v[i]->music->track_id, v[pivot]->music->track_id) <= 0) ++i;
        while(strcmp(v[j]->music->track_id, v[pivot]->music->track_id) > 0) --j;
        
        if(j > i) {
            tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;
        }
    }

    tmp = v[pivot];
    v[pivot] = v[j];
    v[j] = tmp;
    
    pivot = j;

    quicksort(v, start, pivot - 1);
    quicksort(v, pivot + 1, end);
}


/*
    Função radixsort256:
    Parâmetros: v - vetor desordenado de células, correspondnente à uma linha intera da matriz de dissimilaridade
                N - tamanho do vetor
    Realiza a ordenação crescente de uma linha inteira da matriz de dissimilaridade em relação as distância entre as música
*/
void radixsort256(CELL *v, int N) {
    // Utilizando base 256 para a ordenação
    int counting[256] = {0};
    int position[256];

    CELL *copy_array = calloc(N, sizeof(CELL));

    int P = 1000000; // Forma de contornar o fato da chave ser double, ou seja, não ser discreta

    for(int shift = 0; shift <= 24; shift += 8) {
        for(int j = 0; j < N; ++j) {
            short k = ( (int) (v[j].distance * P) >> shift ) & 255;
            counting[k]++;
            copy_array[j] = v[j];
        }
        position[0] = 0;
       
        for(int i = 1; i < 256; ++i) {
            position[i] = position[i-1] + counting[i-1];
            counting[i-1] = 0;
        }

        for(int j = 0; j < N; ++j) {
            short k = ( (int)(copy_array[j].distance * P) >> shift ) & 255;
            v[position[k]] = copy_array[j];
            position[k]++;
        }
    }

    free(copy_array);
}