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

    return 0;
}