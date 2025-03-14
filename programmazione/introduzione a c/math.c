#include <stdio.h>
#include <math.h>

int main(){
    int x = 5;
    int y = 2;
    int res = x/y;
    printf("%d\n", res); // prints 2, not 2.5 because res is an integer
    float r2 = x/y;
    printf("%f\n", r2); // prints 2.000000, not 2.5 because x and y are integers
    float r3 = (float)x/y;
    printf("%f\n", r3); // prints 2.500000, because we casted x to a float

    x *= 3;
    printf("%d\n", x); // prints 15

    double A = sqrt(9);
    double B = pow(2, 3); // 2^3
    int C = round(3.1415); // 3 round to nearest integer
    int D = ceil(3.1415); // 4  round up to nearest integer
    int E = floor(3.1415); // 3 round down to nearest integer
    double F = fabs(-3.1415); // 3.1415 absolute value
    double G = log(2.71828); // 1 natural log
    double H = log10(100); // 2 log base 10
    double I = exp(1); // 2.71828 e^x
    double J = sin(0); // 0 sine
    double K = cos(0); // 1 cosine
    double L = tan(0); // 0 tangent

}