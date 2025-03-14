#include<stdio.h>
#include<string.h>


main(){
    int age;
    char name[25]; // 25 is the maximum number of characters that can be stored in the name variable
    // if we put more we will encouter buffer overflow

    printf("\nType your name and surname, separated by a space\n");
    // scanf eads up until the space, we have to use fgets
    fgets(name, 25, stdin); // stdin is the standard input, which is the keyboard
    name[strlen(name)-1] = '\0'; // we need to remove the \n character from the name variable

    printf("Hello, how old are you?\n");
    scanf("%d", &age); // & is the address of operator, it returns the address of a variable
    // if we didn't use the & operator, we would be passing the value of age, not the address of age

    printf("\nYour name is %s", name);
    printf("\nYou are %d years old\n", age);
}