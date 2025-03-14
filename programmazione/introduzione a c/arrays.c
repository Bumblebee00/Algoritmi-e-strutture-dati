#include<stdio.h>
#include<ctype.h>

int main(){
    //an array is a data structure that stores a collection of elements of the same type

    double prices[] = {9.99, 15.99, 24.99, 39.99, 49.99};
    printf("%lf\n",prices[0]);

    double grades[5];

    grades[0] = 10.0;
    grades[4] = 9.0;

    // float somethings[]; is not valid

    // 2d arrays
    int matrix[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    int second_matrix[][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    char cars[][10] = {"Volvo", "BMW", "Ford"};

    // cars[0] = "Tesla"; is not valid
    strcopy(cars[0], "Tesla");
}