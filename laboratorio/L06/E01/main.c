/*
Strutture dati:
- vettore v con la sequenza di interi
- vettore p con, in posizione i, l'indice del predecessore nella più lunga sequenza di attività fino all'attività i
- vettore d con la durata della sopramenzionata più lunga sequenza di attività fino all'attività i
*/
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "sort.h"

void leggiFile(char *path, att* *v, int* n);

int main(int argc, char *argv[]){
    if (argc != 2){ printf("Usage: %s filename\n", argv[0]); return 1; }

    int n;
    att* v;
    leggiFile(argv[1], &v, &n);

    printf("Before:\n");
    for (int i=0; i<n; i++){ printf("%-6d|%d\n", v[i].inizio, v[i].fine); }

    MergeSort(v, n); // sort by starting time
    
    printf("After:\n");
    for (int i=0; i<n; i++){ printf("%-6d|%d\n", v[i].inizio, v[i].fine); }

    int *p = malloc(sizeof(int)*n);
    int *d = malloc(sizeof(int)*n);

    // first element doesn't have a predecessor
    p[0] = -1;
    d[0] = v[0].fine - v[0].inizio;

    // per ogni attività
    int maxdIndex;
    for (int i=1; i<n; i++){
        // trova un attività a cui si può attaccare la i-esima. in caso di più possibilità, scegli quella di durata massima
        maxdIndex=-1;
        for (int j=0; j<i; j++){
            if (v[j].fine <= v[i].inizio && d[j] > d[maxdIndex]){
                maxdIndex=j;
            }
        }
        if (maxdIndex!=-1){
            p[i] = maxdIndex;
            d[i] = d[maxdIndex] + v[i].fine - v[i].inizio;
        } else {
            p[i] = -1;
            d[i] = v[i].fine - v[i].inizio;
        }
    }

    // trova sequenza di attività durata massima
    maxdIndex = 0;
    for (int i=0; i<n; i++){ if (d[i] > d[maxdIndex]){ maxdIndex = i; } }
    
    // ricostruisci la sequenza (usiamo maxIndex come variabile di iterazione)
    printf("Sequenza di durata totale massima = %d\nEccola in ordine anti cronologico:\ninizio|fine\n", d[maxdIndex]);
    while (maxdIndex >= 0){
        printf("%-6d|%d\n", v[maxdIndex].inizio, v[maxdIndex].fine);
        maxdIndex = p[maxdIndex];
    }
}

void leggiFile(char *path, att* *v, int* n){
    FILE* fp = fopen(path, "r");
    if (fp==NULL){ printf("File %s not found", path); }
    fscanf(fp, "%d\n", n);

    *v = malloc(sizeof(att)*(*n));

    for (int i=0; i<(*n); i++){
        fscanf(fp, "%d %d\n", &((*v)[i].inizio), &((*v)[i].fine));
    }
    fclose(fp);
}