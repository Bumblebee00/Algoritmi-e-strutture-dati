#include<stdlib.h>
#include "sort.h"

void MergeSort(att* v, int n){
    att* helper = malloc(sizeof(att)*n);
    MergeSortR(v, 0, n-1, helper);
    free(helper);
}

void MergeSortR(att* v, int l, int r, att* helper){
    if (l==r){
        return;
    }

    int m = (l+r)/2;

    MergeSortR(v, l, m, helper);
    MergeSortR(v, m+1, r, helper);
    Merge(v, l, r, helper);
}

void Merge(att* v, int l, int r, att* helper){
    int m = (l+r)/2;
    int i = l;
    int j = m+1;

    for (int x=l; x<=r; x++){
        if (i>m){
            helper[x] = v[j];
            j++;
        } else if (j>r){
            helper[x] = v[i];
            i++;
        } else if (v[i].inizio < v[j].inizio){
            helper[x] = v[i];
            i++;
        } else {
            helper[x] = v[j];
            j++;
        }
    }

    for (int x=l; x<=r; x++){
        v[x] = helper[x];
    }
}