#include<stdio.h>
#include<stdlib.h>

typedef struct ELENCO_s* ELENCO;
typedef struct DISTMATR_s* DISTMATR;
typedef struct SEDI_s* SEDI;


// liste usate per le città N-M da assegnare alle N città con p.s.
typedef struct node* link;
struct node{ int i; link next; }; // indice della città nell'elenco
// funzinoe per aggiungere un elemento al fondo di una lista (ritorna la nuova lista)
link addToList(link l, int i);

typedef struct SERVIZI_s* SERVIZI;


char* getNome(ELENCO e, int i);
SERVIZI serviziInit(SEDI s);
// elenco e distmat passaty by reference e NON ancora inizializzati con malloc
void caricaDATI(FILE* fp, ELENCO* e, DISTMATR* m);

int* getCittàSenzaPS(SEDI s, int N, int M);

// per ogniuna delle altre N-M città esiste almeno una città con p.s. a distanza minore di MAXD
// ogni città con p.s. deve servire almeno MINS città senza p.s. (a distanza < di MAXD) // returns 0 if the sol is not valid, 1 if valid
int checkSedi(DISTMATR m, int MAXD, int MINS, SEDI s);

// runnning out of time...
SERVIZI sol_from_appartenenza_c_n_ps(DISTMATR m, SEDI s, int* appartenenza_c_n_ps);

// return 1 if you can prune, 0 otherwise
// prune if
int prunePart(DISTMATR m, SEDI s, int* appartenenza_c_n_ps, int MINS, int MAXD);


SERVIZI bestpart(ELENCO e, DISTMATR m, SEDI s, int MINS, int MAXD);