/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    BCC - Bacharelado em Ciências de Computação

    COMPARAÇÃO DE MATRIZES

    - Insertion sort x Bubble sort x Merge Sort

    Aluno: Bernardo Marques Costa
    Número USP: 11795551

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "filemanager.h"
#include "sortalgoritm.h"

#define N_EXECUTION 10

enum algoritm {BUBBLE = 1, INSERTION, MERGE};

void print_words(char **words, int n){
    for(int i = 0; i < n; ++i)
        printf("%s\n", words[i]);
}

int main(int argc, char *argv[]){
    
    char filename[20];
    int sort_type = 0;

    scanf("%s %d", filename, &sort_type);
        
    int num_words = 0;
    
    char **txt = read_file(filename, &num_words);

    // Parte do trabalho: Run.codes
    #ifndef DEBUG
        if(sort_type == BUBBLE)
            bubblesort(txt, num_words);
        
        else if(sort_type == INSERTION)
            insertionsort(txt, num_words);
        
        else if(sort_type == MERGE)
            mergesort(txt, 0, num_words - 1);

        print_words(txt, num_words);
    #endif

    // Parte do trabalho: relatório e obtenção de dados
    #ifdef DEBUG
        clock_t startTime = 0, endTime = 0;
        double averageTime = 0;
       
        for(int i = 0; i < N_EXECUTION; ++i){

            // Reinicio o vetor desordenado
            char **aux = calloc(num_words, sizeof(char*));
            for(int j = 0; j < num_words; ++j){
                aux[j] = calloc(strlen(txt[j]) + 1, sizeof(char));
                strcpy(aux[j], txt[j]);    
            }

            startTime = clock();
            if(sort_type == BUBBLE){
                printf("Bubble iniciado\n");
                bubblesort(aux, num_words);
                printf("Bubble finalizado\n");
            }

            else if(sort_type == INSERTION){
                printf("Insertion iniciado\n");
                insertionsort(aux, num_words);
                printf("Insertion finalizado\n");
            }
            
            else if(sort_type == MERGE){
                printf("Merge iniciado\n");
                mergesort(aux, 0, num_words - 1);
                printf("Merge finalizado\n");
            }
            endTime = clock();

            averageTime += getExecutionTime(startTime, endTime);

            for(int j = 0; j < num_words; ++j)
                free(aux[j]);
            free(aux);
        }

        averageTime = averageTime / (double) N_EXECUTION;

        saveTimeDataIntoFile(sort_type, filename, averageTime, 10);

    #endif

    for(int i = 0; i < num_words; ++i) free(txt[i]);
    free(txt);

    return 0;
}