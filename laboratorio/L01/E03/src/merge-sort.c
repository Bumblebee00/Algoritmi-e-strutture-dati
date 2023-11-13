#include <stdio.h>
#include <string.h>
#include "../include/main.h"
#include "../include/merge-sort.h"

/*
A is the array to sort
N is the number of elements in A
key is the parameter of BusRide to look at

This function is a wrapper for MergeSortR, and will sort the array A in place (no return value)
*/
void MergeSort(BusRide A[], int N, ord_key key){
    int l=0, r=N-1;
    BusRide B[N];
    MergeSortR(A, B, l, r, key);
}

void MergeSortR(BusRide A[], BusRide B[], int l, int r, ord_key key) {
    int q;
    if (r <= l) // condizione di terminazione
        return;
    q = (l + r)/2;
    MergeSortR(A, B, l, q, key);
    MergeSortR(A, B, q+1, r, key);
    Merge(A, B, l, q, r, key);
}

void Merge(BusRide A[], BusRide B[], int l, int q, int r, ord_key key) {
    int i, j, k;
    i = l;
    j = q+1;
    for(k = l; k <= r; k++)
        if (i > q)
            B[k] = A[j++]; // (3)
        else if (j > r)
            B[k] = A[i++]; // (3)
        else if (ITEMlt(A[i], A[j], key) || ITEMeq(A[i], A[j], key)  ) // (4)
            B[k] = A[i++]; // (1)
        else
            B[k] = A[j++]; // (2)
    for ( k = l; k <= r; k++ )
        A[k] = B[k];
    return;
}

int ITEMeq(BusRide A, BusRide B, ord_key key) {
    switch (key)
    {
    case r_codice_tratta:
        if (strcmp(A.code, B.code)==0){ return 1; }
        else { return 0; }
        break;
    
    case r_stazione_partenza:
        if (strcmp(A.from, B.from)==0){ return 1; }
        else { return 0; }
        break;

    case r_stazione_arrivo:
        if (strcmp(A.to, B.to)==0){ return 1; }
        else { return 0; }
        break;
    
    // in theory there should never be two entries with same date and same hour si this piece of code is usless
    case r_data:
        if (isBefore(A, B)==0){ return 1; }
        else { return 0; }
        break;

    default:
        break;
    }
}

int ITEMlt(BusRide A, BusRide B, ord_key key) {
    switch (key)
    {
    case r_data:
        if (isBefore(A, B) > 0) { return 1; }
        else { return 0; }
        break;

    case r_codice_tratta:
        if (strcmp(A.code, B.code) < 0) { return 1; }
        else { return 0; }
        break;

    case r_stazione_partenza:
        if (strcmp(A.from, B.from) < 0){ return 1; }
        else { return 0; }
        break;
    
    case r_stazione_arrivo:
        if (strcmp(A.to, B.to) < 0){ return 1; }
        else { return 0; }
        break;

    default:
        break;
    }
}

/*
if r1 is before r2, return 1
if equal, return 0
if not before, return -1
*/
int isBefore(BusRide r1, BusRide r2){
    int y1, m1, d1, y2, m2, d2;
    sscanf(r1.date, "%d/%d/%d", &y1, &m1, &d1);
    sscanf(r2.date, "%d/%d/%d", &y2, &m2, &d2);
    if (y1 < y2){ return 1;}
    else if (y1 == y2){
        if (m1 < m2){ return 1; }
        else if (m1 == m2){
            if (d1 < d2){ return 1; }
            else if (d1 == d2){

    int h1, min1, sec1, h2, min2, sec2;
    sscanf(r1.departure, "%d:%d:%d", &h1, &min1, &sec1);
    sscanf(r2.departure, "%d:%d:%d", &h2, &min2, &sec2);
    if (h1 < h2){ return 1; }
    else if (h1 == h2){
        if (min1 < min2){ return 1; }
        else if (min1 == min2){
            if (sec1 < sec2){ return 1; }
            else if (sec1==sec2) { return 0; }
            else { return -1; }
        } else { return -1; }
    } else { return -1; }

            } else { return -1; }
        } else { return -1; }
    } else { return -1; }
}