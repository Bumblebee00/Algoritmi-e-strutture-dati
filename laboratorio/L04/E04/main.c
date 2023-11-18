#include <stdio.h>
#include<stdlib.h>
#define n_pietre 4

enum Pietra { ZAFFIRO, RUBINO, TOPAZIO, SMERALDO };

// regole[RUBINO] (equivalente a regole[1]) contiene le pietre che possono precedere il rubino, e così via
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
void findMaxCollana(int *mark, int *val_pietre, int max_rip);
int findCollanaR(int pos, int *sol, int *mark, int *markInv, int *val_pietre, int maxPossible, int* max, int *maxCollana, int max_rip, int* maxLenght, int nVolteConsec);
void printCollana(int *collana, int lenght);

int main(){
    int n, z, r, t, s, vz, vr, vt, vs, max_rip;
    FILE* fp = fopen("test_set.txt", "r");
    fscanf(fp, "%d\n", &n);
    for (int i=0;i<n;i++){
        fscanf(fp, "%d %d %d %d  %d %d %d %d %d\n", &z, &r, &t, &s, &vz, &vr, &vt, &vs, &max_rip);
        int mark[n_pietre] = {z, r, t, s};
        int val_pietre[n_pietre] = {vz, vr, vt, vs};
        printf("Test #%2d: ", i+1);
        findMaxCollana(mark, val_pietre, max_rip);
    }
    fclose(fp);
}

void findMaxCollana(int *mark, int *val_pietre, int max_rip){
    int maxValFound = 0;
    int maxLenghtFound = 0;
    int maxLenghtPossible = 0;
    int maxValPoss = 0;
    for (enum Pietra p=ZAFFIRO; p<=SMERALDO; p++){
        maxLenghtPossible += mark[p];
        maxValPoss += mark[p]*val_pietre[p];
    }
    int *maxCollana = malloc(sizeof(int)*maxLenghtPossible); // forse stiamo sovrallocando ma vabbe
    int *sol = malloc(sizeof(int)*maxLenghtPossible);
    int markInv[n_pietre] = {0, 0, 0, 0};

    findCollanaR(0, sol, mark, markInv, val_pietre, maxLenghtPossible, &maxValFound, maxCollana, max_rip, &maxLenghtFound, 0);

    printf("Valore massimo trovato = %4d (usando %2d gemme). Collana massima: ", maxValFound, maxLenghtFound);
    printCollana(maxCollana, maxLenghtFound);

    free(maxCollana);
    free(sol);
}

/*
pos è l'indice della ricorsione a cui siamo arrivati
sol è la collana che abbiamo composto finora. il numero 0 sta per zaffiro, 1 per rubino, eccetra
mark è un vettore di n_pietre interi, che contirne il numero di pietre ancora disponibili per trovare la collana
markInv è un vettore di n_pietre interi, che contirne il numero di pietre usate per trovare la collana. NOTA: in realtà ci serve solo contare gli zaffiri e gli smeraldi, ma li contiamo tutti per generalità
val_pietre è un vettore di n_pietre interi, che contiene il valore di ogni pietra
maxPossible is z+r+t+s
max è la lughezza massima trovata della collana finora (passato by reference)
maxCollana è la collana più lunga trovata (stesso type di sol)
max_rip è il numero massimo di ripetizioni di una pietra
maxLenght è la lunghezza della collana più lunga trovata finora (passato by reference)
nVolteConsec è il numero di volte consecutive che la tipologia di pietra attuale è stata aggiunta alla collana

the return value is 0 or 1 (= max possible solution has been found)
*/
int findCollanaR(int pos, int *sol, int *mark, int *markInv, int *val_pietre, int maxPossible, int* max, int *maxCollana, int max_rip, int* maxLenght, int nVolteConsec){
    int addedAtLeasOne = 0;
    for (enum Pietra p=ZAFFIRO; p<=SMERALDO; p++){
        enum Pietra pietraPrecedente;
        int newNVC = nVolteConsec;
        // calcola tutti i criteri di pruning (sono 4):
        // - la pietra p deve poter stare dopo la pietra precedente
        if (pos==0){ pietraPrecedente = regole[p][0]; } // in caso p sia la prima pietra, può sempre stare lì, quindi prendi una pietra che può di sicuro può precedere p
        else { pietraPrecedente = sol[pos-1]; }
        if (!thisOrderIsPossible(pietraPrecedente, p)){ continue; }
        // - nessuna tipologia di pietra si può ripetere più di max_rip volte consecutive
        if (p==pietraPrecedente){
            newNVC++;
            if (newNVC > max_rip) { continue; }
        }
        else { newNVC = 1; }
        // - ci devono essere abbastanza pietre rimaste
        if (mark[p] == 0) { continue; }
        // - il numero di zaffiri non può superare il numero di smeraldi
        if (markInv[SMERALDO] + (p==SMERALDO) > markInv[ZAFFIRO] + (p==ZAFFIRO)) { continue; }

        // se tutti i criteri sono soddisfatti, aggiungi la pietra alla collana
        sol[pos] = p;
        mark[p]--; markInv[p]++;
        if (findCollanaR(pos+1, sol, mark, markInv, val_pietre, maxPossible, max, maxCollana, max_rip, maxLenght, newNVC)) { return 1; }
        mark[p]++; markInv[p]--;
        addedAtLeasOne = 1;
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

void printCollana(int *collana, int lenght){
    for (int i=0; i<lenght; i++){
        switch (collana[i]){
            case ZAFFIRO: printf("z"); break;
            case RUBINO: printf("r"); break;
            case TOPAZIO: printf("t"); break;
            case SMERALDO: printf("s"); break;
        }
    }
    printf("\n");
}