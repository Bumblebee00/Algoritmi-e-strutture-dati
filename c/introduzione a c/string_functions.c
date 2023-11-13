#include <stdio.h>
#include <string.h>

int main(){
    char string1[20] = "Mattia";
    char string2[] = "Micheletta";

    // concatenation
    strcat(string1, string2);
    printf("%s\n",string1);

    // length
    printf("%lu\n",strlen(string1));

    // copy
    char string3[20];
    strcpy(string3, string1);
    printf("%s\n",string3);

    // comparison. It returns 0 if the strings are equal, a positive number if the first string is greater than the second, a negative number otherwise
    printf("%d\n",strcmp(string1, string2));



    return 0;
}