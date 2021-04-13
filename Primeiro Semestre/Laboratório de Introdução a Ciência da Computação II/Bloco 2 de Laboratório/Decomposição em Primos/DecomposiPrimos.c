/*
    DECOMPOSIÇÃO EM PRIMOS
    ALUNO: Bernardo Marques Costa
    NÚMERO USP: 11795551

    Programa que recebe um número inteiro qualquer e decompõe este valor em números primos, demonstrando suas multiplicidades.
*/

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]){
    
    int valor, cont = 0;  //Declarando as variáveis inteiras valor e cont.
    
    scanf ("%d", &valor);  //Recebendo do teclado e armazenando o número escolhido na variável valor.
    

    //Itereação que irá ocorrer até que o valor seja dividido consecutivamente e resulte em 1, chegando ao final da fatoração.
    //A variável i de iteração irá dividir até que o número não seja mais divisível por tal valor de i, sendo contado a partir da variável cont
    //o total de vezes que foi possível a divisão.
    //O i irá aumentar em 1 a cada momento que se chega em um novo valor não divisível por i.
   
    for (int i = 2; valor != 1 ; i++){
        cont = 0;
        if (valor%i == 0){
            while (valor % i == 0){
            valor = valor/i;
            cont ++;
            }
        }
        
        //Caso o contador seja diferente de 0, ocorrerá a impressão.
        if (cont != 0){
        printf ("%d %d\n", i, cont);
        }
    }

    return 0;
}