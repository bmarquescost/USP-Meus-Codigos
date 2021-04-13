/*
    TROCO EM MOEDAS
    ALUNO: Bernardo Marques Costa
    NÚMERO USP: 11795551

    ICMC - Bacharelado em Ciências de Computação

    Programa que recebe um número inteiro correspondente a um valor em reais.
    O programa realizará a contabilização do troco em moedas de 1 real, 50 centavos, 25 centavos, 10 centavos, 5 centavos e 1 centavo.
*/

#include <stdio.h>
#include <stdlib.h>

//Função de cálculo do troco.
int* calculo(int valor){

    int *vetor_valores;     //Vetor que armazenará a quantidade de moedas de cada um dos valores.

    vetor_valores = (int*)calloc(6, sizeof(int));   //Alocando na memória heap 
    
    //Cálculo em ordem de maior valor de moeda para menor, divindo o valor total pelo valor em centavos --> a divisão resulta na quantidade 
    //desta moeda para o troco, uma vez que se trata de um inteiro.
    //Em seguida, o próximo valor a ser considerado nas próximas linhas é a diferença do valor total inicial com a resposta da divisão pelo moeda, ou seja,
    //o módulo da divisão.
    
    vetor_valores[0] = valor/100;
    valor = valor % 100;

    vetor_valores[1] = valor/50;
    valor = valor%50;

    vetor_valores[2] = valor/25;
    valor = valor%25;

    vetor_valores[3] = valor/10;
    valor = valor%10;

    vetor_valores[4] = valor/5;
    valor = valor%5;

    vetor_valores[5] = valor/1;
    valor = valor%1;

    
    //Retornando o tipo ponteiro de inteiros armazenado na heap para que o vetor seja manipulado por meio do ponteiro declarado na função main.
    return vetor_valores;

}

int main (){    

    long int dinheiro;  

    int *vetor_resposta;  //Ponteiro do tipo inteiro que servirá de vetor para armazenar a quantidade de cada uma das moedas.

    scanf ("%li", &dinheiro);      //Recebendo do teclado o valor do dinheiro que receberá a contagem do troco.

    vetor_resposta = (int*) calculo(dinheiro);  //Recebendo o retorno da função calculo que contabilizará o troco, enviando como parâmetro o valor digitado.


    
    //Printando os resultados de cada um dos valores de moedas: cada posição do vetor armazena a contagem de moedas na ordem de 1 real, 50 cetavos,
    //25 centavos, 10 centavos, 5 centavos e 1 centavo respectivamente.
    printf ("O valor consiste em %d moedas de 1 real\n", vetor_resposta[0]);
    printf ("O valor consiste em %d moedas de 50 centavos\n", vetor_resposta[1]);
    printf ("O valor consiste em %d moedas de 25 centavos\n", vetor_resposta[2]);
    printf ("O valor consiste em %d moedas de 10 centavos\n", vetor_resposta[3]);
    printf ("O valor consiste em %d moedas de 5 centavos\n", vetor_resposta[4]);
    printf ("O valor consiste em %d moedas de 1 centavo\n", vetor_resposta[5]);

    //Liberanado as posições na  memória Heap em que estava o vetor. 
    free(vetor_resposta);
    
    return 0;
}