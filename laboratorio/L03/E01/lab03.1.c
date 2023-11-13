// Mattia Micheletta Merlin, esercizio 1, laboratorio 3

#include<stdio.h>

// prototypes
int majority( int *a, int N);
int findMajor(int *a, int l, int r);
int countOccurencies(int *a, int l, int r, int b);

int main(){
    int N;
    printf("Input the number of elements of the array: ");
    scanf("%d", &N);

    int a[N];
    for (int i=0; i<N; i++){
        printf("Input the %d-th element of the array: ", i);
        scanf("%d", &a[i]);
    }

    int maj = majority(a, N);
    printf("The majority element is %d\n", maj);
}


/*
gets a vector a, of N ints.
the majoritary element is the element that appears more than N/2 times.
it could not exist (-1 is returned).
*/
int majority(int *a, int N){
    return findMajor(a, 0, N-1);
}


/*
it is a recursive function. it splits the vector in 2, and finds the majoritay in each of the two.
base case:
    a vector of one element
then when ricombinig:
    if the two maj are equal return maj
    if the two dont have a maj return -1
    if only one has a maj, count how many occurrencies of the maj are there in the other sub array, and decide if there is a maj or not
    if there are two different maj check for each one of them, if it's a maj of the whole thing
l and r are left and right indexes
*/
int findMajor(int *a, int l, int r){
    // base case
    if (l==r){
        return a[l];
    }
    // divide
    int middle = (l+r)/2;
    int leftMaj = findMajor(a, l, middle);
    int rightMaj= findMajor(a, middle+1, r);
    // recombine
    if (rightMaj==leftMaj){ return rightMaj; }// both maj == -1, return -1. both maj == x, return x
    else if (leftMaj!=-1 && rightMaj==-1){
        int nOfLeftMaj = countOccurencies(a, l, middle, leftMaj);
        int nOfRightMaj = countOccurencies(a, middle+1, r, leftMaj);
        if (nOfLeftMaj+nOfRightMaj > (r+1-l)/2){
            return leftMaj;
        } else {
            return -1;
        }
    } else if (leftMaj==-1 && rightMaj!=-1){
        int nOfRightMaj = countOccurencies(a, middle+1, r, rightMaj);
        int nOfLeftMaj = countOccurencies(a, l, middle, rightMaj);
        if (nOfLeftMaj+nOfRightMaj > (r+1-l)/2){
            return rightMaj;
        } else {
            return -1;
        }
    } else {
        int nOfLeftMaj_inLeft = countOccurencies(a, l, middle, leftMaj);
        int nOfLeftMaj_inRight = countOccurencies(a, middle+1, r, leftMaj);
        if (nOfLeftMaj_inLeft+nOfLeftMaj_inRight > (r+1-l)/2)
            return leftMaj;
        
        int nOfRightMaj_inLeft = countOccurencies(a, l, middle, rightMaj);
        int nOfRightMaj_inRight = countOccurencies(a, middle+1, r, rightMaj);
        if (nOfRightMaj_inLeft+nOfRightMaj_inRight > (r+1-l)/2)
            return rightMaj;

        return -1;
    }
}

// count how many times the int b is in the array a between the indices r and l
int countOccurencies(int *a, int l, int r, int b){
    int count = 0;
    for (int i=l; i<=r; i++){
        if (a[i]==b){ count++; }
    }
    return count;
}