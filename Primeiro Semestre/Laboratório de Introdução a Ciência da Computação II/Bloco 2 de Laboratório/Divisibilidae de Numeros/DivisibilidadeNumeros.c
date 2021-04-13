/*
    DIVISIBILIDADE DE NUMEROS
    ALUNO: Bernardo Marques Costa
    NÚMERO: 11795551
*/

#include <stdio.h>
#include <stdlib.h>

int main (){
    long numeros [31], resto;             //Definindo as variaveis inteira: vetor com 31 termos e resto.

    for (int i = 0; i < 31; i++){         //Laço de repetição para preencher o vetor dos números desejados.
        scanf ("%ld", &numeros [i]);
    }
    /*
    
    Agora será realizado o processo de verificação de divisores: cada elemento do vetor (desde a posição 0 até a 29)
    será divido pelo número que esta armazenado na posição 30 do vetor.
    Caso o resto de sua divisão dê 0, teremos então que este número é divisível, 
    e assim ocorrerá a impressão deste na tela, continuando a sequência até o fim do laço de repetição.
   
    */
    for (int j = 0; j < 30; j ++){              
        resto = numeros [j] % numeros[30];
        if (resto == 0){
            printf ("%ld", numeros[j]);
        }
    } 



    return 0;
}