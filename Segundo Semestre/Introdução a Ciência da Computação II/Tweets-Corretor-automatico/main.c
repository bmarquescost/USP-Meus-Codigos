/*
    Introdução a Ciência da Computação II
    Moacir Ponti 

    Aluno: Bernardo Marques Costa
    nUSP: 11795551
*/

#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "trie.h"
#include "dictionary.h"
#include "json.h"
#include "menu.h"

int main(int argc, char *arv[]) {
    TRIE *dictionary = create_dictionary_from_books();
    JSON_DATA *json = json_construct_from_tweet();
    speel_check_tweet(dictionary, json);
    free_memory(dictionary, json);
    
    return 0;
}