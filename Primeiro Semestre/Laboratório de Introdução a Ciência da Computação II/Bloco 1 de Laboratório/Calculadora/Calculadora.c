#include <stdio.h>
#include <math.h>

int main (){
    char op;
    double a,b;
    scanf ("%lf %c %lf", &a, &op, &b);
    if (op == '+') printf ("%lf\n", a + b);
    if (op == '-') printf ("%lf\n", a - b);
    if (op == '*') printf ("%lf\n", a * b);
    if (op == '/') printf ("%lf\n", a / b);
    if (op == '%') printf ("%lf\n", (a/b)*100);


    return 0;
}