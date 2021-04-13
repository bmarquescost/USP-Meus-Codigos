/*
    MEDIA HARMÔNICA AMORTIZADA
    ALUNO: Bernardo Marques Costa
    NÚMERO USP: 11795551
    
*/


#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]){

    int trabalhos;                          //Declarando inteira a variável que receberá o total de trabalhos.             

    double *notas, media, denominador;      //Declarando notas que será um ponteiro do tipo double que servirá como um vetor armazenado na heap para armazenar as notas dos trabalhos.
                                            //Declarando também a media e o denominador que servirão para o calculo final da média.
    scanf ("%d", &trabalhos);               
    //Recebendo do teclado o número de trabalhos que serão contabilizados.
    
    notas = (double *)calloc (trabalhos,sizeof(double));  
    //A variável notas receberá o endereço na memória heap em que serão armazenados um número de bits equivalente à trabalho(variável) * 8 (tamanho de um double)
    //A função calloc ainda preenche todas os espaços da memória de 8 em 8 bits com o valor 0.

    //Iteração que lerá as notas e armazenará nas posições respectivas como de um vetor dentro da memória heap.
    //Ainda, ocorre o cálculo que totalizará no denominador final que dividirá trabalho no cálculo final da média.
    for (int i = 0; i < trabalhos; i++){
        scanf("%lf", (notas+ i));
        denominador += 1/(*(notas + i) + 1);    
        }

    //Cálculo final da média.
    media = (trabalhos/denominador) - 1;

    //Imprimindo a média final.
    printf ("%.2lf", media);

    free (notas); //Liberando a memória heap que foi utilizada.

    return 0;
}