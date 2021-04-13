/*
    Introdução a Ciência da Computação II
    Moacir Ponti 

    Aluno: Bernardo Marques Costa
    nUSP: 11795551

    Biblioteca com funções relaciondas ao JSON do tweet 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "json.h"

/*
    Criação de uma instância json
*/
JSON_DATA *json_create(void) {
    JSON_DATA *new_json = calloc(1, sizeof(JSON_DATA));
    new_json->texts = NULL;
    new_json->amnt_texts = 0;
    return new_json;
}

/*
    Deleta uma struct completa json
*/
void json_delete(JSON_DATA *json) {
    if(json == NULL) return;

    for(int n_texts = 0; n_texts < json->amnt_texts; ++n_texts) {
        
        for(int n_strings = 0; n_strings < json->texts[n_texts].amnt_strings; ++n_strings)
            free(json->texts[n_texts].string_list[n_strings]);
        free(json->texts[n_texts].string_list);
    }

    free(json->texts);

    free(json);
}

/*
    Realiza a leitura de uma chave de um arquivo json
    A leitura é feita entre os caracteres aspas "
    Retorna a string entre as aspas
*/
static char *json_read_quoted_key(FILE *json) {
    char *key = calloc(BUFFER, sizeof(char));
    
    char character = '\0';
    int num_chars = 0;
    while(character != '"' && !feof(json)) {
        character = fgetc(json);
        if(character == '"') {
            do {
                character = fgetc(json);
                key[num_chars] = character;
                ++num_chars;
            } while(character != '"' && !feof(json));

            key[num_chars - 1] = '\0';
        }            
    }
    key = realloc(key, num_chars * sizeof(char));

    return key;
}

/*
    Realiza a leitura do valor de um campo de um arquivo json
    A leitura é feita entre os caracteres " e o final da linha '\n', já que pode existir uma aspas no texto
    sem ser indicativa do final do conteúdo
*/
static char *json_read_quoted_value(FILE *json) {
    char *value = calloc(BUFFER, sizeof(char));
    char character = '\0';
    int num_chars = 0;
    
    fseek(json, 3, SEEK_CUR); // Pulando os caracteres ':', ' ', e '"' para realiza a leitura corretamente 

    while(character != '\n' && !feof(json)) {

        character = fgetc(json);
        if(character == '"') {
            char check_comma = fgetc(json);
            char check_end_line = fgetc(json);
            if(check_comma == ',' && check_end_line == '\n') {
                value[num_chars] = '\0';
                break;
            }
            else 
                fseek(json, -2, SEEK_CUR);
        }
        value[num_chars++] = character;
    }

    value = realloc(value, (num_chars + 1)* sizeof(char));
    
    return value;
}

/*
    Constrói a estrutura json a partir de um arquivo json
*/
JSON_DATA *json_from_tweet(char *filename) {
    char *tweet_filepath = create_filepath(filename, TWEET_PATH);
    
    FILE *fp = NULL;
    if(!(fp = fopen(tweet_filepath, "r"))) {
        printf("Erro na abertura do arquivo %s\n", filename);
        free(tweet_filepath);
        exit(1);
    }

    int amnt_lines = num_of_lines(fp);

    JSON_DATA *json_data = json_create();

    for(int i = 0; i < amnt_lines && !feof(fp); ++i) {
        char *json_key = json_read_quoted_key(fp);
        
        if(!strcmp(json_key, "errors")) {
            fclose(fp);
            free(tweet_filepath);
            free(json_key);
            free(json_data);
            return NULL;
        }

        if(!strcmp(json_key, "text")) {
            json_data->texts = realloc(json_data->texts, (json_data->amnt_texts+1) * sizeof(JSON_TEXT));
            char *json_text_value = json_read_quoted_value(fp);
            
            json_data->texts[json_data->amnt_texts].string_list = parse_line(json_text_value, &json_data->texts[json_data->amnt_texts].amnt_strings);
            free(json_text_value);      
            
            ++json_data->amnt_texts;                
        }
        free(json_key);
    }

    fclose(fp);
    free(tweet_filepath);
    return json_data;
}

/*
    Realiza a impressão de todos os tweets (não é utilizada no programa principal) 
*/
void json_print_everything(JSON_DATA *js) {
    if(js == NULL) {
        printf("No tweets to check\n");
        return;
    }
    for(int i = 0; i < js->amnt_texts; ++i)
        for(int j = 0; j < js->texts[i].amnt_strings; ++j)
            printf("%s\n", js->texts[i].string_list[j]);
}