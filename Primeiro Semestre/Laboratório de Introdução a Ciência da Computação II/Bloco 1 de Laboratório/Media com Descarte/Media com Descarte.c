#include <math.h>
#include <stdio.h>
int main (){
    double menor, media, soma;
    double numeros[4];
    for (int i = 0; i <= 3; i++){
        scanf ("%lf", &numeros[i]);
        if (i == 0) menor = numeros [i];
        else if (numeros [i] < menor) menor = numeros [i];
        soma = soma + numeros [i];
    media = (soma - menor)/3;
    
    }
    printf ("%.4lf", media);
        
    

    
    return 0;
}