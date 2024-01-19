/*
Soluzione Greedy proposta con tre criteri diversi di ordinamanto dei dati.
A seconda del gruppo di esercizi (letti da file) la soluzione puo' esistere o no.
L'ottimo NON e' garantito.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 100  /* massima lunghazza stringa */

#define NDIAG 3   /* numero di diagonali nel programma */
#define MAXE 5    /* numero massimo di elementi per diagonale */

typedef struct elemento {
    char nome[MAXL];
    int tipo;
    int in, out;
    int finale;
    int prec;
    int diff;
    float val;
    float val_rel; // densita' di punteggio
    int preso;
} elemento_t;

struct elementi_s {
    elemento_t *ve;
    int ne; // numero elementi
};
typedef struct elementi_s* elementi;

typedef struct diagonale_s {
    int elementi[MAXE];
    int ne;
    int diff;
    float val;
} diagonale_t;

typedef struct diagonali_s {
    diagonale_t vd[NDIAG];
    int diff;
} diagonali_t;

int DD, DP;

int elementoMigliore(elemento_t *e1, elemento_t *e2) {
    return e1->val_rel > e2->val_rel;
}

/* cerca l'elemento con valore massimo, tra qualli che rispettano i vincoli */
int nextBest(elementi E, int first, int direzione, int diff, int diff_p, int acrob, int cambiadir) {
    int i, iBest=-1;

    for(i=0; i<E->ne; i++) {
        if (!E->ve[i].preso && (E->ve[i].in == direzione) && !(first && E->ve[i].prec) &&
            (diff + E->ve[i].diff <= DD) && (diff_p + E->ve[i].diff <= DP)) {
            if (acrob==0 || E->ve[i].tipo==acrob || (acrob==3 && E->ve[i].tipo>0)) {
                if (cambiadir && E->ve[i].out != direzione) return i;
                if (iBest<0 || elementoMigliore(&(E->ve[i]),&(E->ve[iBest])))
                    iBest = i;
            }
        }
    }
    if (iBest>=0)
        E->ve[iBest].preso = 1;

    return iBest;
}

int verificaAcrobatici(diagonale_t *diag, elementi el, int i, int acrob) {
    /* se trovato l'elemento acrobatico (unico) cercato, non cercarlo piu' */
    int curr = diag->elementi[i];
    if ((acrob == 1 || acrob == 2) && el->ve[curr].tipo == acrob)
        return 0;
    /* verifica sequenza */
    else if (acrob == 3 && i>0 && el->ve[curr].tipo != 0) {
        /* elemento acrobatico trovato dalla seconda posizione in poi */
        int prev = diag->elementi[i-1];
        /* se precedente acrobatico : disabilita */
        if (el->ve[prev].tipo != 0)
            return 0;
    }
    return acrob; /* non trovato ritorna acrob come ottenuto in ingresso */
}

/* obiattivo: completare una diagonale (diag) con elementi presi da el
   diff_iniziale; serve per verificare il vincolo sulla difficolta' massima del programma
   acrob: eventuale vincolo/richiesta su elementi acrobatici */
int diagonale(diagonale_t *diag, elementi el, int diff_iniziale, int acrob) {
    int i, next;
    int diff=0;
    int direzione = 1;

    diag->ne=0;
    diag->val=0.0;
    for(i=0; i<el->ne; i++) {
        el->ve[i].preso = 0;
    }
    for (i=0; i<MAXE; i++) {
        /* primo giro (eventualmente cerca un esercizio acrobatico (acrob = 1, 2, o 3) */
        next = nextBest(el, i==0, direzione, diff, diff+diff_iniziale,acrob,0);
        if (acrob && next<0) {
            /* cercato elemento acrobatico e non trovato: ritenta
               cerca non acrobatico e cambia direzione */
            next = nextBest(el, i==0, direzione, diff, diff+diff_iniziale,0,1);
        }
        if (next<0) break; /* uscita non strutturata - nessuna ulteriore scelta possibile */
        direzione = el->ve[next].out;
        diff += el->ve[next].diff;
        diag->elementi[i] = next;
        diag->ne++;
        diag->val += el->ve[next].val;
        acrob = verificaAcrobatici(diag,el,i,acrob);
    }
    diag->diff = diff;
    /* almeno un elemento e richiesta elementi acrobatici soddisfatta */
    return (diag->ne>0 && acrob==0);
}

int checkBonus(diagonali_t *prog, elementi E) {
    int i, j, bonus = -1;
    /* una qualunque diagonale puo' avere il bonus. Eventualmente andranno permutate per
       avere il bonus nell'ultima diagonale */

    for (i=0; i<NDIAG; i++) {
        j=prog->vd[i].ne-1;
        if (E->ve[j].tipo > 0 && E->ve[prog->vd[i].elementi[j]].diff > 7) {
            if (bonus == -1 || (prog->vd[bonus].val < prog->vd[i].val))
                bonus = i;
        }
    }
    return bonus;
}

void greedy(elementi E) {
    int i, j, bonus = -1;
    float val = 0.0;
    int diff_tot = 0;
    diagonali_t prog; /* struct contenente un vettore di 3 diagonali */
    int acrob=0;
    int valido=1;

    /* Costruzione del programma una diagonale alla volta */
    /* richieste:
       prima diagonale: elemento acrobatico avanti (1)
       seconda diagonale: elemento acrobatico indietro (2)
       terza diagonale: due elementi acrobatici in sequan\za (3)\
     */
    for(i=0; valido && i<NDIAG; i++) {
        /* DIAGONALE i */
        acrob++; /* acrob = 3 per sequenza */
        valido &= diagonale(&prog.vd[i],E,diff_tot,acrob);
        if (valido) {
            diff_tot += prog.vd[i].diff;
            val += prog.vd[i].val;
        }
    }

    if (valido) {
        bonus = checkBonus(&prog,E);
        if (bonus>=0) {
            val += 0.5 * prog.vd[bonus].val;
        }
        printf("TOT = %f\n", val);
        for(i=0;i<NDIAG;i++) {
            printf("DIAG %d > %.3f %s\n", i, prog.vd[i].val, ((bonus == i) ? "BONUS" : ""));
            for(j=0;j<prog.vd[i].ne;j++) printf("%s ", E->ve[prog.vd[i].elementi[j]].nome);
            printf("\n");
        }
    } else {
        printf("Programma non valido\n");
    }
}

int main(void) {
    // leggi file e crea vettore di elementi
    FILE* fp = fopen("elementi.txt", "r");
    elementi E = malloc(1 * sizeof(*E));
    fscanf(fp, "%d", &E->ne);
    E->ve = calloc(E->ne, sizeof(elemento_t));
    for(int i=0;i<E->ne;i++) {
        fscanf(fp, "%s %d %d %d %d %d %f %d\n", E->ve[i].nome, &E->ve[i].tipo, &E->ve[i].in, &E->ve[i].out, &E->ve[i].prec, &E->ve[i].finale, &E->ve[i].val, &E->ve[i].diff);
        E->ve[i].val_rel = E->ve[i].val / (float) E->ve[i].diff;
    }
    fclose(fp);

    printf("Inserisci DD e DP separati da uno spazio: ");
    scanf("%d %d", &DD, &DP);
    printf("Soluzione Greedy:\n");
    greedy(E);
}
