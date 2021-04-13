#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int main (){
    int num, resto, cont = 0, prox;
    scanf ("%d", &num);
    for (int i = 1, aux = 0; aux <= num; i ++){
        aux = aux + i;
        resto = num - aux;
        if (resto == 0) {
            printf ("SIM\n");
            cont = 1;
            prox = aux + i + 1;
            printf ("%d\n", prox);
            if (sqrt(num + prox)) printf ("SIM\n");
            break;
        }
    }
    if (cont == 0) printf ("NAO\n");
    
    return 0;
}