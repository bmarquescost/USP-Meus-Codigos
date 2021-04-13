/*
    Aluno: Bernardo Marques Costa
    Número USP: 11795551
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubblesort(char **words, int num_words){
    char *aux_word = NULL;
    for(int i = 0; i < num_words; ++i){
        for(int j = 0; j < num_words - i - 1; ++j){
            int comp = strcmp(words[j],words[j+1]);
            if(comp < 0){
                aux_word = words[j];
                words[j] = words[j+1];
                words[j+1] = aux_word;
            }
        }
    }
}

void insertionsort(char **words, int num_words){
    int i = 1;
    while(i < num_words){
        char *aux_word = words[i];
        int j = i - 1;
        while(j >= 0 && strcmp(aux_word, words[j]) > 0){
            words[j+1] = words[j];
            --j;
        }
        words[j+1] = aux_word;
        ++i;
    }
}

void merge(char **words, int start, int middle, int end){
    char **tmp_matrix = calloc(end - start + 1, sizeof(char*));
    int i = start;
    int j = middle + 1;
    int k = 0;

    while(i <= middle && j <= end){
        if(strcmp(words[i], words[j]) > 0)   
            tmp_matrix[k++] = words[i++];
        else
            tmp_matrix[k++] = words[j++];
    }

    while(i <= middle)
        tmp_matrix[k++] = words[i++];
    while(j <= end)
        tmp_matrix[k++] = words[j++];

    for(i = start, k = 0; i <= end; ++i, ++k)
        words[i] = tmp_matrix[k];
    
    free(tmp_matrix);
}


void mergesort(char **words, int start, int end){
    if(start < end){
        int middle = start + (end - start)/2;

        mergesort(words, start, middle);
        mergesort(words, middle + 1, end);

        merge(words, start, middle, end);
    }
}