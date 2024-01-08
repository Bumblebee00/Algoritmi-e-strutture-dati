/*
trovare e salvare tutte le diagonali possibili. dopo trovare la combinazione di diagonali possiblie che massimizza il punteggio.
Abbiamo 19 elementi e una prima stima del numero di diagonali possibili è 19^5 = 2.476.099, combinate in (19^5)^3 = 1,518e19. In realtà saranno molto meno. le diagonali saranno salvare in un vettore o lista? vettore dovrei fare un alloc da 2,4M*(sizeof diagonale tipo 28 byte) = 69 Mbyte che però sarà sovrallocatissima. il vantaggio è che non devo scrivere il codice per le liste. il vantaggio delle liste sarebbe non sprecare memoria... e non mi sembra altro. Per trovare tutte le diagonali possibili utilizzerò il modello delle disposizioni ripetute
per trovare la comb di diagonali che massimizza il punteggio userò la strategia delle disposizioni ripetute. perciò non serve che il vettore sia ordinato nè niente.
*/
#include<stdio.h>
#include<stdlib.h>

#define LUNGHEZZA_DIAG 5
#define MAX_C 100

struct elemento{
    char nome[MAX_C];
    int tipologia; // acrobatico avanti [2], acrobatico indietro [1] o di transizione [0]
    int dir_ingresso; // frontalmente [1] o di spalle [0]
    int dir_uscita; // frontalmente [1] o di spalle [0]
    int precedenza; // può essere eseguito come primo di una sequenza [0] o no [1]
    int finale; // può essere seguito da altri elementi [0] o no [1]
    float valore;
    int difficoltà;
};
typedef struct elemento* Elemento;

struct diagonale_s{
    int elementi[LUNGHEZZA_DIAG];
    int difficoltà;
    float punteggio;
};
typedef struct diagonale_s* Diagonale;

void trovaDiagonali(Diagonale sol, int pos, Diagonale diagonali, int* n_diagonali, Elemento elementi, int n_elementi, int k, int DD);
void trovaProgramma(int sol[3], int pos, Diagonale diagonali, int n_diagonali, Elemento elementi, int n_elementi, int DP, int programma_max[3], float *punteggio_max);

int main(){
    int n_elementi, DD, DP, n_diagonali_max, n_diagonali;
    Elemento elementi;
    Diagonale diagonali;

    printf("Inserisci i valore di DD e DP separati da uno spazio: ");
    scanf("%d %d", &DD, &DP);

    FILE* fp = fopen("elementi.txt", "r");
    fscanf(fp, "%d\n", &n_elementi);
    elementi = malloc(sizeof(struct elemento)*(n_elementi));
    for (int i=0; i<n_elementi; i++){
        fscanf(fp, "%s %d %d %d %d %d %f %d\n", elementi[i].nome, &elementi[i].tipologia, &elementi[i].dir_ingresso, &elementi[i].dir_uscita, &elementi[i].precedenza, &elementi[i].finale, &elementi[i].valore, &elementi[i].difficoltà);
    }
    fclose(fp);

    // trova tutte le diagonali
    n_diagonali_max = 1;
    for (int i=0; i<LUNGHEZZA_DIAG; i++){ n_diagonali_max *= n_elementi; }
    diagonali = malloc(sizeof(struct diagonale_s)*n_diagonali_max);

    n_diagonali = 0;
    Diagonale sol_d = malloc(sizeof(struct diagonale_s));
    for (int l=1; l<=LUNGHEZZA_DIAG; l++){
        trovaDiagonali(sol_d, 0, diagonali, &n_diagonali, elementi, n_elementi, l, DD);
    }
    printf("%d diagonali trovate\n", n_diagonali);

    // trova il programma che massimizza il punteggio
    int sol_p[3], programma_max[3];
    float punteggio_max;
    trovaProgramma(sol_p, 0, diagonali, n_diagonali, elementi, n_elementi, DP, programma_max, &punteggio_max);

    printf("Il programma massimo, con punteggio %f, è:\n", punteggio_max);
    for (int i=0; i<3; i++){
        printf("Diag %d (%f): ", i, diagonali[programma_max[i]].punteggio);
        for (int j=0; j<LUNGHEZZA_DIAG; j++){
            printf("%s ", elementi[diagonali[programma_max[i]].elementi[j]].nome);
        }
        printf("\n");
    }
}

