/*
soluzione1: trovare e salvare tutte le diagonali possibili . dopo trovare la combinazione di diagonali possiblie che massimizza il punteggio.

soluzione2: introdurre un elemento separatore, che separa la fine di una diagonale dall'inizio di un altra. trovare la combianzione di elementi (al più 15) che massimizza il punteggio.

provo con la seconda perchè credo che le diagonali possibili siano tantissime, e memorizzarle tutte sia uno spreco. però boh
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L_PROGR 17 // 15 elements + 2 separators

struct elemento{
    char nome[100];
    int tipologia; // acrobatico avanti [2], acrobatico indietro [1] o di transizione [0]
    int dir_ingresso; // frontalmente [1] o di spalle [0]
    int dir_uscita; // frontalmente [1] o di spalle [0]
    int precedenza; // può essere eseguito come primo di una sequenza [0] o no [1]
    int finale; // può essere seguito da altri elementi [0] o no [1]
    float valore;
    int difficoltà;
};
typedef struct elemento* e;

struct diagonale_s{
    int diag[5];
    int lunghezza;
    int finita;
    int difficoltà;
    float punteggio;
    int ha_un_elemento_acrobatico;
};
typedef struct diagonale_s* diagonale;

struct programma_s{
    diagonale diagonali;
    int diagonale_in_riempimento;
    int bonus;
    float punteggio_tot;
};
typedef struct programma_s* programma;

int addElementoToProgramma(programma p, int elemento, int indice_del_separatore);
void revertDiUno(programma p);

programma findMaxProgramma();
void disp_rip(programma currentP, programma maxP);

e elementi;
int n_elementi, DD, DP;

int main(int argc, char *argv[]){
    //if (argc!=2){ printf("Usage: %s <path>\n", argv[0]); return 1; }

    // FILE* fp = fopen(argv[1], "r");
    FILE* fp = fopen("elementi.txt", "r");
    fscanf(fp, "%d\n", &n_elementi);
    n_elementi++;
    elementi = malloc(sizeof(struct elemento)*(n_elementi));

    for (int i=0; i<n_elementi-1; i++){
        fscanf(fp, "%s %d %d %d %d %d %f %d\n", elementi[i].nome, &elementi[i].tipologia, &elementi[i].dir_ingresso, &elementi[i].dir_uscita, &elementi[i].precedenza, &elementi[i].finale, &elementi[i].valore, &elementi[i].difficoltà);
    }
    fclose(fp);
    strcpy(elementi[n_elementi-1].nome, "SEPARATORE");
    printf("Inserisci il valore massimo di una diagonale e del programma: "); //scanf("%d %d", &DD, &DP);
    DD=10; DP=20;

    programma p = findMaxProgramma();

    printf("DD = %d DP = %d\n", DD, DP);
    printf("TOT = %.3f\n", p->punteggio_tot);
    for (int i=0; i<3; i++){
        printf("DIAG #%d > %.3f", i+1, p->diagonali[i].punteggio);
        if (p->diagonali[i].finita && p->bonus){ printf(" * 1.5 (BONUS)\n"); }
        else{ printf("\n"); }
        for (int j=0; j<p->diagonali[i].lunghezza; j++){
            printf(" %s", elementi[p->diagonali[i].diag[j]].nome);
        }
        printf("\n");
    }
}

programma programmaInit(){
    programma p = malloc(sizeof(struct programma_s));
    p->diagonali = malloc(sizeof(struct diagonale_s)*3);
    p->diagonale_in_riempimento=0;
    return p;
}

programma findMaxProgramma(){
    programma maxP = programmaInit();
    programma currentP = programmaInit();
    disp_rip(currentP, maxP);
    return maxP;
}

/*
n_elementi è il numero di elementi del vettore elementi
currentP è il programma attuale
pos è l'indice di currentP->elementi_i a cui siamo arrivati a rimepire
maxP è il programma a punteggio massimo trovato finora
*/
void disp_rip(programma currentP, programma maxP){
    // condizione terminazione
    if (currentP->diagonale_in_riempimento >= 3){
        // calcola validità e punteggio
        // 1) ha incluso almeno un elemento acrobatico avanti nel corso del suo programma?
        // 2) ha incluso almeno un elemento acrobatico indietro nel corso del suo programma?
        // 3) ha presentato almeno una diagonale in cui compaiono almeno due elementi acrobatici in sequenza?
        // 4) il programma ha una difficolta inferiore a DP?
        // 5) nell'ultima diagonale c'è un elemento di difficoltà >= 8?
        int c1=0, c2=0, c3=0, c4=0, c5=0;
        float punteggio_totale=0;
        for (int i=0; i<3; i++){
            int prev_acrobatico = 0;
            float punteggio_diagonale = 0;
            for (int j=0; j<currentP->diagonali[i].lunghezza; j++){
                int e = currentP->diagonali[i].diag[j];
                if (elementi[e].tipologia>0){ // elemento acrobatico
                    if (elementi[e].tipologia == 2){ c1=1; }
                    if (elementi[e].tipologia == 1){ c2=1; }
                    if (prev_acrobatico){ c3=1; }
                    else { prev_acrobatico=1; }
                }
                if (i==2 && elementi[e].difficoltà>=8){ c5=1;}

                c4 += elementi[e].difficoltà;
                punteggio_diagonale += elementi[e].valore;
            }

            if (c5){ punteggio_diagonale *= 1.5; currentP->bonus=1;}
            currentP->diagonali[i].punteggio = punteggio_diagonale;
            punteggio_totale += punteggio_diagonale;
        }
        if (c4<=DP){ c4=1; }
        else{ c4=0; }

        if (c1 && c2 && c3 && c4 && punteggio_totale>currentP->punteggio_tot){
            currentP->punteggio_tot = punteggio_totale;
            memcpy(maxP, currentP, sizeof(struct programma_s));
        }
    }

    // esplorazione
    for (int i=0; i<n_elementi; i++){
        if (addElementoToProgramma(currentP, i, n_elementi-1)){
            disp_rip(currentP, maxP);
            revertDiUno(currentP);
        }
    }
}

