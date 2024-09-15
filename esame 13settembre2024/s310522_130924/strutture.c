#include"strutture.h"
#include<stdio.h>
#include<stdlib.h>

struct ELENCO_s{
    int N; // numero totale di città
    char** nome_città; // vettore di N stringhe contente i nomi delle città
};

void printELENCO(ELENCO e){
    printf("Elenco delle città:\n");
    for (int i=0; i<e->N; i++){
        printf("%s\n", e->nome_città[i]);
    }
    printf("\n");
}

char* getNome(ELENCO e, int i){
    return e->nome_città[i];
}

struct DISTMATR_s{
    int N;
    int** mat; // NxN matrix
};

// elenco e distmat passaty by reference e NON ancora inizializzati con malloc
void caricaDATI(FILE* fp, ELENCO* e, DISTMATR* m){
    *e = malloc(sizeof(struct ELENCO_s));
    *m = malloc(sizeof(struct DISTMATR_s));
    fscanf(fp, "%d", &((*e)->N));

    (*m)->N = (*e)->N;
    (*e)->nome_città = malloc(sizeof(char*) * (*e)->N);
    for (int i=0; i<(*e)->N; i++){
        (*e)->nome_città[i] = malloc(sizeof(char) * 100);
        fscanf(fp, "%s", (*e)->nome_città[i]);
    }

    (*m)->mat = malloc(sizeof(int*) * (*m)->N);
    for (int i=0; i<(*m)->N; i++){
        (*m)->mat[i] = malloc(sizeof(int) * (*m)->N);
        for (int j=0; j<(*m)->N; j++){
            fscanf(fp, "%d", &(*m)->mat[i][j]);
        }
    }
}

struct SEDI_s{
    int M;
    int* sedi; // elenco di M int contenenti l'indice delle città sede di p.s. nell'elenco generale
};

// indice_sedi: vettore di M interi contenenti l'indice delle città sede di p.s. nell'elenco generale
SEDI creaSEDI(int M, int* indice_sedi){
    SEDI new = malloc(sizeof(struct SEDI_s));
    new->M = M;
    new->sedi = malloc(sizeof(int) * M);
    for (int i=0; i<M; i++){ new->sedi[i] = indice_sedi[i]; }
    return new;
}

// utility function: returns 1 if an int is in the vectro, 0 otherwise
int elInVector(int* v, int lenght, int el){
    for (int i=0; i<lenght; i++){
        if (v[i] == el){return 1;}
    }
    return 0;
}

// utility function: returns a vector of N-M elements containing the index of the cities without p.s.
int* getCittàSenzaPS(SEDI s, int N, int M){
    int* città_no_ps = malloc(sizeof(int) * (N-M));
    int index = 0;
    for (int i=0; i<N; i++){
        if (!elInVector(s->sedi, M, i)){ città_no_ps[index] = i; index++; }
    }
    return città_no_ps;
}

/*
 * per ognuna delle altre N-M città esista almeno una città sede di p.s. a distanza minore di MAXD
 * ogni città sede di p.s. deve servire almeno MINS città senza p.s. (a distanza < di MAXD)
 * returns 0 if the sol is not valid, 1 if valid
 */
int checkSedi(DISTMATR m, int MAXD, int MINS, SEDI s){
    int N_M = m->N - s->M;
    int* città_no_ps = getCittàSenzaPS(s, m->N, s->M);
    int found;
    for (int i=0; i<N_M; i++){
        found = 0;
        for (int j=0; j<s->M; j++){
            if (m->mat[città_no_ps[i]][s->sedi[j]] <= MAXD){ found = 1; break; }
        }
        if (found == 0){ return 0; }
    }
    int n_servite;
    for (int i=0; i<s->M; i++){
        n_servite = 0;
        for (int j=0; j<N_M; j++){
            if (m->mat[città_no_ps[i]][s->sedi[j]] <= MAXD){ n_servite++; }
        }
        if (n_servite < MINS){ return 0; }
    }
    return 1; // se ha passato tutti i check...
}

/*
 * struct SERVIZI_s:
 * - N: numero totale di città
 * - M: numero di città con pronto soccorso
 * - dist_media: distanza media tra le città sede di p.s. e le città senza p.s.
 * - città_no_ps: vettore di N-M interi. indici nell'elenco generale delle
 *   città senza p.s.
 * - sol: vettore di N-M interi. l'i-esimo elemento è l'indice (nell'elenco 
 *   generale) della città a cui l'i-esima città senza p.s. è stata assegnata
 * - servite: vettore di M interi. l'i-esimo elemento è il numero di città senza 
 *   pronto soccorso servite dalla i-esima città sede di p.s. (che ha indice
 *   nell'elenco generale pari a sedi_ps->sedi[i])
 * 
 * Nota: il vettore servite si può calcolare a partire dal vettore sol, ma è
 *       comodo averlo già calcolato per fare i controlli
 * Nota: città_no_ps si può ricavare da sedi_ps->sedi, ma è comodo averlo già
 *      calcolato per fare i controlli
 */
struct SERVIZI_s{
    int N, M;
    float dist_media;
    int *città_no_ps;
    int* sol;
    int* servite;
};