/*
sol è la diagonale in riempimento
pos è l'indice di riempimento a cui siamo arrivati
diagonali è il vettorone dove salviamo tutte la diagonali
n_diagonali è il numero di diagonali (che viene aumentato)
elementi e n_elementi
k è la lunghezza delle diagonali da formare
DD è la difficoltà massima della diagnoale

Una volta riempita la diagonale valuteremo le seguenti condizioni:
- ogni diagonale non può avere difficoltà superiore a un dato valore DD
- Un ginnasta inizia una diagonale sempre frontalmente.
- la direzione di uscita di un elemento deve coincidere con la direzione di ingresso del successivo elemento.
- il ginnasta deve includere almeno un elemento acrobatico in ogni diagonale
- un elememento (precedenza = 1) non può stare all'inizio
- un elemento finale (finale = 1) non può essere seguito da altri elementi (la diag non è valida se c'è un finale non alla fine)
*/
void trovaDiagonali(Diagonale sol, int pos, Diagonale diagonali, int* n_diagonali, Elemento elementi, int n_elementi, int k, int DD){
    if (pos >= k){
        // controlla se valida
        if (sol->difficoltà > DD){ return; }
        if (elementi[sol->elementi[0]].dir_ingresso == 0){ return; }
        if (elementi[sol->elementi[0]].precedenza == 1){ return; }
        int ha_acrobatico = 0;
        int cond_ingr_usc = 1;
        int ha_final_in_mezzo = 0;
        for (int i=0; i<k; i++){
            if (elementi[sol->elementi[i]].tipologia > 0){ ha_acrobatico=1; }
            if (i!=k-1 && elementi[sol->elementi[i]].dir_uscita != elementi[sol->elementi[i+1]].dir_ingresso){ cond_ingr_usc = 0; break; }
            if (i!=k-1 && elementi[sol->elementi[i]].finale==1){ ha_final_in_mezzo=1; break; }
        }
        if (!ha_acrobatico || !cond_ingr_usc || ha_final_in_mezzo){ return; }

        // mette nell'array
        diagonali[*n_diagonali].difficoltà = sol->difficoltà;
        diagonali[*n_diagonali].punteggio = sol->punteggio;
        for (int i=0; i<k; i++){ diagonali[*n_diagonali].elementi[i] = sol->elementi[i]; }
        for (int i=k; i<LUNGHEZZA_DIAG; i++){ diagonali[*n_diagonali].elementi[i] = -1; }
        (*n_diagonali)++;
        return;
    }

    for (int e=0; e<n_elementi; e++){
        sol->elementi[pos] = e;
        sol->difficoltà += elementi[e].difficoltà;
        sol->punteggio += elementi[e].valore;

        trovaDiagonali(sol, pos+1, diagonali, n_diagonali, elementi, n_elementi, k, DD);

        sol->difficoltà -= elementi[e].difficoltà;
        sol->punteggio -= elementi[e].valore;
    }
}


/*
sol è il programma in riempimento (indici delle diagnoali nel vettore diagonali)
pos è l'indice di riempimento a cui siamo arrivati
diagonali è il vettorone dove salviamo tutte la diagonali
n_diagonali è il numero di diagonali trovate
elementi e n_elementi
DP è la difficoltà massima del programma
programma_max è il programma amssimo trovato finora
punteggio_max

Una volta riempito il programma valuteremo le seguenti condizioni:
- il ginnasta deve includere almeno un elemento acrobatico avanti e almeno un elemento acrobatico indietro nel corso del suo programma, ma non necessariamente nella stessa diagonale
- il ginnasta deve presentare almeno una diagonale in cui compaiono almeno due elementi acrobatici in sequenza
- se il ginnasta include un elemento finale di difficoltà 8 o superiore nell'ultima diagonale presentata in gara, il punteggio complessivo della diagonale viene moltiplicato per 1.5
- il programma complessivamente non può avere difficoltà superiore a un dato valore DP.

*/
void trovaProgramma(int sol[3], int pos, Diagonale diagonali, int n_diagonali, Elemento elementi, int n_elementi, int DP, int programma_max[3], float *punteggio_max){
    if (pos >= 3){
        // controlla se valido e calcola punteggio
        float punteggio = 0;
        int ha_el_acr_avanti = 0;
        int ha_el_acr_indietro = 0;
        int due_el_acr_in_seq = 0;

        for (int i=0; i<3; i++){
            int precedente_acrobatico = 0;
            int el_di_diff_8_o_sup = 0;

            for (int j=0; j<LUNGHEZZA_DIAG; j++){
                int tmp = elementi[diagonali[sol[i]].elementi[j]].tipologia;
                // se elemento acrobatico
                if (tmp>0){
                    if (tmp == 2){ ha_el_acr_avanti=1; }
                    else if (tmp == 1){ ha_el_acr_indietro=1; } // anche else e basta andrebbe bene
                    if (precedente_acrobatico){ due_el_acr_in_seq=1; }
                    precedente_acrobatico = 1; // per la prossima iterazione
                } else { precedente_acrobatico = 0; }
                if (elementi[diagonali[sol[i]].elementi[j]].difficoltà >= 8){ el_di_diff_8_o_sup=1; }
            }

            punteggio += diagonali[sol[i]].punteggio * ((i==2 && el_di_diff_8_o_sup) ? 1.5 : 1.0);
        }

        if (punteggio < DP && ha_el_acr_avanti && ha_el_acr_indietro && due_el_acr_in_seq && punteggio > *punteggio_max){
            *punteggio_max = punteggio;
            printf("newmax (%f): ", *punteggio_max);
            for (int i=0; i<3; i++){
                printf("%d ", sol[i]);
                programma_max[i] = sol[i];
            }
            printf("\n");
        }

        return;
    }

    for (int i=0; i<n_diagonali; i++){
        sol[pos] = i;
        trovaProgramma(sol, pos+1, diagonali, n_diagonali, elementi, n_elementi, DP, programma_max, punteggio_max);
    }
}