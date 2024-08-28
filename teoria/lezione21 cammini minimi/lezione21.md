[12/02/23]

- [Cammini minimi](#cammini-minimi)
- [Algoritmo di Dijkstra](#algoritmo-di-dijkstra)
  - [Pseudocodice](#pseudocodice)
  - [Implementazione](#implementazione)
  - [Complessità](#complessità)
- [Cammini minimi su DAG pesati](#cammini-minimi-su-dag-pesati)
  - [Seam carving](#seam-carving)
- [Camminimi massimi su DAG pesati](#camminimi-massimi-su-dag-pesati)
- [Algoritmo di Bellman-Ford](#algoritmo-di-bellman-ford)
  - [Pseudocodice](#pseudocodice-1)
  - [Implementazione](#implementazione-1)
  - [Complessità](#complessità-1)
  - [Arbitrage](#arbitrage)


# Cammini minimi
Nel contensto di grafi orientati e pesati, un cammino è un insieme di vertici connessi da archi. Il peso di un cammino è la sommma dei pesi degli archi che lo compongono. Un cammino minimo (s,v), è un cammino tra due vertici s e v con peso minore o uguale a tutti gli altri cammini tra s e v. Se s e v non sono connessi, il cammino minimo tra di loro ha peso infinito.

Elenco di problemi:
- Trovare tutti i cammini minimi da un vertice s a tutti gli altri vertici
  - Algoritmo di Dijkstra
  - Algoritmo di Bellman-Ford
- Trovare tutti i cammini minimi da qualsiasi vertice a un vertice v
- Trovare il cammino minimo tra due vertici s e v
- Trovare il cammino minimo tra tutte le coppie di vertici
  - Algoritmo di Floyd-Warshall (non lo tratteremo)

Nota: potrebbero esistere archi con peso negativo. In questo caso, se non esitono cicli a peso negativo:
- algoritmo di Dijkstra non garantisce di trovare la soluzione ottima
- algoritmo di Bellman-Ford garantisce di trovare la soluzione ottima
se invece esistono cicli a peso negativo:
- algoritmo di Dijkstra non è applicabile
- algoritmo di Bellman-Ford rileva la presenza di cicli a peso negativo e non è applicabile

Nota: i cammini minimi non contengono cicli. Sono cammini semplici. Qundi il massimo numero di archi in un cammino minimo è V-1, dove V è il numero di vertici del grafo.

Ovviamente anche in questo problema possiamo iterare su tutti i possibili cammini e trovare quello con peso minore. Ma questo è un approccio esponenziale. Quindi cerchiamo un approccio più efficiente.

La programmazione dinamica è applicabile? (ricorda: è applicabile se il problema ha una sottostruttura ottima). cioè se ho un cammino minimo tra s e v, e lo decompongo in un sottocammino, quest'ultimo è minimo? Si.

# Algoritmo di Dijkstra
Ipotizza che non esistono archi con peso negativo. dato un grafo G=(V,E), un vertice s e un insieme di vertici V, l'algoritmo di Dijkstra divide V in:
- S: vertici per cui il cammino minimo da `s` è già stato trovato
- V\S: vertici per cui il cammino minimo da `s` non è stato ancora trovato. sono memorizzati in una coda di priorità Q, ordinata in base al peso del cammino stimato da `s` a ciascun vertice.

## Pseudocodice
dist[v] = distanza minima da s a v (inizialmente infinito)
pred[v] = predecessore di v nel cammino minimo da s a v (inizialmente null) (da qua si ricostruiscono i cammini minimi)

```
dist[s] = 0
coda a priorità Q = V
while Q non è vuota
    estrai un vertice u da Q (il vertice con distanza minima)
    aggiungi u a S
    per ogni vertice w adiacente a u rilassare(u,w). cioè:
    se w appartiene a Q e dist[u] + peso(u,w) < dist[w]
        dist[w] = dist[u] + peso(u,w)
        pred[w] = u

ricostituisci i cammini minimi usando pred[]
```
![](<esempio rilassamento.png>)
esempio di rilassamento

## Implementazione
```c
void GRAPHspD(Graph G, int id) {
    // inizializzazione variabili
    int v;
    link t;
    PQ pq = PQinit(G->V);
    int *st, *d;
    st = malloc(G->V*sizeof(int));
    d = malloc(G->V*sizeof(int));
    for (v = 0; v < G->V; v++){
        st[v] = -1;
        d[v] = maxWT;
        PQinsert(pq, d, v);
    }

    d[id] = 0;
    st[id] = id;
    PQchange(pq, d, id);
    while (!PQempty(pq)) {
        if (d[v = PQextractMin(pq, d)] != maxWT)
            for (t=G->ladj[v]; t!=G->z ; t=t->next)
                if (d[v] + t->wt < d[t->v]) {
                d[t->v] = d[v] + t->wt;
                PQchange(pq, d, t->v);
                st[t->v] = v;
        }
    }

    // stampa risultati
    printf("\n Shortest path tree\n");
    for (v = 0; v < G->V; v++)
        printf("parent of %s is %s \n", STsearchByIndex(G->tab, v), STsearchByIndex (G->tab, st[v]));
    printf("\n Min.dist. from %s\n", STsearchByIndex(G->tab, s));
    for (v = 0; v < G->V; v++)
        printf("%s: %d\n", STsearchByIndex(G->tab, v), d[v]);
    Pqfree(pq);
}
```

## Complessità
estrarre u da Q: O(logV)
insierire u in S: O(1)
rilassare(u,v): O(E)

Quindi la complessità totale è O((V + E) log V)

# Cammini minimi su DAG pesati
Basta ordinare topologicamente il DAG, poi applicare la relaxation in quell'ordine

## Seam carving
Da un immagine si costruisce un DAG, in cui i vertici sono i pixel, e il peso degli archi è la differenza di luminosità tra i due pixel. Trovando il cammino minimo tra due vertici, e poi rimuovendo i pixel del cammino, si ottiene un'immagine ridimensionata, senza distorsioni.

# Camminimi massimi su DAG pesati
Basta ordinare topologicamente il DAG, poi applicare la relaxation in quell'ordine. La relaxation però è diversa: si parte da -inf e se v appartiene a Q il nuovo cammino ha peso maggiore, allora aggiorno dist[v] e pred[v]

# Algoritmo di Bellman-Ford
L'algoritmo di Dijkstra non è applicabile se esistono archi con peso negativo. L'algoritmo di Bellman-Ford è applicabile in questo caso. L'algoritmo di Bellman-Ford è anche applicabile se esistono cicli a peso negativo, e in questo caso rileva la presenza di cicli a peso negativo. L'algoritmo di Bellman-Ford è meno efficiente di Dijkstra, ma è più generale.

dato un grafo G=(V,E), e un vertice s, l'algoritmo di Bellman-Ford trova la distanza minima da s a tutti gli altri vertici.
## Pseudocodice
dist[v] = distanza minima da s a v (inizialmente infinito)
pred[v] = predecessore di v nel cammino minimo da s a v (inizialmente null)

dist[s] = 0
for i = 0 to V-1
    for ogni arco (u,v) in E
        rilassare(u,v). cioè:
            se dist[u] + peso(u,v) < dist[v]
                dist[v] = dist[u] + peso(u,v)
                pred[v] = u

## Implementazione
```c
void GRAPHspBF(Graph G, int id){
    // inizializzazione variabili
    int v, i, negcycfound;
    link t;
    int *st, *d; // d[v] = distanza minima da s a v; st[v] = predecessore di v nel cammino minimo da s a v
    st = malloc(G->V*sizeof(int));
    d = malloc(G->V*sizeof(int));
    for (v = 0; v < G->V; v++) {
        st[v]= -1;
        d[v] = maxWT;
    }

    d[id] = 0;
    st[id] = id;
    // per ogni vertice i
    for (i=0; i<G->V-1; i++)
        // per altro vertice v
        for (v=0; v<G->V; v++)
            // se esiste un arco da i a v
            if (d[v] < maxWT)
                // rilassare tutti gli archi uscenti da v
                for (t=G->ladj[v]; t!=G->z ; t=t->next)
                    if (d[t->v] > d[v] + t->wt) {
                        d[t->v] = d[v] + t->wt;
                        st[t->v] = v;
                    }
    
    // rilevamento cicli a peso negativo
    negcycfound = 0;
    for (v=0; v<G->V; v++)
    if (d[v] < maxWT)
        for (t=G->ladj[v]; t!=G->z ; t=t->next)
            if (d[t->v] > d[v] + t->wt)
                negcycfound = 1;
    
    // stampa risultati
    if (negcycfound == 0) {
        printf("\n Shortest path tree\n");
        for (v = 0; v < G->V; v++)
            printf("Parent of %s is %s \n", STsearchByIndex(G->tab, v), STsearchByIndex (G->tab, st[v]));
            printf("\n Min.dist. from %s\n", STsearchByIndex (G->tab, s));
        for (v = 0; v < G->V; v++)
           printf("%s: %d\n", STsearchByIndex (G->tab, v), d[v]);
    }
    else
        printf("\n Negative cycle found!\n");
}
```

## Complessità
O(V*E)

## Arbitrage
L'arbitrage è la pratica di sfruttare le differenze di prezzo di un bene in mercati diversi. L'arbitrage è possibile se esiste un ciclo a peso negativo. L'algoritmo di Bellman-Ford può essere usato per rilevare la presenza di cicli a peso negativo.