#include<stdio.h>

typedef struct ELENCO_s* ELENCO;
struct ELENCO_s{
    int N; // numero totale di città
    char** nome_città; // vettore di N stringhe contente i nomi delle città
};

char* getNome(ELENCO e, int i){
    return e->nome_città[i];
}

typedef struct DISTMATR_s* DISTMATR;
struct DISTMATR_s{
    int N;
    int** mat; // NxN matrix
};
int getM(DISTMATR m, int i, int j){
    return m->mat[i][j];
};

typedef struct SEDI_s* SEDI;
struct SEDI_s{
    int M;
    int* sedi; // elenco di M int contenenti l'indice delle città sede di p.s. nell'elenco
 };

// liste usate per le città N-M da assegnare alle N città con p.s.
typedef struct node* link;
struct node{ int i; link next; }; // indice della città nell'elenco
// funzinoe per aggiungere un elemento al fondo di una lista (ritorna la nuova lista)
link addToList(link l, int i){
    link new = malloc(sizeof(struct node));
    new->i = i; new->next == NULL;
    if (l == NULL){ return new; }
    link t = l;
    while (t->next != NULL){ t = t->next; }
    t->next = new;
    return l;   
}
// removes last element form list
link removeFromList(link l){
    // ...
}
typedef struct SERVIZI_s* SERVIZI;
struct SERVIZI_s{
    SEDI sedi_ps; // città sedi del p.s. di riferimento
    link* v; // vettore di M liste, ogni lista contiene le città senza p.s. assegnate alle rispettive città con p.s.
    int* l; // lunghezza delle liste
    int dist_media; // distanza media p.s. - città senza p.s.
};
SERVIZI serviziInit(SEDI s){
    SERVIZI new = malloc(sizeof(struct SERVIZI_s));
    new->sedi_ps = s;
    new->l = malloc(sizeof(int) * s->M);
    for (int i=0; i<s->M; i++){ new->l[i] = NULL; }
        new->v = calloc(s->M, sizeof(link));
    new->dist_media = -1;
    return new;
}


// elenco e distmat passaty by reference e NON ancora inizializzati con malloc
void caricaDATI(FILE* fp, ELENCO* e, DISTMATR* m){
    e = malloc(sizeof(struct ELENCO_s));
    m = malloc(sizeof(struct DISTMATR_s));
    fscanf(fp, "%d", &((*e)->N));
    (*m)->N = (*e)->N;
    for (int i=0; i<(*e)->N; i++){
        fscanf(fp, "%s", (*e)->nome_città[i]);
    }
    for (int i=0; i<(*m)->N; i++){
        for (int j=0; j<(*m)->N; j++){
            fscanf(fp, "%d", (*m)->mat[i][j]);
        }
    }
}

// utility function: returns 1 if an int is in the vectro, 0 otherwise
int elInVector(int* v, int lenght, int el){
    for (int i=0; i<lenght; i++){
        if (v[i] = el){return 1;}
    }
    return 0;
}

int* getCittàSenzaPS(SEDI s, int N, int M){
    int N_M = N - M;
    int* città_no_ps = malloc(sizeof(int) * (N_M));
    int index = 0;
    // per ogni città (indice i)...
    for (int i=0; i<N; i++){
        // se non è nelle città con p.s. (sedi)
        if (!elInVector(s->sedi, M, i)){ città_no_ps[index] = i; index++; }
    }
    return città_no_ps;
}

// per ogniuna delle altre N-M città esiste almeno una città con p.s. a distanza minore di MAXD
// ogni città con p.s. deve servire almeno MINS città senza p.s. (a distanza < di MAXD) // returns 0 if the sol is not valid, 1 if valid
int checkSedi(DISTMATR m, int MAXD, int MINS, SEDI s){
    int N_M = m->N - s->M;
    int* città_no_ps = getCittàSenzaPS(s, m->N, s->M);
    int found;
    for (int i=0; i<N_M; i++){
        found = 0;
        for (int j=0; j<s->M; j++){
            if (m->mat[città_no_ps[i]][s->sedi[j]] <= MAXD){ found = 1; break; }
        }
        if (found = 0){ return 0; } // if there is not even one città con sedi at required distance
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

// runnning out of time...
SERVIZI sol_from_appartenenza_c_n_ps(DISTMATR m, SEDI s, int* appartenenza_c_n_ps){
    int N_M = m->N - s->M;
    int* città_no_ps = getCittàSenzaPS(s, m->N, s->M);
    SERVIZI sol = serviziInit(s->M);
    sol->sedi_ps = s;
    for(int i=0; i<N_M; i++){
        addToList(sol->v[appartenenza_c_n_ps[i]], città_no_ps[i]);
        sol->l[appartenenza_c_n_ps[i]]++;
    }
    // calcola dist_media
    for (int i=0; i<s->M; i++){
    }
    return sol;
}

// return 1 if you can prune, 0 otherwise
// prune if
int prunePart(DISTMATR m, SEDI s, int* appartenenza_c_n_ps, int MINS, int MAXD){
    SERVIZI cuurent_sol = sol_from_appartenenza_c_n_ps(m, s, appartenenza_c_n_ps);
    int MAXS = m->N - MINS * s->M;
    for (int i=0 ; i<s->M; i++){
        if (current_sol->l[i] < MINS || current_sol->l[i] > MAXS){ return 1; }
    }
    return 0;
}

void bestpart_r(DISTMATR m, SEDI s, int MINS, int MAXD, int pos, SERVIZI* best_sol, int* appartenenza_c_n_ps){
    if (prunePart(m, s, appartenenza_c_n_ps, MINS, MAXD)){ return; }
    // condizione terminazione
    if (pos == s->M - m->N){
        SERVIZI current_sol = sol_from_appartenenza_c_n_ps(m, s, appartenenza_c_n_ps);

        if (checkPart(current_sol) && current_sol->dist_media < (*best_sol)->dist_media){
        (*best_sol) = current_sol; // doens't work, i should copy everthing, but i dont have time...
        }
        return;
    }
    // per ogni possibile città con p.s. di appartenenza
    for (int i=0; i<s->M; i++){
        appartenenza_c_n_ps[pos] = s->sedi[i]; // assegnala ala città senza p.s. indicata da pos
        bestpart_r(m, s, MINS, MAXD, pos+1, best_sol, appartenenza_c_n_ps);
    }
}


SERVIZI bestpart(ELENCO e, DISTMATR m, SEDI s, int MINS, int MAXD){
    SERVIZI best_sol = serviziInit(s);
    int M = s->M; int N = m->N;
    int* appartenenza_c_n_ps = malloc(sizeof(int) * (N-M));
    for (int i=0; i<N-M; i++){ appartenenza_c_n_ps[i] = -1; }
    bestpart_r(m, s, MINS, MAXD, 0, &best_sol, appartenenza_c_n_ps);
    // print bestsol
}