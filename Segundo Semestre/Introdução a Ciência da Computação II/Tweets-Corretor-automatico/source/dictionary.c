/*
    Introdução a Ciência da Computação II
    Moacir Ponti 

    Aluno: Bernardo Marques Costa
    nUSP: 11795551

    Biblioteca com funções para criação do dicionário, utilizando da estrutura trie
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "trie.h"
#include "dictionary.h"

/*
    Recebe o nome de um arquivo onde será lido todas as palavras que serão armazenadas no dicionário
    Constrói a estrutura de dados trie, retornando-a 
*/
TRIE *read_and_create_trie(char *filename) {
    char *book_filepath = create_filepath(filename, BOOKS_PATH);

    FILE *fp = NULL;
    if(!(fp = fopen(book_filepath, "r"))) {
        printf("Erro na abertura do arquivo %s\n", filename);
        exit(1);
    }

    int amnt_lines = num_of_lines(fp);

    char *aux_line = NULL;
    char **aux_list_strings = NULL;
    int amnt_parsed_strings = 0;

    TRIE *dictionry_trie = trie_create();

    for(int i = 0; i < amnt_lines; ++i) {
        aux_line = readline(fp);
        aux_list_strings = parse_line(aux_line, &amnt_parsed_strings); 

        // Inserindo de cada linha do arquivo, string a string na estrutura trie
        for(int j = 0; j < amnt_parsed_strings; ++j) {
            trie_insert_string(dictionry_trie, aux_list_strings[j]);
            free(aux_list_strings[j]);
        }
        
        free(aux_list_strings);
        free(aux_line);
    }
    
    free(book_filepath);
    fclose(fp);
    return dictionry_trie;
}