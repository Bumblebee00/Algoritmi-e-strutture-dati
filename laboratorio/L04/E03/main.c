#include <stdio.h>
#include<stdlib.h>

#define n_pietre 4

enum Pietra { ZAFFIRO, RUBINO, TOPAZIO, SMERALDO };

// successivo[TOPAZIO] contiene le pietre che possono stare dopo al topazio
int successivo[n_pietre][2] = {
    {RUBINO, ZAFFIRO},
    {TOPAZIO, SMERALDO},
    {RUBINO, ZAFFIRO},
    {TOPAZIO, SMERALDO},
};

// metodo ricorsivo con esplorazione dello spazio delle soluzioni con powerset e tre criteri di pruning. questa funzione non riesce a trovare la soluzione per il test con 69 pietre (in hard test set)
void findMaxCollana(int *mark);
int findCollanaR(int pos, int *sol, int *mark, int* nOfStones, int* max, int *maxCollana);
// metodo intelligente trovato studiando il problema, non ricorsivo, funziona instantaneamente con qualsiasi numero di pietre
void findMaxCollanaSmart(int *mark);
// funzione di uitility
void printCollana(int *collana, int len);

int main(int argc, char* argv[]){
    int n, z, r, t, s;
    
    if (argc != 2){ printf("Usage: %s <path>", argv[0]); return 1; }
    FILE* fp = fopen(argv[1], "r");
    fscanf(fp, "%d\n", &n);
    for (int i=0;i<n;i++){
        fscanf(fp, "%d %d %d %d\n", &z, &r, &t, &s);
        int mark[n_pietre] = {z, r, t, s};
        printf("Test #%2d:", i);
        
        // findMaxCollana(mark);
        findMaxCollanaSmart(mark);
    }
}

void findMaxCollana(int *mark){
    int maxLenghtFound = 0;
    int nOfStones = 0;
    for (int i=0; i<n_pietre; i++){ nOfStones += mark[i];}
    int *maxCollana = malloc(sizeof(int)*nOfStones); // forse stiamo sovrallocando ma vabbe
    int *sol = malloc(sizeof(int)*nOfStones);

    // first stone choiche is handled outside the recursion
    for (enum Pietra p=ZAFFIRO; p<=SMERALDO; p++){
        if (mark[p] == 0){ continue; }
        sol[0] = p;
        mark[p]--;
        if (findCollanaR(1, sol, mark, &nOfStones, &maxLenghtFound, maxCollana)) { break; }
        mark[p]++;
    }

    printf(" z+r+t+s = %2d Collana massima (di lunghezza %2d): ", nOfStones, maxLenghtFound);
    printCollana(maxCollana, maxLenghtFound);

    free(maxCollana);
    free(sol);
}

/*
pos è l'indice della ricorsione a cui siamo arrivati
sol è la collana che abbiamo composto finora. il numero 0 sta per zaffiro, 1 per rubino, eccetra
mark è un vettore di n_pietre interi, che contirne il numero di pietre ancora disponibili per trovare la collana
nOfStones is z+r+t+s
max è la lughezza massima trovata della collana finora (passato by reference)
maxCollana è la collana più lunga trovata (stesso type di sol)

the return value is 0 or 1 (= max possible solution has been found)
*/
int findCollanaR(int pos, int *sol, int *mark, int* nOfStones, int* max, int *maxCollana){
    int addedAtLeasOne = 0;
    for (int i=0; i<2; i++){
        enum Pietra p = successivo[sol[pos-1]][i];
        // valuta se prunare l'albero
        // - se non ci sono abbastanza pietre, passa alla prossima pietra
        if (mark[p] == 0){ continue; }
        // - se siamo a una ...t, e sono finite le r, la collana continuerà con tutte le z e poi bom
        if (p == TOPAZIO && mark[RUBINO]==0 && mark[ZAFFIRO]>0){
            int len = pos+1+mark[ZAFFIRO];
            addedAtLeasOne=1;
            if (len > *max) {
                *max = len;
                // save this sol
                int i;
                for (i=0; i<pos; i++){ maxCollana[i] = sol[i]; }
                maxCollana[pos] = TOPAZIO;
                i++;
                for (; i<len; i++) { maxCollana[i] = ZAFFIRO; }
                if (*max == *nOfStones){ return 1; }
            }
            // now we calculated this branche and we passiamo alla prossima pietra
            continue;
        }
        // - se siamo a una ...r, e sono finite le t, la collana continuerà con tutte le s e poi bom
        if (p == RUBINO && mark[TOPAZIO]==0 && mark[SMERALDO]>0){
            int len = pos+1+mark[SMERALDO];
            addedAtLeasOne=1;
            if (len > *max) {
                *max = len;
                // save this sol
                int i;
                for (i=0; i<pos; i++){ maxCollana[i] = sol[i]; }
                maxCollana[pos] = RUBINO;
                i++;
                for (; i<len; i++) { maxCollana[i] = SMERALDO; }
                if (*max == *nOfStones){ return 1; }
            }
            // now we calculated this branche and we passiamo alla prossima pietra
            continue;
        }

        sol[pos] = p;
        mark[p]--;
        if (findCollanaR(pos+1, sol, mark, nOfStones, max, maxCollana)) { return 1; }
        mark[p]++;
        addedAtLeasOne = 1;
    }
    // condizione di terminazione. non serve metterlo prima perchè nel caso si abbia pos=nOfStones, il vettore mark sarà tutto a 0, quindi sol[pos] non verrà mai eseguito (non c'è errore) e !addedAtLeasOne rimane a true
    if (!addedAtLeasOne){
        // la lunghezza della collana è pos
        if (pos > *max){
            *max = pos;
            for (int i=0; i<pos; i++){ maxCollana[i] = sol[i]; }
            if (*max == *nOfStones){ return 1; }
        }
    }
    return 0;
}



