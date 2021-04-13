/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    Curso : Bacharelado em Ciências de Computação

    Programa : NOME BIBLIOGRÁFICO

    Aluno : Bernardo Marques Costa
    Número USP: 11795551

    Programa que receberá um input de um nome, convertendo-o ao padrão de representação bibliográfica:
        input : João Guimarães Rosa 
        Output : ROSA, João Guimarães
*/

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


/* 
    Função readline:
    Recebe como parâmetro o stdin.
    Retorna um ponteiro para uma string na memória Heap
*/
char *readline(FILE *stream){
    char *string = NULL;
    int pos = 0;
    do {
        string = (char*)realloc(string, pos+1);
        string[pos] = fgetc(stream);
        pos++;
    } while(string[pos-1] != '\n' && string[pos-1] != '\0' && !feof(stream));
    string[pos-1] = '\0';
    return string;
}


int main (int argc, char * argv[]){
    char *name = NULL;   // String que corresponde ao nome completo digitado
    char *bibliografic = NULL;  // String que corresponde ao nome no formato bibliográfico
    char *lastname = NULL;  // String que armazenará o sobrenome.

    // Recebendo o input do nome completo.
    name = readline(stdin);


    int space_at = 0;   // Variável que armazenará a posição onde está o último espaço no nome (antes do sobrenome final).
    int i = strlen(name) - 2;       // Inicializando i com o tamanho do nome - 2 (correspondente ao \r\n).
    while(name[i] != ' '){
        i--;
    }
    
    space_at = i; // O espaço então estará na posição i.

    int k; 
    // Criando o vetor do sobrenome: i é iniciado logo após o espaço, associando para cada posição do vetor lastname o char
    // convetido para maiúsculo no vetor name na posição i.
    for (i = space_at + 1, k = 0; i < strlen(name) - 1; i++, k++){
        lastname = (char*)realloc(lastname, k+1);
        lastname[k] = (char) toupper(name[i]);
    }

    // Criando o vetor do nome em formato bibliográfico
    for (i = 0; i < k; i++){
        bibliografic = (char*)realloc(bibliografic, i+1);
        bibliografic[i] = lastname[i];
    }

    // Acrescentado os caracteres ',' e ' ' logo apos o sobrenome.
    bibliografic = realloc(bibliografic, i+1);
    bibliografic[i] = ',';
    bibliografic[i+1] = ' ';
   

    int size = strlen(bibliografic);  
    
    // Os caracteres do nome, desde a posição 0 até a última posição, em que se encontra o espaço, serão adicionados
    // no vetor bibliografic na posição após o ultimo caractere (' ') acrescentado. 
    for (i = size, k = 0; k < space_at; i++, k++){
        bibliografic = (char*)realloc(bibliografic, size+k);
        bibliografic[i] = name[k];
    }
    // Realocando e acrescentando o NULL.
    bibliografic = realloc(bibliografic, size + k);
    bibliografic[size+k] = '\0';
    
    printf("%s\n", bibliografic);

    // Liberando a memória Heap utilizada.
    free(bibliografic);
    free(lastname);
    free(name);
    
    return 0;
}