#include <stdio.h>
#include <math.h>
int main (){
    double a,b, exp;
    scanf ("%lf", &a);
    scanf ("%lf", &b);
    exp = pow(a,b);
    printf ("%.4lf", exp);
    
    return 0;
}