/*
Dopo numerose considerazioni sono arrivato alla conclusione che ogni collana più lunga sarà scritta come:
- se ci sono più t che r (nella collana vengono usati (n_r) rubini e (n_r + 1) topazi):
  tr...tr ss..ss t zz..zz
- se ci sono più r che t (nella collana vengono usati (n_t) topazi e (n_t + 1) rubini):
  rt...rt zz..zz r ss..ss

questo perchè s e z possono stare in lunghi blocchi (le s dopo una r le z dopo una t) e possono sempre essere messe tutte
r e t invece si possono alternare una all'altra, quindi rtrt... o trtr...
se usiamo la prima   forma (rt), dopo mettiamo le z, poi una r di mezzo e le s. quindi ci devono essere più r che t
se usiamo la seconda forma (tr), dopo mettiamo le s, poi una t di mezzo e le z. quindi ci devono essere più t che r

nel caso t e r siano uguali, possiamo scrivere egualmente
r tr...tr ss..ss t zz..zz
t rt...rt zz..zz r ss..ss

Il ragionamento di prima funziona anche per i casi minimi in cui
t=1 r=1 o
t=1 r=0 o
t=0 r=1
nel caso invece che sia t che r sono 0 (sfigato), la collana sarà solo di z o s
*/

void findMaxCollanaSmart(int *mark){
    int max = 0;
    int nOfStones = 0;
    for (int i=0; i<n_pietre; i++){ nOfStones += mark[i];}
    int *maxCollana = malloc(sizeof(int)*nOfStones); // forse stiamo sovrallocando ma vabbe

    if (mark[TOPAZIO] == 0 && mark[RUBINO] == 0){
        if (mark[SMERALDO] > mark[ZAFFIRO]){
            // ss...ss
            for (int i=0; i<mark[SMERALDO]; i++){ maxCollana[i] = SMERALDO; }
            max = mark[SMERALDO];
        }
        else {
            // zz...zz
            for (int i=0; i<mark[ZAFFIRO]; i++){ maxCollana[i] = ZAFFIRO; }
            max = mark[ZAFFIRO];
        }
    }
    else if (mark[TOPAZIO] > mark[RUBINO]){
        // tr...tr ss..ss t zz..zz
        int i;
        for (i=0; i<mark[RUBINO]; i++){
            maxCollana[2*i]     = TOPAZIO;
            maxCollana[2*i + 1] = RUBINO;
        }
        for (; i<2*mark[RUBINO]+mark[SMERALDO]; i++){
            maxCollana[i] = SMERALDO;
        }
        maxCollana[i] = TOPAZIO;
        i++;
        for (; i<2*mark[RUBINO]+mark[SMERALDO]+1+mark[ZAFFIRO]; i++){
            maxCollana[i] = ZAFFIRO;
        }
        max = 2*mark[RUBINO]+mark[SMERALDO]+1+mark[ZAFFIRO];
    }
    else if (mark[TOPAZIO] < mark[RUBINO]){
        // rt...rt zz..zz r ss..ss
        int i;
        for (i=0; i<mark[TOPAZIO]; i++){
            maxCollana[2*i]     = RUBINO;
            maxCollana[2*i + 1] = TOPAZIO;
        }
        for (; i<2*mark[TOPAZIO]+mark[ZAFFIRO]; i++){
            maxCollana[i] = ZAFFIRO;
        }
        maxCollana[i] = RUBINO;
        i++;
        for (; i<2*mark[TOPAZIO]+mark[ZAFFIRO]+1+mark[SMERALDO]; i++){
            maxCollana[i] = SMERALDO;
        }
        max = 2*mark[TOPAZIO]+mark[ZAFFIRO]+1+mark[SMERALDO];
    }
    else {
        // r tr...tr ss..ss t zz..zz
        maxCollana[0] = RUBINO;
        int i=1;
        for (; i<mark[TOPAZIO]-1; i++){
            maxCollana[2*i]     = TOPAZIO;
            maxCollana[2*i + 1] = RUBINO;
        }
        for (; i<2*mark[TOPAZIO]+mark[SMERALDO]; i++){
            maxCollana[i] = SMERALDO;
        }
        maxCollana[i] = TOPAZIO;
        i++;
        for (; i<2*mark[TOPAZIO]+mark[SMERALDO]+1+mark[ZAFFIRO]; i++){
            maxCollana[i] = ZAFFIRO;
        }
        max = 2*mark[TOPAZIO]+mark[SMERALDO]+mark[ZAFFIRO];
    }

    printf(" z+r+t+s = %2d Collana massima (di lunghezza %2d): ", nOfStones, max);
    printCollana(maxCollana, max);

    free(maxCollana);
}

// funzione di uitility
void printCollana(int *collana, int n){
        for (int i=0; i<n; i++){
        enum Pietra p = collana[i];
        if (p==ZAFFIRO) printf("z");
        else if (p==RUBINO) printf("r");
        else if (p==TOPAZIO) printf("t");
        else if (p==SMERALDO) printf("s");
    } printf("\n");
}