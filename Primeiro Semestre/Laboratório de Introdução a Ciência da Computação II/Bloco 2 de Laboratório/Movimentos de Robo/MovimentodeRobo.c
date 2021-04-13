/*
    MOVIMENTO DO ROBÔ
    ALUNO: Bernardo Marques Costa
    NÚMERO USP: 11795551
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (){
    char comando[200], orientation;  //Definindo como char o vetor de 200 caracteres que receberá a orientação e a orientação que recebera cada caractere E ou D.
    
    //Definindo o total que será utilizado para calcular a direção que é observada pelo robô.
    int total = 0;
    
    //Armazenando os comandos digitados.
    scanf ("%s", comando);
    
    /*
    Laço de iteração: é analizado cara um dos comandos um por um
    O comando D (direita) corresponde a um acrescimo de 1 unidade ao total.
    O comando E (esquerda) corresponde a um descrescimo de 1 unidade ao total.
    Ao chegar em 4 unidades, o total é resetado para definir que o robô está orientado novamente para o Norte.
    */

    for (int i = 0; i < strlen (comando); i++){
        orientation = comando [i];
        if (orientation == 'D') total += 1;
        
        else if (orientation == 'E') total -= 1;
        
        if (total % 4 == 0) total = 0;
    }   
    
    /*
    Condiçoes para definir a orientação:
    Se o total for divisivel por 4, teremos que o robô está orientado para Norte -> por exemplo, dando uma volta completa.
    Se o modulo da divisão por 4 for igual à 1 ou -3 o robô está orientado para Leste -> Ou deu mais voltas no sentido horário - D (quando 1) -  ou mais no anti-horário - E (quando -3).
    Se o módulo da divisão por 4 for igual à 2 ou -2 o robô está orientado para o Sul -> Deu uma meia volta, andando ou 2 vezes para o sentido horario ou 2 para o anti-horário.
    Se o módulo da divisão por 4 for igual à 3 ou -1 o robô está orientado para Oeste -> Ou deu mais voltas no sentido anti-horario - E (quando -1) ou deu mais voltas no sentido horário - D (quando -3).
    (Todas análises são veridicas, mas feitas sobre uma movimentação simplificada do robô).
    */
    if (total % 4 == 0) printf ("Norte");
    if (total % 4 == 1 || total % 4 == -3) printf ("Leste");
    if (total % 4 == 2 || total % 4 == -2) printf ("Sul");
    if (total % 4 == 3 || total % 4 == -1) printf ("Oeste");

    return 0;

}