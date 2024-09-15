#include<stdio.h>
#include "strutture.h"


int main(){
    ELENCO e;
    DISTMATR m;
    FILE* fp = fopen("input.txt", "r");
    caricaDATI(fp, &e, &m);

    int MINS = 2;
    int MAXD = 4;
    SEDI s = creaSEDI(2, (int[]){0, 2});
    printSEDI(s, e);
    SERVIZI best_sol = bestPart(m, s, MINS, MAXD);
    printf("Best solution:\n");
    printSERVIZI(best_sol, e, s);
}