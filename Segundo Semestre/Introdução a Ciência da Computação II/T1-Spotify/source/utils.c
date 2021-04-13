// Bernardo Marques Costa - 11795551

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "string.h"

/*
    Realiza a leitura de buffer
*/
char *readline(FILE *stream){
    char c, *string = NULL;
    int pos = 0, multiplier = 0;
    do{
        if(pos % BUFFER_SIZE == 0) string = realloc(string, (++multiplier)*BUFFER_SIZE);
        c = (int) fgetc(stream);
        if(c != '\r'){
            string[pos] = c;
            ++pos;
        }
    }while(c != '\n' && !feof(stream));
    
    string = realloc(string, pos);
    string[pos - 1] = '\0';

    return string;
}

/*
    Particiona a string obtida pelo arquivo CSV, a partir de uma posição (start) até o caractere 
    delimitador (TOKEN : ';').                                                                   
*/
char *part_string(char *string, int start, boolean *is_end){
    
    int end = start;

    while(string[end] != TOKEN && string[end] != '\0')
        end++;

    if(string[end] == '\0') *is_end = TRUE;

    int tamanho_auxiliar = end - start + 2;

    char *auxiliar = calloc(tamanho_auxiliar, sizeof(char));
    
    for(int i = start, j = 0; i < end; ++i, ++j)
        auxiliar[j] = string[i]; 

    return auxiliar;
}

/*
    Realiza a leitura do arquivo CSV completo, recebendo como parâmetros o nome do arquivo CSV  
    em que será feita a leitura, recebe também por referência variável que armazena o total de 
    tracks (faixas) que o arquivo CSV possui                                                    
*/
char **read_csv(char *csv_filename, int *num_tracks){
    FILE *csv_handle = NULL;
    
    if(!(csv_handle = fopen(csv_filename, "r"))){
        printf("Erro na abertura do arquivo CSV\n");
        return NULL;
    }
    
    char caracter;
    int num_rows = 0;
    while(!feof(csv_handle)){
        caracter = fgetc(csv_handle);
        if(caracter == '\n') // É necessário uma quebra de linha ao final de cada um dos dados que desejamos armazenar.
            ++num_rows;
    }

    // Descontando a linha que descreve o título de cada coluna
    --num_rows; 

    char **csv_data = NULL;
    csv_data = calloc(num_rows, sizeof(char* ));
    
    fseek(csv_handle, 0, SEEK_SET);

    char *columns_header = readline(csv_handle);
    free(columns_header);
    
    for(int i = 0; i < num_rows; ++i)
        csv_data[i] = readline(csv_handle);

    *num_tracks = num_rows;
    
    fclose(csv_handle);
    
    return csv_data;    
}