/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    Curso : Bacharelado em Ciências de Computação

    Programa: IMPRIMINDO CHARS COMO INTEIROS

    Aluno : Bernardo Marques Costa
    Número USP : 11795551

    Programa que receberá do stdin uma quantidade de caracteres divisível por 4, e converterá, de 4 em 4 caracteres armazenados
    na memória, em um valor inteiro correspondente.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo um BUFFER que será utilizado para não ser necessários inúmeras realocações já que a quantidade de caracteres
// pode ser numerosa
#define BUFFER 4000

/*
    Função readAll:
    Recebe como um parâmetro o stdin.
    Realiza a leitura de todos os caracteres, desconsiderando eventuais ENTER ('\n') e '\r', não armazenando-os dentro
    da variável.
    A leitura termina quando encerra o arquivo de entrada (stdin).
*/
char *readAll(FILE *stream){
    char *string = (char*)calloc(BUFFER, sizeof(char));
    int pos = 0;
    int aux = 1;
    char character;
    while (!feof(stream)){     

        // Realocando a caso o número de caracteres esteja na iminência de ultrapassar o tamanho em bits alocados
        // na Heap para o vetor de caracteres. 
        if(!((pos + 1)%BUFFER)){
            string = (char*)realloc(string, (++aux)*BUFFER);
        }
        // Armazenando em um char auxiliar para capturar do buffer do teclado o caractere digitado.
        character = (int) fgetc(stream);
        
        // Desconsiderando '\n' ou '\r'.
        if (character != '\n' && character != '\r'){
            string[pos] = character;
            pos++;
        }
    }
    // Realocando o vetor para exatamente o número de bits que possui e alterando sua posição final para o '\0', delimitador do final
    // da cadeia de caracteres.
    string = (char*)realloc(string, pos);
    string[pos-1] = '\0';
    return string;
}

// Função compare, utilzida para a ordenação da função qsort (quicksort).
int compare(const void *a, const void *b){
    return (*(char*) a - *(char*)b);
}

int main (int argc, char *argv[]){
    
    // Ponteiro que receberá o endereço inicial na Heap de onde começa todo os caracteres digitados. 
    char *input = NULL;
    input = readAll(stdin);
   
    // Função de ordenação dos elementos:
    // -> É necessário utilizar o qsort pois a entrada dos casos teste pode chegar à 40.000 caracteres, sendo necessário
    //    um algoritmo rápido de ordenação, suficiente para não resultar em time limit exceeded.
    qsort(input, strlen(input), sizeof(char), compare);


    // Subdivisão que conterá 4 caracteres e será usado para subdividir o input, e será "convertido" para inteiro.
    unsigned char *subdivision = (unsigned char *) calloc(4, sizeof(char));
    // "Cursor", sinalizando em que posição se encontra no input inicial a análise.
    int pos = 0;
    // Variável unsigned int que receberá a subdivisão como ponteiro de inteiro
    unsigned int number;

    //Realizando o laço até o final do input.
    while(pos < strlen(input)){

        // Armazenando de 4 em 4 caracteres no vetor de subdivisão.
        for(int i = 0; i < 4; i++){
            subdivision[i] = input[pos];
            pos++;  
        }

        // Realizando a conversão com casting.
        number = *(unsigned int*)subdivision;

        // Imprimindo o número obtido em cada laço.
        printf("%u\n", number);
    }

    // Desalocando a memória Heap utilizada no programa.
    free(input);
    free(subdivision);

    return 0;
}