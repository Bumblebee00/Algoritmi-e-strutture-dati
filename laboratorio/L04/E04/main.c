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
int thisOrderIsPossible(enum Pietra a, enum Pietra b){
    for (int i=0; i<2; i++){ if (regole[b][i] == a) return 1; }
    return 0;
}

int isPossible(enum Pietra pietraPrecedente, enum Pietra p, int *markInv, int max_rip, int nVolteConsec){
    // le condizioni sono:
    // - la pietra attuale può stare dopo la pietra precedente. questo è determinato dalle regole
    // - nessuna tipologia di pietra si può ripetere più di max_rip volte consecutive
    // - il numero di zaffiri non può superare il numero di smeraldi
    int newSmeraldo = markInv[SMERALDO] + (p==SMERALDO);
    int newZaffiro = markInv[ZAFFIRO] + (p==ZAFFIRO);
    return thisOrderIsPossible(pietraPrecedente, p) && (nVolteConsec <= max_rip) && (newZaffiro <= newSmeraldo);
}

void findMaxCollana(int *mark, int *val_pietre, int max_rip);
int findCollanaR(int pos, int *sol, int *mark, int *markInv, int *val_pietre, int maxPossible, int* max, int *maxCollana, int max_rip, int* maxLenght, int nVolteConsec);

int main(){
    int n, z, r, t, s, vz, vr, vt, vs, max_rip;
    FILE* fp = fopen("test_set.txt", "r");
    fscanf(fp, "%d\n", &n);
    for (int i=0;i<n;i++){
        fscanf(fp, "%d %d %d %d  %d %d %d %d %d\n", &z, &r, &t, &s, &vz, &vr, &vt, &vs, &max_rip);
        int mark[n_pietre] = {z, r, t, s};
        int val_pietre[n_pietre] = {vz, vr, vt, vs};
        printf("Test #%2d:", i+1);
        findMaxCollana(mark, val_pietre, max_rip);
    }
}

void findMaxCollana(int *mark, int *val_pietre, int max_rip){
    int maxValFound = 0;
    int maxLenghtFound = 0;
    int maxLenghtPossible = 0;
    for (int i=0; i<n_pietre; i++){ maxLenghtPossible += mark[i];}
    int maxValPoss = 0;
    for (int i=0; i<n_pietre; i++){ maxValPoss += mark[i]*val_pietre[i]; }
    
    int *maxCollana = malloc(sizeof(int)*maxLenghtPossible); // forse stiamo sovrallocando ma vabbe
    int *sol = malloc(sizeof(int)*maxLenghtPossible);
    int markInv[n_pietre] = {0, 0, 0, 0};

    findCollanaR(0, sol, mark, markInv, val_pietre, maxLenghtPossible, &maxValFound, maxCollana, max_rip, &maxLenghtFound, 0);

    printf(" valore massimo possibile = %2d. Valore massimo trovato = %4d (usando %2d gemme). ", maxValPoss, maxValFound, maxLenghtFound);

    printf("Collana massima: ");
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
markInv è un vettore di n_pietre interi, che contirne il numero di pietre usate per trovare la collana
val_pietre è un vettore di n_pietre interi, che contiene il valore di ogni pietra
maxPossible is z+r+t+s
max è la lughezza massima trovata della collana finora (passato by reference)
maxCollana è la collana più lunga trovata (stesso type di sol)
max_rip è il numero massimo di ripetizioni di una pietra
nVolteConsec è il numero di volte consecutive che la tipologia di pietra attuale è stata aggiunta alla collana

the return value is 0 or 1 (= max possible solution has been found)
*/
int findCollanaR(int pos, int *sol, int *mark, int *markInv, int *val_pietre, int maxPossible, int* max, int *maxCollana, int max_rip, int* maxLenght, int nVolteConsec){
    int addedAtLeasOne = 0;
    for (enum Pietra p=ZAFFIRO; p<=SMERALDO; p++){
        enum Pietra pietraPrecedente;
        // prendi una pietra che possa stare davanti alla prima pietra della collana, in modo che tutte le pietre possano stare all'inizio della collana
        if (pos==0){ pietraPrecedente = regole[p][0]; }
        else {
            pietraPrecedente = sol[pos-1];
        }

        // se tutti i criteri sono soddisfatti, aggiungi la pietra alla collana
        if (isPossible(pietraPrecedente, p, markInv, max_rip, nVolteConsec) && mark[p] > 0){
            sol[pos] = p;
            mark[p]--; markInv[p]++;
            int newNVC;
            if (p==pietraPrecedente){ newNVC = nVolteConsec+1; }
            else { newNVC = 1; }
            
            if (findCollanaR(pos+1, sol, mark, markInv, val_pietre, maxPossible, max, maxCollana, max_rip, maxLenght, newNVC)) { return 1; }
            mark[p]++; markInv[p]--;
            addedAtLeasOne = 1;
        }
    }
    // condizione di terminazione. non serve metterlo prima perchè nel caso si abbia pos=maxLenghtPossible, il vettore mark sarà tutto a 0, quindi sol[pos] non verrà mai eseguito (non c'è errore) e !addedAtLeasOne rimane a true
    if (!addedAtLeasOne){
        // la lunghezza della collana è pos
        int valore = 0;
        for (int i=0; i<pos; i++){ valore += val_pietre[sol[i]]; }
        if (valore > *max){
            *max = valore;
            *maxLenght = pos;
            for (int i=0; i<pos; i++){ maxCollana[i] = sol[i]; }
            if (*maxLenght == maxPossible){ return 1; }
        }
    }
    return 0;
}