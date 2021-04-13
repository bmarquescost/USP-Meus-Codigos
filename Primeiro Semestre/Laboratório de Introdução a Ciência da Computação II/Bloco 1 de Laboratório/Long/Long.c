/*
    LONG 
    ALUNO: Bernardo Marques Costa
    NÚMERO USP: 11795551
    ICMC Bacharelado em Ciência da Computação

    Exercício de verificação em hexadecimal byte a byte dos 8 bytes que compõem um valor do tipo long int.

*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv []){
    
    unsigned char *ponteiro;   //Declarando um ponteiro do tipo unsigned char que irá percorrer os 8 bytes da memória em que estão alocados o long long int.

    long number;      //Declarando o numero to tipo long.
    
    scanf ("%ld", &number);  //Lendo do teclado o numero escolhido

    //Ponteiro recebendo o endereço do número, sendo este o primeiro endereço da memória no qual está armazenado o primero byte (8 bits) do valor long
    //O casting de unsigned char é feito para que seja interpretado um padrão de funcionamento de leitura deste ponteiro, identificando assim um monitoramento de 8 em 8 bytes.
    ponteiro =  (unsigned char *) &number;  

    //Laço de repetição que rodará até o tamanho total do long long int (8 bytes), sendo que a cada iteração o ponteiro irá ser somado de i, acessando o valor que está armazenado 
    //neste respectivo endereço de 1 byte na memória, e convertendo-o para hexadecimal. 
    for (int i = 0; i < sizeof(long); i++){
        printf ("%x\n", *(ponteiro+i));
    }
    
    return 0;
}
