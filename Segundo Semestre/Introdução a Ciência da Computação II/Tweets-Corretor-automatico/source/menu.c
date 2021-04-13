/*
    Introdução a Ciência da Computação II
    Moacir Ponti 

    Aluno: Bernardo Marques Costa
    nUSP: 11795551

    Funcionalidades básicas do programa de spellchecker
*/

#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "trie.h"
#include "dictionary.h"
#include "json.h"

/*
    Construção do dicionário
*/
TRIE *create_dictionary_from_books(void) {
    char *dict_from_book = readline(stdin);
    TRIE *dictionary = read_and_create_trie(dict_from_book);
    free(dict_from_book);
    return dictionary;
}

/*
    Construção do json do tweet, com todos os campos texts
*/
JSON_DATA *json_construct_from_tweet(void) {
    char *tweet_name = readline(stdin);
    JSON_DATA *json_tweet = json_from_tweet(tweet_name);
    free(tweet_name);
    return json_tweet;
}

/*
    Verificação das palavras do tweet com as palavaras do dicionário
*/
void speel_check_tweet(TRIE *dict, JSON_DATA *js) {
    if(js == NULL) {
        printf("No tweets to check\n");
        return;
    }
    
    for(int i = 0; i < js->amnt_texts; ++i) {
        for(int j = 0; j < js->texts[i].amnt_strings; ++j) 
            if(!trie_search_word(dict, js->texts[i].string_list[j])) 
                printf("%s ", js->texts[i].string_list[j]);
        printf("\n");
    }
}

/*
    Liberando a memória utilizada pelo programa
*/
void free_memory(TRIE *dict, JSON_DATA *js) {
    trie_delete(&dict);
    json_delete(js);
}