/*
	ICMC - Instituto de Ciências Matemáticas e de Computação
	BCC - Bacharelado em Ciências de Computação

	MERGE SORT 3 VIAS
	
	Aluno: Bernardo Marques Costa
	Número USP: 11795551

*/

#include <stdio.h>
#include <stdlib.h>

#define BUFFER 128


typedef struct _book_list{
    char *title;
    double price;
}LIST;

typedef struct _library{
    LIST *book_list;
    int num_books;
}LIBRARY;  

// Leitura de buffer
char *readline(FILE *stream){
    char *string = NULL;
    int pos = 0, multiplier = 0;
    char character;
    do{
        if(pos % BUFFER == 0) string = realloc(string, (++multiplier) * BUFFER);
        character = (int) fgetc(stream);
        if(character != '\r')
            string[pos] = character;
        ++pos;
    }while(character != '\n' && !feof(stream));

    string = realloc(string, pos);
    string[pos-1] = '\0';
    return string;
}

// Particiona a entrada de dados obtida, obtendo o título e o preço da obra
void part_input(char **title, double *price){
    
    int end_pos = 0, comma_pos = 0, size = 0;
    
    comma_pos = 0;
    
    while((*title)[comma_pos] != ',' && (*title)[comma_pos] != '\0')
        ++comma_pos;
    
    end_pos = comma_pos + 1;
    
    while((*title)[end_pos] != '\0')
        ++end_pos;
    
    size = end_pos - comma_pos;
    
    char *price_in_strings = calloc(size, sizeof(char));

    int number_pos = comma_pos + 2;
    for(int i = 0, j = number_pos; i < size; ++i, ++j)
        price_in_strings[i] = (*title)[j];

    (*price) = atof(price_in_strings);

    (*title)[comma_pos] = '\0';
    *title = realloc((*title), comma_pos + 1); 

    free(price_in_strings);
}

// Imprime a lista dos preços dos livros
void print_book_list_price(LIST *l, int start, int end){
    for(int i = start; i < end; ++i)
        printf("%.2lf ", l[i].price);
    printf("\n");
}

// Imprime a lista de livros
void print_all_list(LIBRARY *b){
    printf("\n");
    for(int i = 0; i < b->num_books; ++i)
        printf("%s, R$%.2lf\n", b->book_list[i].title, b->book_list[i].price);
}

// Passo de conquista do algoritmo mergesort
void merge(LIBRARY *data, int start, int mid1, int mid2, int end){

    int i = start;
    int j = mid1;
    int k = mid2;

    int original_pos = 0;

    LIST *tmp_list = calloc(end - start, sizeof(LIST));

    while(i < mid1 && j < mid2 && k < end){
        if(data->book_list[i].price < data->book_list[j].price){
            if(data->book_list[i].price < data->book_list[k].price)
                tmp_list[original_pos++] = data->book_list[i++];
            else
                tmp_list[original_pos++] = data->book_list[k++];
        }
        else{
            if(data->book_list[j].price < data->book_list[k].price)
                tmp_list[original_pos++] = data->book_list[j++];
            else
                tmp_list[original_pos++] = data->book_list[k++];
        }
    }

    while(i < mid1 && j < mid2){
        if(data->book_list[i].price < data->book_list[j].price)
            tmp_list[original_pos++] = data->book_list[i++]; 
        else
            tmp_list[original_pos++] = data->book_list[j++];   
    }

    while(i < mid1 && k < end){
        if(data->book_list[i].price < data->book_list[k].price)
            tmp_list[original_pos++] = data->book_list[i++];
        else
            tmp_list[original_pos++] = data->book_list[k++];
    }

    while(j < mid2 && k < end){
        if(data->book_list[j].price < data->book_list[k].price)
            tmp_list[original_pos++] = data->book_list[j++];
        else   
            tmp_list[original_pos++] = data->book_list[k++];
    }

    while(i < mid1)
        tmp_list[original_pos++] = data->book_list[i++];
    
    while(j < mid2)
        tmp_list[original_pos++] = data->book_list[j++];
   
    while(k < end)
        tmp_list[original_pos++] = data->book_list[k++];


    for(i = start, j = 0; j < end - start; ++i, ++j)
       data->book_list[i] = tmp_list[j];  

    free(tmp_list);  
}

// Passo de divisão do algoritmo do mergesort
void mergesort(LIBRARY *data, int start, int end){
    
    if(end - start > 0) print_book_list_price(data->book_list, start, end);
    
    if(end - 1 <= start) return;
               
    
    int mid1 = start + (end - start + 2) / 3;
    int mid2 = start + (2 * (end - start) + 2) / 3; 


    mergesort(data, start, mid1);
    mergesort(data, mid1, mid2);
    mergesort(data, mid2, end);

    merge(data, start, mid1, mid2, end);
}

// Inicialização / Construtor da struct library
LIBRARY *init_library(){
    LIBRARY *new_library = NULL;
    
    new_library = calloc(1, sizeof(LIBRARY));
    new_library->book_list = NULL;
    new_library->num_books = 0;
    
    return new_library;
}

int main(int argc, char *argv[]){

    LIBRARY *data = init_library();

    scanf("%d ", &data->num_books);
    
    data->book_list = calloc(data->num_books, sizeof(LIST));

    for(int i = 0; i < data->num_books; ++i){ 
        data->book_list[i].title = readline(stdin);
        part_input(&(data->book_list[i].title), &(data->book_list[i].price));
    }   
    
    mergesort(data, 0, data->num_books);

    print_all_list(data);
	
    // Desalocação da memória utilizada no programa
    for(int i = 0; i < data->num_books; ++i)
        free(data->book_list[i].title);
    
    free(data->book_list);
    free(data);
    
    return 0;
}