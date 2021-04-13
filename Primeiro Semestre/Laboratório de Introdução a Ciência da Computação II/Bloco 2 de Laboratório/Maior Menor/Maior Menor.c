/*  
    PROGRAMA MAIOR E MENOR NUMEROS DE UMA SEQUENCIA
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    long int n;             //Definindo como long int uma variavel n que recebera o numero de termos a serem escritos.
    long int maior, menor;  //Definindo duas variaveis que serao utilizadas mais a frente que representarao o menor e o maior termo da sequencia 
    scanf ("%ld", &n);      //Requisitando a digitação e enderençando o numero recolhido na variavel.
    long int vector [n];    //Criando um vetor do tipo inteiro com n termos.
    int i;                  //Definindo o termo de iteração
    
    //Preenchendo o vetor com os numeros desejados.

    for ( i = 0; i < n; i++){
            scanf ("%ld", &vector[i]);
    }
    int j; //Defnindo a variavel para a proximo laço de reptiçao
    
    //Agora sera realizada a avaliaçao dos termos e verificar quais sao o menor e o maior termo.
    for ( j = 0; j < n; j++){
        if ( j == 0 ){
            maior = menor = vector [j];  //Quando iniciar o processo, o primeiro termo da sequencia será tanto o menor quanto o maior termo, inciando o processo de comparação posteriormente.
        }
        else {
            if (vector [j] < menor) menor = vector [j]; 
            else if (vector [j] > maior) maior = vector [j];
        }   
       }
    printf ("max: %ld \nmin: %ld\n", maior,menor); //Printando os maiores valores e os menores valores.

    return 0;
}