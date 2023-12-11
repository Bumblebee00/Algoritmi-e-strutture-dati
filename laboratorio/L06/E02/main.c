// TODO: non funziona
/*
Dato un certo numero di pietre preziose, calcolare al lunghezza della collana più lunga possibile.
I sottoproblemi già risolti (date queste pietre qual'è la soluzione più lunga) saranno memorizzati in cosa?

Due soluzioni:
- in un vettore 4 dimensionale. gli indici sono z,r,s,t, e il valore è la soluzione al problema, o -1 se non è stato risolto. questo è perchè l'accesso al vettore è O(1). Il problema e che usiamo tanta memoria r*s*t*z*sizeof(int). Il vettore 4d è implementato con un vettore 1d, e l'indice è calcolato con funzioni ausiliarie

- in una lista ordinata, la chiave di ordinamnto è la somma del numero di pietre r+s+t+z. E possibilie che casi diversi abbiano la stessa chiave, ma vabbè. Questa scelta perchè nel caso non si esplori tutto lo spazio delle soluzioni, risparmiamo molta memoria.
*/
#include<stdio.h>
#include<stdlib.h>
#define n_pietre 4

enum Pietra { ZAFFIRO, RUBINO, TOPAZIO, SMERALDO };

struct knownSolutionsWrapper{
    int *solutions;
    int z;
    int r;
    int t;
    int s;
};
typedef struct knownSolutionsWrapper *sp;

// prototipi
int index4D(int z, int r, int t, int s, sp sol);

void findMaxCollana(int mark[n_pietre], sp sol);

// l'input è dato senza togliere la pietra iniziale. è impossibile che accada fZ({0 zaffiri, r, t, s})
int fZ(int mark[n_pietre], sp sol);
int fR(int mark[n_pietre], sp sol);
int fT(int mark[n_pietre], sp sol);
int fS(int mark[n_pietre], sp sol);

int main(int argc, char* argv[]){
    int n, z, r, t, s;
    sp sol = malloc(sizeof(struct knownSolutionsWrapper));

    if (argc != 2){ printf("Usage: %s <path>", argv[0]); return 1; }
    FILE* fp = fopen(argv[1], "r");
    fscanf(fp, "%d\n", &n);
    for (int i=0;i<n;i++){
        printf("Test #%2d: ", i);
        fscanf(fp, "%d %d %d %d\n", &z, &r, &t, &s);

        int mark[n_pietre] = {z, r, t, s};

        sol->solutions = malloc(sizeof(int)*z*r*t*s);
        for (int j=0; j<z*r*t*s; j++){ sol->solutions[j] = -1; }
        sol->z = z;
        sol->r = r;
        sol->t = t;
        sol->r = r;

        findMaxCollana(mark, sol);

        free(sol->solutions);
    }
}

void findMaxCollana(int mark[n_pietre], sp sol){
    int temp;
    int maxLenghtFound = 0;

    // if z!=0... vabbè all'inizio non sono mai zero
    maxLenghtFound = fZ(mark, sol);
    temp = fR(mark, sol);
    if (temp>maxLenghtFound){ maxLenghtFound = temp; }
    temp = fT(mark, sol);
    if (temp>maxLenghtFound){ maxLenghtFound = temp; }
    temp = fS(mark, sol);
    if (temp>maxLenghtFound){ maxLenghtFound = temp; }

    printf("Collana massima di lunghezza %2d\n", maxLenghtFound);
}

int fZ(int mark[n_pietre], sp sol){
    int i = index4D(mark[ZAFFIRO], mark[RUBINO], mark[TOPAZIO], mark[SMERALDO], sol);
    int temp = sol->solutions[i];
    if (temp != -1){ return temp; }

    mark[ZAFFIRO]--;
    int maxLenghtFound = 0;
    // uno zaffiro deve essere seguito immediatamente o da un altro zaffiro o da un rubino
    if (mark[ZAFFIRO]>0){ maxLenghtFound = fZ(mark, sol); }
    if (mark[RUBINO]>0){
        temp = fR(mark, sol);
        if (temp>maxLenghtFound){ maxLenghtFound = temp; }
    }
    sol->solutions[i] = maxLenghtFound +1;
    return maxLenghtFound + 1;
}

int fR(int mark[n_pietre], sp sol){
    int i = index4D(mark[ZAFFIRO], mark[RUBINO], mark[TOPAZIO], mark[SMERALDO], sol);
    int temp = sol->solutions[i];
    if (temp != -1){ return temp; }

    mark[RUBINO]--;
    int maxLenghtFound = 0;
    // un rubino deve essere seguito immediatamente o da uno smeraldo o da un topazio
    if (mark[SMERALDO]>0){ maxLenghtFound = fS(mark, sol); }
    if (mark[TOPAZIO]>0){
        temp = fT(mark, sol);
        if (temp>maxLenghtFound){ maxLenghtFound = temp; }
    }
    sol->solutions[i] = maxLenghtFound+1;
    return maxLenghtFound + 1;
}

int fT(int mark[n_pietre], sp sol){
    int i = index4D(mark[ZAFFIRO], mark[RUBINO], mark[TOPAZIO], mark[SMERALDO], sol);
    int temp = sol->solutions[i];
    if (temp != -1){ return temp; }

    mark[TOPAZIO]--;
    int maxLenghtFound = 0;
    // un topazio deve essere seguito immediatamente o da uno zaffiro o da un rubino.
    if (mark[ZAFFIRO]>0){ maxLenghtFound = fZ(mark, sol); }
    if (mark[RUBINO]>0){
        temp = fR(mark, sol);
        if (temp>maxLenghtFound){ maxLenghtFound = temp; }
    }
    sol->solutions[i] = maxLenghtFound + 1;
    return maxLenghtFound + 1;
}

int fS(int mark[n_pietre], sp sol){
    int i = index4D(mark[ZAFFIRO], mark[RUBINO], mark[TOPAZIO], mark[SMERALDO], sol);
    int temp = sol->solutions[i];
    if (temp != -1){ return temp; }

    mark[SMERALDO]--;
    int maxLenghtFound = 0;
    // uno smeraldo deve essere seguito immediatamente o da un altro smeraldo o da un topazio
    if (mark[SMERALDO]>0){ maxLenghtFound = fS(mark, sol); }
    if (mark[TOPAZIO]>0){
        temp = fT(mark, sol);
        if (temp>maxLenghtFound){ maxLenghtFound = temp; }
    }
    sol->solutions[i] = maxLenghtFound+1;
    return maxLenghtFound + 1;
}

int index4D(int z, int r, int t, int s, sp sol){
    return z*(sol->r*sol->t*sol->s) + r*(sol->t*sol->s) + t*sol->s + s;
}