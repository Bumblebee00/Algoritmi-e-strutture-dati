[9/02/24] In questa lezione definiamo Gli alberi ricoprenti minimi e analizziamo due algoritmi per trovarli: Kruskal e Prim.

- [Alberi ricoprenti minimi](#alberi-ricoprenti-minimi)
  - [Definizione](#definizione)
  - [Rappresentazione in c](#rappresentazione-in-c)
  - [Approccio del calcolo combiantorio](#approccio-del-calcolo-combiantorio)
  - [Approccio Greedy](#approccio-greedy)
    - [Teorema sugli archi sicuri](#teorema-sugli-archi-sicuri)
    - [Corollario](#corollario)
  - [Algoritmo di Kruskal](#algoritmo-di-kruskal)
    - [Pseudocodice](#pseudocodice)
    - [Struttura dati](#struttura-dati)
    - [Implementazione](#implementazione)
    - [Complessità](#complessità)
  - [Algoritmo di Prim](#algoritmo-di-prim)
    - [Pseudocodice](#pseudocodice-1)
    - [Strutture dati](#strutture-dati)
    - [Complessità](#complessità-1)

# Alberi ricoprenti minimi

## Definizione
Sia dato un grafo G=(V,E) con V insieme dei vertici e E insieme degli archi. G è un grafo non orientato, pesato, connesso. Un albero ricoprente minimo (o Minimum Weight Spanning Tree - MST) è un sottografo G' di G tale che:
- G' = (V, A) con A sottoinsieme di E (qundi stessi vertici, alcuni archi)
- G' è un albero, cioè un grafo connesso e aciclico
- la somma dei pesi degli archi di A è minima

L'albero MST è unico se e solo se i pesi degli archi sono tutti distinti.

## Rappresentazione in c
Il grafo originale viene rappresentato con un ADT grafo normale. Nella matrice di adiacenza, per segnalare l'assenza dell'arco, unsiamo un valore `maxWT` idealmente infinito.

il MST può essere rappresentato con un array di archi (usato nell'algoritmo di Kruskal), o con un grafo (quindi lista di adiacenza) o con due vettori, uno per i pesi dei vertici e uno per i padri dei vertici (usato nell'algoritmo di Prim).

## Approccio del calcolo combiantorio
Potremmo usare i modelli del caclolo combiantorio per provare con tutti i possibili sottografi. Possiamo fare un pò di pruning perchè il MST avrà esattametne V-1 archi (se ne avesse di più, avrebbe un ciclo, se ne avesse di meno, non sarebbe connesso). Inoltre non tutti i sottoinsiemi di V-1 archi sono accettabili, alcuni non sono alberi, altri non sono connessi.

## Approccio Greedy
In questo specifico caso si può dimostrare che l'approccio greedy porta alla soluzione globalmente ottima. Usiamo un algorimo incrementale, cioè che a ogni step aggiunge un elemento alla soluzione.

La soluzione A corrente è un sottoinsieme degli archi di un albero ricoprente minimo.
- inizialmente A è l’insieme vuoto
- ad ogni passo si aggiunge ad A un arco “sicuro”
- fino a quando A non diventa un albero ricoprente minimo.

Il problema è determinare un arco “sicuro” da aggiungere ad A. l’arco (u,v) è sicuro se e solo se aggiunto ad un sottoinsieme di un albero ricoprente minimo produce ancora un sottoinsieme di un albero ricoprente minimo. Per trovarlo dobbiamo prima definire alcuni concetti.

> DEF(taglio): Dato un grafo G non orientato pesato e connesso, si definisce taglio (S, V\S) di G una partizione di V in due insiemi disgiunti S e V\S. Si dice che un taglio rispetta un sottoinsieme di archi A di G se nessun arco di A ha un estremo in S e l’altro in V\S, cioè se nessun arco di A attraversa il taglio.

![](<taglio rispetta.png>)

> DEF(arco leggero): Dato un grafo G non orientato pesato e connesso, si definisce arco leggero di un taglio (S, V\S) un arco (u,v) di G che attraversa il taglio tale che il peso di (u,v) è minimo tra tutti gli archi che attraversano il taglio.

![](<arco leggero.png>)

### Teorema sugli archi sicuri
Dati:
- un grafo G=(V,E) non orientato, pesato e connesso
- un sottoinsieme di archi A di G che è contenuto in un albero ricoprente minimo di G
- un taglio (S, V\S) di G che rispetta A
- un arco leggero (u,v) del taglio dato (S, V\S)

Allora l’arco (u,v) è sicuro per A.

su questo teorema si basa l'algoritmo di Prim.

### Corollario
Dati:
- un grafo G=(V,E) non orientato, pesato e connesso
- un sottoinsieme di archi A di G che è contenuto in un albero ricoprente minimo di G
- un albero C di G che fa parte di una foresta di alberi di G
- un arco (u,v) di G che collega un vertice di C ad un vertice di un albero diverso da C

Allora esiste un arco sicuro per A che collega un vertice di C ad un vertice di un albero diverso da C.

su questo corollario si basa l'algoritmo di Kruskal.

## Algoritmo di Kruskal
### Pseudocodice
si inizia da una foresta formata da alberi, ogni albero composto da un singolo vertice
si itera su tutti gli archi in ordine crescente di peso
se un arco connette due alberi diversi, i due alberi diventano uno solo connessi da quell'arco
se un arco connette due vertici dello stesso albero, si scarta l'arco perchè creerebbe un ciclo
quando tutti i vertici sono rinuiti in un solo albero, l'algoritmo termina.

### Struttura dati
Useremo l'adt di prima classe Union Find, struttura dati per memorizzare una collezione di insiemi disgiunti, ad esempio la partizione di un insieme in più sottoinsiemi (disgiunti per definizione di partizione). Questa struttura ha due operazioni: union (fonde 2 sottoinsiemi) e find (verifica se due elementi sono nello stesso sottoinsieme). È implementata con un vettore `id` che contiene per ogni elemento l'indice dell'elemento che lo rappresenta, e un vettore `sz` che contiene per ogni elemento la dimensione del sottoinsieme di cui fa parte.

```c
// UF.h
void  UFinit(int N);
int   UFfind(int p, int q);
void  UFunion(int p, int q);
```

```c
// UF.c
#include <stdlib.h>
#include "UF.h"
static int *id, *sz;
void UFinit(int N) {
    int i;
    id = malloc(N*sizeof(int));
    sz = malloc(N*sizeof(int));
    for(i=0; i<N; i++) {
        id[i] = i; sz[i] = 1;
    }
}

static int find(int x) {
    int i = x;
    while (i!= id[i]) i = id[i];
    return i;
}

int UFfind(int p, int q) { return(find(p) == find(q)); }

void UFunion(int p, int q) {
    int i = find(p), j = find(q);
    if (i == j) return;
    if (sz[i] < sz[j]) {
        id[i] = j; sz[j] += sz[i];
    }
    else {
        id[j] = i; sz[i] += sz[j];
    }
}
```

### Implementazione
```c

int mstE(Graph G, Edge *mst, Edge *a) {
    int i, k;
    GRAPHedges(G, a);
    sort(a, 0, G->E-1);
    UFinit(G->V);
    for (i=0, k=0; i < G->E && k < G->V-1; i++ )
        if (!UFfind(a[i].v, a[i].w)) {
            UFunion(a[i].v, a[i].w);
            mst[k++]=a[i];
        }
    return k;
}

// wrapper
void GRAPHmstK(Graph G) {
    int i, k, weight = 0;
    Edge *mst = malloc((G->V-1) * sizeof(Edge)); Edge *a = malloc(G->E * sizeof(Edge));
    
    k = mstE(G, mst, a);

    printf("\nEdges in the MST: \n");
    for (i=0; i < k; i++) {
        printf("(%s - %s) \n", STsearchByIndex(G->tab, mst[i].v), STsearchByIndex(G->tab, mst[i].w));
        weight += mst[i].wt;
    }
    printf("minimum weight: %d\n", weight);
}
```

### Complessità
L'algoritmo di Kruskal ha complessità O(E log E). Ricordando che |E|=O(V^2), l'algoritmo ha complessità O(E log V).

## Algoritmo di Prim
ne vedremo due versioni
### Pseudocodice
si inizia da un albero con un solo vertice
si itera su tutti i vertici
si aggiunge ad ogni passo un arco leggero che connette l'albero corrente ad un vertice non ancora nell'albero
quando tutti i vertici sono nell'albero, l'algoritmo termina.

vedi esempio pag 36-46

### Strutture dati
- Grafo rappresentato come matrice delle adiacenze dove l’assenza di un arco si indica con maxWT (anziché 0)
- vettore `st` di G->V elementi per registrare per ogni vertice che appartiene alla soluzione (a S) il padre
- vettore `fringe` di G->V elementi per registrare per ogni vertice che non appartiene alla soluzione (a V\S) qual'è il vertice di S più vicino
- vettore `wt` di G->V+1 elementi per registrare per ogni vertice:
  - se fa parte della soluzione, il peso dell'arco che lo collega al padre
  - se non fa parte della soluzione, il peso dell'arco leggero che lo collega al padre
- variabile `min` per il vertice in V\S più vicino a S

```c
void mstV(Graph G, int *st, int *wt) {
    int v, w, min, *fr = malloc(G->V*sizeof(int));
    for (v=0; v < G->V; v++) {
        st[v] = -1; fr[v] = v;  wt[v] = maxWT;
    }
    st[0] = 0;   wt[0] = 0;   wt[G->V] = maxWT;
    for (min = 0; min != G->V; ) {
        v = min;  st[min] = fr[min];
        for (w = 0, min = G->V; w < G->V; w++)
        if (st[w] == -1) {
            if (G->madj[v][w] < wt[w]) {
                wt[w] = G->madj[v][w]; fr[w] = v;
            }
            if (wt[w] < wt[min]) min = w;
        }
    }
}
// wrapper
void GRAPHmstP(Graph G) {
    int v, *st, *wt, weight = 0;
    st = malloc(G->V*sizeof(int));
    wt = malloc((G->V+1)*sizeof(int));
    mstV(G, st, wt);
    printf("\nEdges in the MST: \n");
    for (v=0; v < G->V; v++) {
        if (st[v] != v) {
            printf("(%s-%s)\n",STsearchByIndex(G->tab,st[v]),STsearchByIndex(G->tab,v));
            weight += wt[v];
        }
    }
    printf("\nminimum weight: %d\n", weight);
}
```

vedi esempio pag 53-61

### Complessità
L'algoritmo di Prim ha complessità O(V^2).
Possibili miglioramenti per grafi sparsi: usare una coda a priorità per gestire la fringe. La complessità diventa O(E log V).