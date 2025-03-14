#include <stdio.h>
#include <stdbool.h> // bool is not a built-in data type in C, so we need to include this header file

int main(){
    int x; // declaration
    x = 10; // initialization
    int age = 20; // declaration and initialization

    printf("you are %d years old\n", x); // %d is a placeholder for an integer value

    // data type - format specifier - memory size, range of values, description

    float pi = 3.141592;                // float     - %f  - 4 bytes of memory, roughly 6-7 digits of precision
    double pi2 = 3.14159265358979323846;// double    - %lf - 8 bytes of memory, roughly 15 digits of precision
    
    bool is_true = true;                // boolean   - %d  - 1 byte of memory
    
    char class = 'Q';                   // character - %c  - 1 byte of memory
    char class2 = 100;                  // you can also assign a character to an integer value from -128 to 127
    unsigned char class3 = 220;         // unsigned char is a character represented with a number 0-255
    char name[] = "John";               // string    - %s  -

    int y = 10;                         // integer   - %d  - 4 bytes of memory, from -2147483648 to 2147483647
    // this is the same as long int. is not short int
    unsigned int x2 = 10;               // unsigned integer - %u - 4 bytes of memory, from 0 to 4294967295
    short int age2 = 20;                // short int - %hd - 2 bytes of memory, from -32768 to 32767
    unsigned short int age3 = 20;       // unsigned short int - %hu - 2 bytes of memory, from 0 to 65535
    short age4 = 32768;                 // you can also not put the int keyword and it will still work
    // this will have the value -32768 because it loops
    long long int age5 = 2147483648;    // long long int - %lld - 8 bytes of memory, from -9223372036854775808 to 9223372036854775807
    unsigned long long int age6 = -1; // unsigned long long int - %llu - 8 bytes of memory, from 0 to 18446744073709551615

    printf("your name is %s\n", name); // %s is a placeholder for a string value
    printf("the class is %c\n", class); // prints Q
    printf("the class is %d\n", class2); // prints 100
    printf("your age is %hd\n", age2);
    printf("your age is %llu\n", age6);

    /* more on format specifiers: 
    %.1 - 1 decimal place
    %.4 - 4 decimal places
    %10 - 10 characters wide
    %10.4 - 10 characters wide with 4 decimal places
    %010.4 - 10 characters wide with 4 decimal places, padded with 0s
    %-10.4 - 10 characters wide with 4 decimal places, left aligned
    */
    printf("pi is %-.4f\n", pi);



    // constant variables:
    const float PI = 3.141592; // you can't change the value of PI


    return 0;
}