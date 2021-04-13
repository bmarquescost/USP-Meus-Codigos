#include <math.h>
#include <stdio.h>

int main (){
    double a,inteiro, decimal, arredondado;
    scanf ("%lf", &a);
    inteiro = floor(a);
    decimal = a - ((int)a);
    if (decimal >= 0.5)
        arredondado = ceil(a);
    else arredondado = floor (a);
    printf ("%.0lf\n%.4lf\n%.0lf", inteiro, decimal, arredondado);
    
    return 0;

}