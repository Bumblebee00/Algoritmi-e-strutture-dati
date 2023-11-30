// TODO: provare a aggiungere un altro criterio di pruning, precomuputando la somma rimanente.
#include<stdio.h>
#include<stdlib.h>
#include "main.h"
#include "sort.h"

int main(int argc, char* argv[]){
    if (argc != 2) { printf("Usage: %s filename\n", argv[0]); return 1; }
    int n;
    att* v;

    v = leggiFile(argv[1], &n, v);

    // debug
    for (int i=0; i<n; i++){ printf("index number %d: %d %d\n", i, v[i].inizio, v[i].fine); }

    MergeSort(v, n);

    // debug
    for (int i=0; i<n; i++){ printf("index number %d: %d %d\n", i, v[i].inizio, v[i].fine); }

    attSel(n, v);
}

void attSel(int n, att* v){
    int* sol = malloc(sizeof(int)*n);
    // debug
    for (int i=0; i<n; i++){ sol[i] = -1; }
    int max=0;
    int* maxSol = malloc(sizeof(int)*n);
    powersetPruned(0, v, sol, n, &max, maxSol, NULL);
    printSubset(maxSol, v, n);
    free(sol);
    free(maxSol);
}

/*
pos is the index. we are arrived at chosing element index pos
val is the set we have to do the subset of
sol is a vector of zeros or ones, containing whether the element is inside or outside the pos. you should read it up to the index pos.
val and sol are of lenght n.
max is the maximum duration ever recorded.
maxSol is a pointer to a array of int. if a new max is found, that solution should be saved in this array
lastSelected is a pointer to the last selected activity. is used for pruning if the current activity overlaps with the last selected, it should not be selected.
*/
void powersetPruned(int pos, att* val, int* sol, int n, int* max, int* maxSol, att* lastSelected){
    // terminazione: check if the sum of duration is max
    if (pos >= n) {
        int duration = calculateDuration(sol, val, n);
        if (duration>*max){
            *max = duration;
            for (int i=0; i<n; i++){ maxSol[i] = sol[i]; }
        }
        return;
    }
    
    //debug
    int* tmp = malloc(sizeof(int)*n);
    for (int i=0; i<n; i++){ tmp[i] = sol[i]; }
    printf("Sol is: ");
    for (int i=0; i<n; i++){ if(i!=pos){ printf("%-2d ", tmp[i]); } else { printf("?  "); } }
    free(tmp);
    printf(", overlap is %d", overlap(lastSelected, &val[pos]));
    printf(", current is %d %d", val[pos].inizio, val[pos].fine);
    if (lastSelected!=NULL){printf(" and lastSelected is %d %d\n", (*lastSelected).inizio, (*lastSelected).fine);}
    else { printf("\n"); }

    // take the element as not included
    sol[pos] = 0;
    powersetPruned(pos+1, val, sol, n, max, maxSol, lastSelected);
    // take the element as included, if it doesn't overlap with the last selected
    if (!overlap(lastSelected, &val[pos])){
        sol[pos] = 1;
        powersetPruned(pos+1, val, sol, n, max, maxSol, &val[pos]);
    }
}

int overlap(att* lastSelected, att* current){
    // first activity can't overlap with anything
    if (lastSelected==NULL){ return 0; }
    if ((*lastSelected).fine > (*current).inizio) { return 1; }
    return 0;
}

// sol determines a subset of v. this function assumes that all activities don't overlap.
int calculateDuration(int* sol, att* v, int n){
    int totDuration = 0;
    for (int i=0; i<n; i++){
        if (sol[i]){
            totDuration += (v[i].fine - v[i].inizio);
        }
    }
    return totDuration;
}

// sol e val should be of the same lenght n
void printSubset(int* sol, att* val, int n){
    int duration = 0;
    for (int i=0; i<n; i++){
        if (sol[i]){
            printf("i: %-2d, f:%-2d\n", val[i].inizio, val[i].fine);
            duration += val[i].fine - val[i].inizio;
        }
    }
    printf("Max duration is %d\n", duration);
}

att* leggiFile(char* path, int* n, att* v) {
    FILE* fp = fopen(path, "r");
    if (fp==NULL){ printf("File %s not found", path); }
    fscanf(fp, "%d\n", n);
    v = malloc(sizeof(att)*(*n));
    for (int i=0; i<*n; i++){ fscanf(fp, "%d %d\n", &v[i].inizio, &v[i].fine); }
    fclose(fp);
    return v;
}