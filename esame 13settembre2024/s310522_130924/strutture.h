#include<stdio.h>
#include<stdlib.h>

typedef struct ELENCO_s* ELENCO;
typedef struct DISTMATR_s* DISTMATR;
typedef struct SEDI_s* SEDI;
typedef struct SERVIZI_s* SERVIZI;

// elenco e distmat passaty by reference e NON ancora inizializzati con malloc
void caricaDATI(FILE* fp, ELENCO* e, DISTMATR* m);


char* getNomeCittà(ELENCO e, int i);
// indice_sedi: vettore di M interi contenenti l'indice delle città sede di p.s. nell'elenco generale
SEDI creaSEDI(int M, int* indice_sedi);
void printELENCO(ELENCO e);
void printSEDI(SEDI s, ELENCO e);
void printSERVIZI(SERVIZI s, ELENCO e, SEDI sedi);


/*
 * checkSedi: un pre controllo sulla validità della distribuzione delle sedi, 
 * ritornerà 1 se la distribuzione è valida, 0 altrimenti. Controlla che:
 * - per ogniuna delle altre N-M città esiste almeno una città sede di p.s. a distanza minore di MAXD
 * - ogni città sede di p.s. deve servire almeno MINS città senza p.s. (a distanza < di MAXD)
 */
int checkSedi(DISTMATR m, int MAXD, int MINS, SEDI s);

/*
 * bestPart: funzione che cerca la migliore assegnazione di città senza pronto
 * soccorso a città sede di pronto soccorso, dove per migliore si intende che con
 * distanza media minore tra le città senza p.s. e le città sede di p.s.
 */
SERVIZI bestPart(DISTMATR m, SEDI s, int MINS, int MAXD);