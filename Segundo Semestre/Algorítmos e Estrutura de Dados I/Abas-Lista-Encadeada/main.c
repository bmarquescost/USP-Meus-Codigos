/*
    Disciplina: Algoritmos e estruturas de dados I
    Professor: Rudinei Goulart

    Código: Abas do navegador

    Aluno: Bernardo Marques Costa
    Número USP: 11795551
*/

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "tab.h"

#define BUFFER 512

// Reads a buffer
char *readline(FILE *stream){
    char c, *string = NULL;
    int pos = 0, multiplier = 0;
    do{
        if(pos % BUFFER == 0) string = realloc(string, (++multiplier)*BUFFER);
        c = (int) fgetc(stream);
        if(c != '\r') {
            string[pos] = c;
            pos++;
        }
    } while(c != '\n' && !feof(stream));
    string = realloc(string, pos * sizeof(char));
    string[pos - 1] = '\0';
    
    return string;
}

// Insert a new tab in the list
void insert_tab(LIST *l){
    char *title = readline(stdin);

    char *url = readline(stdin);

    TAB_DATA *tab = tab_create();
    
    tab_set_title(tab, title);
    tab_set_url(tab, url);
    
    list_push(l, tab);
}

// Change the position of an node of the list, based in tab's title parameter
void change_pos_tab(LIST *list){
    char *title = readline(stdin);
    int index = 0;

    char * index_string = NULL;    
    index_string = readline(stdin);
    
    index = atoi(index_string);
    
    if(!list_check_existence(list, title)){
        free(index_string);
        free(title);
        return;
    }

    if(index < 1) {
        free(index_string);
        free(title);
        return;
    }
    
    list_change_pos(list, title, index);

    free(index_string);
    free(title);
}


int main(int argc, char *argv[]){
    int command = 0;

    LIST *list = list_create();
    char *command_string = NULL;
    
    while(1){
        command_string = readline(stdin);
        command = atoi(command_string);

        while(command < 1 || command > 4){
            command_string = readline(stdin);
            command = atoi(command_string);
        }

        if(command == 1)
            insert_tab(list);
       
        else if(command == 2)
            change_pos_tab(list);

        else if(command == 3)
            list_print(list);

        else if(command == 4)
            break;

        free(command_string);
    }

    free(command_string);
    list_delete(&list);

    return 0;
}