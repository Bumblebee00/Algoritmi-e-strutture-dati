#include<stdlib.h>
#include "sort.h"

// wrapper 😎
void MergeSort(att* v, int n){
    att *help = malloc(sizeof(att)*n);
    MergeSortR(v, help, 0, n-1);
    free(help);
}

// funzione ricorsiva
void MergeSortR(att* v, att* help, int l, int r){
    // condizione di terminazione: vettore di lunghezza 1
    if (l>=r){ return; }
    // dividi a metà
    int m = (l+r)/2;
    MergeSortR(v, help, l, m);
    MergeSortR(v, help, m+1, r);
    Merge(v, help, l, m, r);
}

void Merge(att *v, att *help, int l, int m, int r){
    int i=l, j=m+1, k=l;
    for(;k<r+1;k++){
        if (i>m){ help[k] = v[j]; j++; }
        else if (j>r){ help[k] = v[i]; i++; }
        else if (v[i].inizio < v[j].inizio){help[k] = v[i]; i++;}
        else {help[k] = v[j]; j++;}
    }

    //get back from helper vector to real vector
    for (k=l; k<r+1; k++){ v[k] = help[k]; }
}