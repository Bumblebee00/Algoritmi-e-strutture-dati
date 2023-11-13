#include <stdio.h>

int main(){
    /*
    Escape sequences are used to represent certain special characters within string literals and character literals.
    They are represented by a backslash followed by a character or a sequence of digits. For example
    \n represents a newline character.
    \t represents a tab character.
    \" represents a double quote character, inside a string.
    \\ represents a backslash character.
    \b represents a backspace character.
    \r represents a carriage return character.
    */
    printf("Hello\tWorld!\rciao");
    return 0;
}