SERVIZI serviziInit(int N, SEDI sedi_ps){
    int M = sedi_ps->M;
    SERVIZI new = malloc(sizeof(struct SERVIZI_s));
    
    // inizializza i campi della struct
    new->N = N; new->M = M; new->dist_media = 9999999.0;
    // inizializza il vettore delle città servite a 0
    new->servite = malloc(sizeof(int) * M);
    for (int i=0; i<M; i++){ new->servite[i] = 0; }
    // inizializza il vettore sol con -1
    new->sol = malloc(sizeof(int) * (N-M));
    for (int i=0; i<N-M; i++){ new->sol[i] = -1; }
    // inizializza e calcola il vettore delle città senza p.s.
    new->città_no_ps = getCittàSenzaPS(sedi_ps, N, M);
    
    return new;
}

SERVIZI copySERVIZI(SERVIZI s, int N, SEDI sedi_ps){
    SERVIZI new = serviziInit(N, sedi_ps);
    new->dist_media = s->dist_media;
    for (int i=0; i<s->N - s->M; i++){
        new->sol[i] = s->sol[i];
    }
    return new;
}



/*
 * return 1 if you can prune, 0 otherwise
 * prune if:
 * (1) a city with p.s. has more than MAXS cities without p.s. assigned to it
 * (2) distance greater than MAXD (its enought to check the last assignment
 *     because prunePart is called recursively)
 */
int prunePart(DISTMATR m, SEDI s, SERVIZI current_sol, int MINS, int MAXD, int pos){
    if (pos == 0){ return 0; }
    // (1)
    int MAXS = m->N - s->M - MINS * (s->M - 1);
    for (int i=0; i<current_sol->M; i++){if (current_sol->servite[i] > MAXS){ return 1; } }
    // (2)
    if (m->mat[current_sol->sol[pos-1]][current_sol->città_no_ps[pos-1]] > MAXD){ return 1; }

    return 0;
}



/*
 * checkPart: ritorna 1 se la soluzione è valida, 0 altrimenti
 * (1) controlla che a ognuna delle sedi di pronto soccorso si assegnano almeno MINS città.
 * (2) controlla che ogni città sia a distanza minore di MAXD da almeno una città sede di p.s.
 *     (in realtà viene già controllato in prunePart)
 * (3) calcola la distanza media tra le città sede di p.s. e le città senza p.s.
 */
int checkPart(SERVIZI current_sol, int MINS, DISTMATR m, SEDI sedi){
    // (1)
    for (int i=0; i<current_sol->M; i++){ if (current_sol->servite[i] < MINS){ return 0; } }
    // (3)
    current_sol->dist_media = 0.0;
    for (int i=0; i<current_sol->N - current_sol->M; i++){
        current_sol->dist_media += m->mat[current_sol->città_no_ps[i]][current_sol->sol[i]];
    }
    current_sol->dist_media = current_sol->dist_media / (current_sol->N - current_sol->M);
    return 1;
}



/*
 * pos: indice che scorre su tutte N-M le città senza pronto soccorso
 * best_sol: soluzione migliore trovata finora
 * current_sol: soluzione corrente
 */
void bestPart_r(DISTMATR m, SEDI sedi_ps, int MINS, int MAXD, int pos, SERVIZI* best_sol, SERVIZI current_sol){
    // pruning
    if (prunePart(m, sedi_ps, current_sol, MINS, MAXD, pos)){ return; }
    // condizione terminazione
    if (pos == m->N - sedi_ps->M){        
        if (checkPart(current_sol, MINS, m, sedi_ps) && current_sol->dist_media < (*best_sol)->dist_media){
            *best_sol = copySERVIZI(current_sol, m->N, sedi_ps);
        }
        return;
    }
    // assegna alla città senza p.s. corrente ogni possibile città sede di p.s.
    for (int i=0; i<sedi_ps->M; i++){
        current_sol->sol[pos] = sedi_ps->sedi[i];
        current_sol->servite[i]++;
        bestPart_r(m, sedi_ps, MINS, MAXD, pos+1, best_sol, current_sol);
        current_sol->servite[i]--;
    }
}


/*
 * bestPart: funzione che cerca la migliore assegnazione di città senza pronto
 * soccorso a città con pronto soccorso, dove per migliore si intende che con
 * distanza media minore tra le città senza p.s. e le città sede di p.s.
 */
SERVIZI bestPart(DISTMATR m, SEDI sedi_ps, int MINS, int MAXD){
    SERVIZI best_sol = serviziInit(m->N, sedi_ps);
    SERVIZI current_sol = serviziInit(m->N, sedi_ps);
    bestPart_r(m, sedi_ps, MINS, MAXD, 0, &best_sol, current_sol);
    // print bestsol
    return best_sol;
}

void printSEDI(SEDI s, ELENCO e){
    printf("Sedi di pronto soccorso:\n");
    for (int i=0; i<s->M; i++){
        printf("%s\n", getNome(e, s->sedi[i]));
    }
    printf("\n");
}

void printSERVIZI(SERVIZI s, ELENCO e, SEDI sedi){
    if (s->dist_media == 9999999.0){
        printf("Nessuna soluzione trovata\n");
        return;
    }
    printf("Assegnazione città con pronto soccorso:\n");
    for (int i=0; i<s->N - s->M; i++){
        printf("%s (senza p.s.) assegnata a %s (con p.s.)\n", getNome(e, s->città_no_ps[i]), getNome(e, s->sol[i]));
    }
    printf("Distanza media tra città sede di p.s. e città senza p.s.: %.2f\n", s->dist_media);
}