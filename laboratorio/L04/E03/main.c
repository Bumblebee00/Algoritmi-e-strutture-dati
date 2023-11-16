#include <stdio.h>
#include<stdlib.h>

#define n_pietre 4

enum Pietra { ZAFFIRO, RUBINO, TOPAZIO, SMERALDO };

// regole[RUBINO] (equivalente a regole[1]) contiene le pietre che possono precedere il rubino
int regole[n_pietre][2] = {
    {ZAFFIRO, TOPAZIO},
    {ZAFFIRO, TOPAZIO},
    {RUBINO, SMERALDO},
    {RUBINO, SMERALDO}
};

// decides wether the order of stones a -> b is alowed
int thisOrderIsPossible(int a, int b){
    return (a==regole[b][0] || a==regole[b][1]);
}

void findMaxCollana(int *mark);
void findCollanaR(int pos, int *sol, int *mark, int* max, int *maxCollana);

int main(){
    int n, z, r, t, s;
    FILE* fp = fopen("easy_test_set.txt", "r");
    fscanf(fp, "%d\n", &n);
    for (int i=0;i<n;i++){
        fscanf(fp, "%d %d %d %d\n", &z, &r, &t, &s);
        int mark[n_pietre] = {z, r, t, s};
        printf("Test #%2d:", i);
        findMaxCollana(mark);
    }
}

void findMaxCollana(int *mark){
    int maxLenghtFound = 0;
    int maxLenghtPossible = 0;
    for (int i=0; i<n_pietre; i++){ maxLenghtPossible += mark[i];}
    int *maxCollana = malloc(sizeof(int)*maxLenghtPossible); // forse stiamo sovrallocando ma vabbe
    int *sol = malloc(sizeof(int)*maxLenghtPossible);

    findCollanaR(0, sol, mark, &maxLenghtFound, maxCollana);

    printf(" z + r + t + s = %2d. Lunghezza massima: %2d\n", maxLenghtPossible, maxLenghtFound);

    // printf("Collana massima: ");
    // for (int i=0; i<maxLenghtFound; i++){
    //     enum Pietra p = maxCollana[i];
    //     if (p==ZAFFIRO) printf("ZAFFIRO ");
    //     else if (p==RUBINO) printf("RUBINO ");
    //     else if (p==TOPAZIO) printf("TOPAZIO ");
    //     else if (p==SMERALDO) printf("SMERALDO ");
    // } printf("\n");
    free(maxCollana);
    free(sol);
}

/*
pos è l'indice della ricorsione a cui siamo arrivati
sol è la collana che abbiamo composto finora. il numero 0 sta per zaffiro, 1 per rubino, eccetra
mark è un vettore di n_pietre interi, che contirne il numero di pietre ancora disponibili per trovare la collana
max è la lughezza massima trovata della collana finora (passato by reference)
maxCollana è la collana più lunga trovata (stesso type di sol)
*/
void findCollanaR(int pos, int *sol, int *mark, int* max, int *maxCollana){
    int addedAtLeasOne = 0;
    for (enum Pietra p=ZAFFIRO; p<=SMERALDO; p++){
        enum Pietra pietraPrecedente;
        if (pos==0) pietraPrecedente = regole[p][0]; // prendi una pietra che possa stare davanti alla prima pietra della collana, in modo che tutte le pietre possano stare all'inizio della collana
        else pietraPrecedente = sol[pos-1];

        // se la pietra p può seguire la pietra precedente, prosegui la ricerca
        if (thisOrderIsPossible(pietraPrecedente, p)){
            if (mark[p] > 0){
                sol[pos] = p;
                mark[p]--;
                findCollanaR(pos+1, sol, mark, max, maxCollana);
                mark[p]++;
                addedAtLeasOne = 1;
            }
        }
    }
    // condizione di terminazione. non serve metterlo prima perchè nel caso si abbia pos=maxLenghtPossible, il vettore mark sarà tutto a 0, quindi sol[pos] non verrà mai eseguito (non c'è errore) e !addedAtLeasOne rimane a true
    if (!addedAtLeasOne){
        // la lunghezza della collana è pos
        if (pos > *max){
            *max = pos;
            for (int i=0; i<pos; i++){ maxCollana[i] = sol[i]; }
        }
    }
}