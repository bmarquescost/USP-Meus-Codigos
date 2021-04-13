/*
        EXPOENTE A PARTIR DE LAÇO DE REPETIÇÃO
*/
#include <stdio.h>
#include <stdlib.h>

int main (){
    double a, potencia;             //Declarando as variáveis a, b e a potencia, sendo a e potencia numeros reais e b um numero inteiro.      
    long int b;    
    scanf ("%lf %ld", &a, &b);
    
    //Agora sera realizado o laço de repetição que ira ser semelhante a potenciação de a elevado a b.
    int i = b;      //Terei a iteração de i no laço while.
    potencia = a;   //Definindo a potencia como a, sendo potencializada sequencialemnte. 
    
    for (i=b; i > 1; i --){           // Iteração ocorre da seguinte forma:                                                         
        potencia *= a;                // i é iniciado como b, sendo decrescido a cada iteração.                                               
    }                                 // No momento que i = 1 a estrutura é encerrada, isso porque,
                                      // por exemplo, se b = 2, haverá apenas uma multiplicação (a x a). 
                                           
    printf ("%.4lf\n", potencia);                     

    return 0;
}