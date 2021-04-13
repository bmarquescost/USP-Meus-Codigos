/*
    Introdução a Ciência da Computação II
    Moacir Ponti 

    Aluno: Bernardo Marques Costa
    nUSP: 11795551

    Funções básicas para leitura de linhas, parseamento, limpeza, etc.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

/*
 Leitura de uma linha completa
*/
char *readline(FILE *stream) {
    char *string = NULL, character;
    int pos = 0, multiplier = 1;
    do {
        if(pos % BUFFER == 0) string = realloc(string, BUFFER * (multiplier++));
        character = fgetc(stream);
        if(character != '\r'){
            string[pos++] = character;
        }
    } while(character != '\n' && !feof(stream));
    
    string = realloc(string, pos);
    string[pos-1] = '\0';
    
    return string;
}

/*
    Limpeza de uma linha, trocando cada caractere não alfabético por espaço
*/
void clear_line(char *line) {
    for(int i = 0; i < strlen(line); ++i)
        if(!(line[i] >= 'A' && line[i] <= 'Z') &&  !(line[i] >= 'a' && line[i] <= 'z'))
            line[i] = ' ';
} 

/*
    Recebe o nome do arquivo buscado, concatenando com o nome do diretório em que os arquivos são armazenados
*/
char *create_filepath(char *filename, char *directory_pathname) {
    int path_strlen = strlen(filename) + strlen(directory_pathname) + 1;
    
    char *path = calloc(path_strlen, sizeof(char));
    strcat(path, directory_pathname);
    strcat(path, filename);
    
    return path;
}

/*
    Função de parseamento de linha:
    Recebe uma linha e o endereço de inteiro que irá armazenar o número de strings da nova lista de strings criada
*/
char **parse_line(char *line, int *num_strings) {
    if(line == NULL) return NULL;
    
    clear_line(line); // Limpando a linha inteira

    *num_strings = 0;
    char **string_list = NULL;
    
    int line_size = strlen(line);
    
    int line_counter = 0;
    while(line_counter < line_size) {
        string_list = realloc(string_list, ((*num_strings) + 1) * sizeof(char *));
        
        string_list[*num_strings] = calloc(45, sizeof(char)); // Alocando o tamanho padrão de 45 caracteres
        
        // Copiando caractere a caractere 
        int num_characters = 0;
        while(line[line_counter] != ' ' && line[line_counter] != '\0') {
            string_list[*num_strings][num_characters] = line[line_counter];
            
            // Trocando o espaço da linha pelo indicador de final de linha
            if(string_list[*num_strings][num_characters] == ' ') 
                string_list[*num_strings][num_characters] = '\0';

            num_characters++;
            line_counter++;
        };

        // Caso a string que acaba de ser obtida seja nula (null) é liberada a memória e realocado a lista de strings
        if(string_list[*num_strings][0] == '\0'){
            free(string_list[*num_strings]);
            string_list = realloc(string_list, ((*num_strings)) * sizeof(char*));
        }
        else
            (*num_strings)++;
        
        line_counter++;
    }

    return string_list;
}

/*
    Retorna o número de linhas de um arquivo dado como parâmetro
*/
int num_of_lines(FILE *file) {
    int current = ftell(file);

    char character;
    
    int amnt_lines = 0;
    while(!feof(file)) {
        character = fgetc(file);
        if(character == '\n' || character == EOF) 
            ++amnt_lines;
    }

    fseek(file, current, SEEK_SET);

    return amnt_lines;
}