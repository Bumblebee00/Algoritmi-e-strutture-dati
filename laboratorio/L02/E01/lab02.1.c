// Mattia Micheletta Merlin, esercizio 1, laboratorio 2

#include <stdio.h>

int gcd(int a, int b);

int main(){
    int a, b, i, count = 0;

    printf("Enter two numbers (separated by space): ");
    scanf("%d %d", &a, &b);
    printf("GCD of %d and %d is %d\n", a, b, gcd(a, b));
}

int gcd(int a, int b){
    if (a==b){
        return a;
    } else if (b > a){
        int temp = a;
        a = b;
        b = temp;
    }
    
    if (a%2==0 && b%2==0){
        return 2*gcd(a/2, b/2);
    }
    else if (a%2!=0 && b%2==0){
        return gcd(a, b/2);
    }
    else if (a%2==0 && b%2!=0){
        return gcd(a/2, b);
    }
    else if (a%2!=0 && b%2!=0){
        return gcd((a-b)/2, b);
    }
    return -1; // to signal error
}