#include<stdio.h>
#include "strutture.h"


int main(){
    ELENCO e;
    DISTMATR m;
    FILE* fp = fopen("input.txt", "r");
    caricaDATI(fp, &e, &m);
    printf("Dati caricati correttamente dal file, ecco l'elenco delle città:\n");
    printELENCO(e);
    printf("\n\n\n");

    int MINS = 2;
    int MAXD = 4;
    SEDI s = creaSEDI(2, (int[]){0, 2});

    printSEDI(s, e);
    if(checkSedi(m, MAXD, MINS, s)){
        printf("Distribuzione di sedi pronto soccorso valida\n\n\n\n\n");
    }else{
        printf("Distribuzione di sedi pronto soccorso non valida\n");
        return 1;
    }

    printf("Cerco la migliore assegnazione di città senza pronto soccorso a città con pronto soccorso...\n");
    SERVIZI best_sol = bestPart(m, s, MINS, MAXD);
    printf("Migliore assegnazione trovata:\n");
    printSERVIZI(best_sol, e, s);
}