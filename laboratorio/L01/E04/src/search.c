#include <string.h>
#include <stdlib.h>
#include "../include/main.h"

/*
searches for a BusRide in the array v, that has the same "from" field as the string from. if there are multiple BusRides with the same "from" field, the function returns all of them, in an array of integers. at each new match, the function will realloc the array to fit the new element. -1 is put at the end to signal the end of the list
*/
int *LinearSearch(BusRide **v, int n, char from[]){
    int *matches = malloc(sizeof(int));
    int m = 0;
    for (int i=0; i<n; i++){
        if (strncmp((*v[i]).from, from, strlen(from))==0){
            matches[m] = i;
            m++;
            matches = realloc(matches, sizeof(int)*(m+1));
        }
    }
    matches[m] = -1;
    return matches;
}

/*
Questo codice è stato preso dalle slide (pag 116 capitolo 01), e leggermente adattato per poter ritornare tutti gli elementi matchanti e non solo uno.
*/
int *BinSearch(BusRide **v, int l, int r, char from[]){
    int m;
    if (l > r){
        int *matches = malloc(sizeof(int));
        matches[0]=-1;
        return matches;
    }
    m = (l + r)/2;
    if (strncmp((*v[m]).from, from, strlen(from))==0){
        // search in both directions
        int *matches = malloc(sizeof(int));
        int len_m = 1;
        matches[0] = m;
        for (int i=m+1; i<=r && strncmp((*v[i]).from, from, strlen(from))==0; i++){
            len_m++;
            matches = realloc(matches, sizeof(int)*len_m);
            matches[len_m-1] = i;
        }
        for (int i=m-1; i>0 && strncmp((*v[i]).from, from, strlen(from))==0; i--){
            len_m++;
            matches = realloc(matches, sizeof(int)*len_m);
            matches[len_m-1] = i;
        }
        matches = realloc(matches, sizeof(int)*(len_m+1));
        matches[len_m] = -1;
        return matches;
    }
    if (strncmp((*v[m]).from, from, strlen(from))>0)
        return BinSearch(v, l, m-1, from);
    return BinSearch(v, m+1, r, from);
}
