#include "grafo.h"

struct grafo_s{
    int N; // numero di vertici
    int **M; // matrice di adiacenza
    int A; // numero di archi
    Arco *archi; // vettore contenente tutti gli archi. viene inizializzato a N^2 ma può essere tagliato
    TS tabella;
};

Arco creaArco(id from, id to, int wt){
    Arco x;
    x.from = from; x.to = to; x.wt = wt;
    return x;
}

Grafo inizializzaGrafo(int N){
    Grafo g = malloc(sizeof(struct grafo_s));
    g->N = N;
    g->M = malloc(sizeof(int*) * N);
    for (int i=0; i<N; i++){
        (g->M)[i] = malloc(sizeof(int) * N);
    }
    g->A = 0;
    g->archi = malloc(sizeof(Arco)*N*N);
    g->tabella = inizializzaTS(N);
    return g;
}

// non si potranno più aggiungere archi
int cristallizzaGrafo(Grafo g){
    g->archi = realloc(g->archi, sizeof(Arco)*g->A);
    return 0;
}

int G_aggiungiInfoNodo(Grafo g, id info, int indice){
    TS_aggiungiElemento(g->tabella, info, indice);
    // stampaTS(g->tabella);
    return 0;
}

int G_aggiungiArco_ID(Grafo g, id from, id to, int weight){
    (g->M)[TS_getFromId(g->tabella, from)][TS_getFromId(g->tabella, to)] = weight;
    g->archi[g->A] = creaArco(from, to, weight);
    g->A++;
    return 0;
}

int G_rimuoviArco_ID(Grafo g, id from, id to){
    (g->M)[TS_getFromId(g->tabella, from)][TS_getFromId(g->tabella, to)] = 0;
    Arco *tmp = malloc(sizeof(Arco)*(g->A-1));
    int j = 0;
    for (int i=0; i<g->A; i++){
        if (confrontaID(g->archi[i].from, from) != 0 || confrontaID(g->archi[i].to, to) != 0){
            tmp[j] = g->archi[i];
            j++;
        }
    }
    g->A--;
    g->archi = realloc(g->archi, sizeof(Arco)*g->A);
    for (int i=0; i<g->A; i++){ g->archi[i] = tmp[i]; }
    return 0;
}

int G_rimuoviArcoDaM(Grafo g, Arco a){
    (g->M)[TS_getFromId(g->tabella, a.from)][TS_getFromId(g->tabella, a.to)] = 0;
    return 0;
}

int G_aggiungiArcoAM(Grafo g, Arco a){
    (g->M)[TS_getFromId(g->tabella, a.from)][TS_getFromId(g->tabella, a.to)] = a.wt;
    return 0;
}

int dfs_visit(Grafo g, int u, int *color){
    color[u] = 1;
    for (int v=0; v<g->N; v++){
        if ((g->M)[u][v] != 0){
            if (color[v] == 0){
                if (dfs_visit(g, v, color) == 0){ return 0; }
            } else if (color[v] == 1){
                return 0;
            }
        }
    }
    color[u] = 2;
    return 1;
}

// this function returns 1 if the given graph is a DAG, that is, if it has no cycles. Otherwise, it returns 0.
// A directed graph G is acyclic if and only if a depth-first search of G yields no back edges
int èDAG(Grafo g){
    int *color = malloc(sizeof(int)*g->N);
    for (int i=0; i<g->N; i++){ color[i] = 0; }
    for (int i=0; i<g->N; i++){
        if (color[i] == 0){
            if (dfs_visit(g, i, color) == 0){ return 0; }
        }
    }
    return 1;
}

// ritorna un array di id dei nodi sorgenti
id *G_IndividuaNodiSorgenti(Grafo g, int *n){
    id *sorgenti = malloc(sizeof(id)*g->N);
    int j = 0;
    for (int i=0; i<g->N; i++){
        int flag = 0;
        for (int k=0; k<g->N; k++){
            if ((g->M)[k][i] != 0){ flag = 1; break; }
        }
        if (flag == 0){ sorgenti[j] = TS_getFromIndex(g->tabella, i); j++; }
    }
    *n = j;
    return sorgenti;
}

int dfs_visit_max_dist(Grafo g, int u, int *color, int *maxDist, int dist) {
    color[u] = 1;
    if (dist > maxDist[u]) {
        maxDist[u] = dist;
    }
    for (int v = 0; v < g->N; v++) {
        if (g->M[u][v] != 0) {
            if (color[v] == 0) {
                if (!dfs_visit_max_dist(g, v, color, maxDist, dist + g->M[u][v])) {
                    return 0;
                }
            } else if (color[v] == 1) {
                return 0;
            }
        }
    }
    color[u] = 2;
    return 1;
}

int G_distanzaMassima(Grafo g, id from, id to) {
    int fromIndex = TS_getFromId(g->tabella, from);
    int toIndex = TS_getFromId(g->tabella, to);

    // Initialize color array and maximum distances
    int color[g->N], maxDist[g->N];
    for (int i = 0; i < g->N; i++) {
        color[i] = 0;
        maxDist[i] = -1;
    }

    // Run DFS from the source node
    dfs_visit_max_dist(g, fromIndex, color, maxDist, 0);

    // If longest distance to destination is still -1, there is no path from src to dest
    if (maxDist[toIndex] == -1)
        return -1;
    else
        return maxDist[toIndex];
}

int getNumA(Grafo g){ return g->A; }
id getIDfromIndex(Grafo g, int index){ return TS_getFromIndex(g->tabella, index); }
Arco getArco_int(Grafo g, int i){ return (g->archi)[i]; }

void stampaGrafo(Grafo g, FILE *fp){
    printf("Il grafo contiene %d nodi e %d archi. Matrice di adiacenza:\n", g->N, g->A);
    printf("        "); for (int i=0; i<g->N; i++){ printf("%c  ", TS_getFromIndex(g->tabella, i).value); } printf("\n      ╭-"); for (int i=0; i<g->N; i++){ printf("---"); } printf("\n");
    for (int i=0; i<g->N; i++){
        printf("%-2d) %c | ", i, TS_getFromIndex(g->tabella, i).value);
        for (int j=0; j<g->N; j++){
            printf("%-2d ", (g->M)[i][j]);
        }
        printf("\n");
    }
    printf("Elenco archi:\n");
    for (int i=0; i<g->A; i++){
        printf("%d) ", i);
        stampaID(g->archi[i].from);
        printf(" -> ");
        stampaID(g->archi[i].to);
        printf(" (%d)\n", g->archi[i].wt);
    }
}