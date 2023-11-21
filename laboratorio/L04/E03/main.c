#include <stdio.h>
#include<stdlib.h>

#define n_pietre 4

enum Pietra { ZAFFIRO, RUBINO, TOPAZIO, SMERALDO };

// successivo[TOPAZIO] (equivalente a successivo[2]) contiene le pietre che possono stare dopo al topazio
int successivo[n_pietre][2] = {
    {ZAFFIRO, RUBINO},
    {TOPAZIO, SMERALDO},
    {ZAFFIRO, RUBINO},
    {TOPAZIO, SMERALDO},
};

void findMaxCollana(int *mark);
int findCollanaR(int pos, int *sol, int *mark, int* maxPossible, int* max, int *maxCollana);

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

    for (enum Pietra p=ZAFFIRO; p<=SMERALDO; p++){
        if (mark[p] == 0){ continue; }
        sol[0] = p;
        mark[p]--;
        if (findCollanaR(1, sol, mark, &maxLenghtPossible, &maxLenghtFound, maxCollana)) { break; }
        mark[p]++;
    }

    printf(" z+r+t+s = %2d Lunghezza massima: %2d Collana massima: ", maxLenghtPossible, maxLenghtFound);
    for (int i=0; i<maxLenghtFound; i++){
        enum Pietra p = maxCollana[i];
        if (p==ZAFFIRO) printf("z");
        else if (p==RUBINO) printf("r");
        else if (p==TOPAZIO) printf("t");
        else if (p==SMERALDO) printf("s");
    } printf("\n");

    free(maxCollana);
    free(sol);
}

/*
pos è l'indice della ricorsione a cui siamo arrivati
sol è la collana che abbiamo composto finora. il numero 0 sta per zaffiro, 1 per rubino, eccetra
mark è un vettore di n_pietre interi, che contirne il numero di pietre ancora disponibili per trovare la collana
maxPossible is z+r+t+s
max è la lughezza massima trovata della collana finora (passato by reference)
maxCollana è la collana più lunga trovata (stesso type di sol)

the return value is 0 or 1 (= max possible solution has been found)
*/
int findCollanaR(int pos, int *sol, int *mark, int* maxPossible, int* max, int *maxCollana){
    int addedAtLeasOne = 0;
    for (int i=0; i<2; i++){
        enum Pietra p = successivo[sol[pos-1]][i];
        // - se non ci sono abbastanza pietre, passa alla prossima pietra
        if (mark[p] == 0){ continue; }
        // - se siamo a una ...t, e sono finite le r, la collana continuerà con tutte le z e poi bom
        if (p == TOPAZIO && mark[RUBINO]==0){
            int len = pos+1+mark[ZAFFIRO];
            addedAtLeasOne=1;
            if (len > *max) {
                *max = len;
                if (*max == *maxPossible){ return 1; }
                // save this sol
                int i;
                for (i=0; i<pos; i++){ maxCollana[i] = sol[i]; }
                maxCollana[pos] = TOPAZIO;
                i++;
                for (; i<len; i++) { maxCollana[i] = ZAFFIRO; }
            }
            // now we calculated this branche and we passiamo alla prossima pietra
            continue;
        }
        // - se siamo a una ...r, e sono finite le t, la collana continuerà con tutte le s e poi bom
        if (p == RUBINO && mark[TOPAZIO]==0){
            int len = pos+1+mark[SMERALDO];
            addedAtLeasOne=1;
            if (len > *max) {
                *max = len;
                if (*max == *maxPossible){ return 1; }
                // save this sol
                int i;
                for (i=0; i<pos; i++){ maxCollana[i] = sol[i]; }
                maxCollana[pos] = RUBINO;
                i++;
                for (; i<len; i++) { maxCollana[i] = SMERALDO; }
            }
            // now we calculated this branche and we passiamo alla prossima pietra
            continue;
        }

        sol[pos] = p;
        mark[p]--;
        if (findCollanaR(pos+1, sol, mark, maxPossible, max, maxCollana)) { return 1; }
        mark[p]++;
        addedAtLeasOne = 1;
    }
    // condizione di terminazione. non serve metterlo prima perchè nel caso si abbia pos=maxLenghtPossible, il vettore mark sarà tutto a 0, quindi sol[pos] non verrà mai eseguito (non c'è errore) e !addedAtLeasOne rimane a true
    if (!addedAtLeasOne){
        // la lunghezza della collana è pos
        if (pos > *max){
            *max = pos;
            for (int i=0; i<pos; i++){ maxCollana[i] = sol[i]; }
            if (*max == *maxPossible){ return 1; }
        }
    }
    return 0;
}