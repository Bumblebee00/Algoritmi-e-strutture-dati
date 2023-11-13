#include<stdio.h>
#include<math.h>

int main(){
    const double PI = 3.141592;
    double r;

    printf("input the radius for the circumference:\n");
    scanf("%lf", &r);

    double c = 2*r*PI;
    double A = PI*pow(r,2);
    printf("Circumference is %lf\n",c);
    printf("Area is %lf\n", A);

    return 0;
}