void revertDiUno(programma p){
    if (p->diagonale_in_riempimento>=3){
        p->diagonale_in_riempimento--;
        return;
    }
    diagonale currentD = &(p->diagonali[p->diagonale_in_riempimento]);
    currentD->lunghezza--;
    if (currentD->lunghezza < 0){
        p->diagonale_in_riempimento--;
    }
}

/*
vengono controllate 2 regole qui per prunare:
- ogni diagonale può contenere al massimo 5 elementi
- il ginnasta deve presentare 3 diagonali
- la direzione di uscita del primo elemento deve coincidere con la direzione di ingresso del secondo elemento
- Un ginnasta inizia una diagonale sempre frontalmente
- ha inlcuso almeno un elemento acrobatico in ogni diagonale?
- ogni diagonale ha una difficoltà inferiore a DD?

ritorna 0 (e non aggiunge nulla) se è un agginuta impossibile
ritorna 1 se è possibile
*/

int addElementoToProgramma(programma p, int e, int separator_index){
    // se aggiungiamo un separatore, cambia diagonale in riempimento
    if (e==separator_index){
        p->diagonali[p->diagonale_in_riempimento].finita = 1;
        p->diagonale_in_riempimento++;
        return 1;
    }

    diagonale currentD = &(p->diagonali[p->diagonale_in_riempimento]);
    // se il ginnasta non inizia la diagonale frontalmente
    if(currentD->lunghezza==0){ if (elementi[e].dir_ingresso != 1){ return 0; } }
    // se l'elemento prima non ha la stessa direzione di uscita di quello da aggiungere
    else if (elementi[e].dir_ingresso != elementi[currentD->diag[(currentD->lunghezza)-1]].dir_uscita){ return 0; }
    // se devo aggiungere solo più un elemento
    if (currentD->lunghezza==4){
        // se non è acrobatico, e la diagonale non ha ancora neanche un elemento acrobatico
        if (!(currentD->ha_un_elemento_acrobatico) && elementi[e].tipologia<=0){ return 0; }
        // se aggingendolo straborderò il massimo DD
        if (currentD->difficoltà + elementi[e].difficoltà > DD){ return 0; }
    }

    currentD->diag[currentD->lunghezza] = e;
    currentD->lunghezza++;
    currentD->difficoltà += elementi[e].difficoltà;

    // se è un elemento acrobatico
    if (elementi[e].tipologia>0){ currentD->ha_un_elemento_acrobatico=1; }
    // se la diagnoale è lunga 5, cambia diagonale in riempimento
    if (currentD->lunghezza >= 5){
        currentD->finita = 1;
        p->diagonale_in_riempimento++;
    }

    return 1;
}