#include<stdio.h>
#include<ctype.h>

void bravo_ragazzo(int); // function prototype, it ensures that the function is defined somewhere else, and is called with the right arguments
// any c compilerd do not check the function prototype, but it is a good practice to use it
int main(){
    char grade;
    printf("Enter your grade: ");
    scanf("%c",&grade);
    grade = toupper(grade);

    // switches is more efficient than if-else
    switch(grade){
        case 'A':
            printf("Excellent\n");
            bravo_ragazzo(3);
            break; // if there is no break, it will execute the next case
        case 'B':
            printf("Good\n");
            break;
        case 'C':
            printf("Average\n");
            break;
        case 'D':
            printf("Poor\n");
            break;
        case 'F':
            printf("Fail\n");
            break;
        default:
            printf("Invalid grade\n");
    }

    return 0;
}

void bravo_ragazzo(int x){
    for (int i=0;i<x;i++){
        printf("Perchè è un bravo ragazzo!\n");
    }
    printf("E nessuno lo può negar!\n");

}