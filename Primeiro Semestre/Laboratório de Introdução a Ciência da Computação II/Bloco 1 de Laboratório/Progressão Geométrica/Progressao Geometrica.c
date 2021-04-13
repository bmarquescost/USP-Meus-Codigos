#include <math.h>
#include <stdio.h>
int main (){
    float a1, an, numeros, q, soma;
    scanf ("%f %f %f", &a1, &q, &numeros);
    an = a1*pow(q,numeros-1);
    soma = (a1*(pow(q,numeros) - 1))/(q -1);
    printf ("%.2f\n%.2f", an, soma);
    return 0;

}