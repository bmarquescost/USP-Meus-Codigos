/*
            CONVERSOR BINARIO PARA NÚMERO DECIMAL
            ALUNO: Bernardo Marques Costa
            NÚMERO USP: 11795551
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main (){
    char binario[35];       //Definindo um vetor do tipo char, para que seja armazenado o binário como uma string (cadeia de caracteres)
    int valor = 0;          //Iniciando a variável inteira valor como zero, que será o valor de conversão binária para decimal 
    int i;                  //Definindo inteira a primeira variável de iteração.
    
    //Nessa iteração ocorrerá o preenchimendo do vetor binario com 0, ou seja, '\0' ou null.
    for (i = 0; i < 40; i ++)

    {
        binario[i] = 0;
    }

    //Preenchendo o vetor com o binário escolhido.
    scanf ("%s", binario);
   
    int j;                  //Próxima variável de iteração.
    
    /*

    Nessa próxima iteração teremos o seguinte processo: 
    j irá variar de 0 até o tamanho do código binário que foi obtido a partir do scanf (tamanho obtido pela função strlen(binario)).
    k seŕa equivalente a potência de 2 nas posições sequencias, lembrando que os expoentes decrescem do bit mais siginifcativo
    correspondente à posição do vetor binario(0) até o bit menos sigficativo (que fica na ultima posição do binario, correpondente
    à strlen(binário) - 1).
    O valor equivale a soma de todas as repetições, nas quais o binário na posição [j] (sendo ou '0' ou '1') é transformado
    no seu respectivo valor na tabela ASCII, sendo assim, 48 para 0 ou 49 para 1. Assim, para obter o valor 0 ou 1, é necessário
    subtrair o inteiro 48. Esse novo número é multiplicado pelo valor de k, e, assim, obtêm-se o valor para aquela posição específica
    do vetor binário.
    
    */
    for (j = 0; j < strlen(binario); j++)   
    {
        int k;
        k = pow (2, strlen(binario)-1-j);
        valor += (binario [j] - 48) * k;
    }
    printf ("%d\n", valor);  //Printando na tela o resultado total em decimal, após a finalização do laço de repetição.

    return 0;
}