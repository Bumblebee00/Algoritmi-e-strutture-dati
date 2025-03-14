#include<stdio.h>

int main(){
    int x = 4;
    int * pointer = &x; // &x is the address of x
    int y = *pointer; // *pointer is the value of the variable at the address pointer,
    // because using the * operator on a pointer returns the value of the variable at the address of the pointer

    printf("x = %d\n",x);
    printf("pointer = %p\n",pointer); // %p is a placeholder for a pointer value
}