#include <math.h>
#include <stdio.h>
int main (){
    long a1, razao, numeros, an, soma;
    scanf ("%li %li %li", &a1, &razao, &numeros);
    an = a1 + (numeros - 1)*razao;
    soma = (a1 + an)*numeros/2;
    printf ("%li\n",an);
    printf ("%li", soma);

    return 0;
}