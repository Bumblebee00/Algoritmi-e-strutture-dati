#include<stdio.h>

int main(){
    // while loop: check condition before executing the body
    // do-while loop: check condition after executing the body
    unsigned long long int input;

    do{
        printf("Input your thelephone number\n");
        scanf("%llu",&input);
    } while (input < 1000000000);

    // continue: skip the rest of the body and go to the next iteration
    // break: exit the loop

    // because 13 is unlucky
    for (int i=5;i<=18;i++){
        if (i==13){
            continue;
        }
        printf("%d\n",i);
    }
}