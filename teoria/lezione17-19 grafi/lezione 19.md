[02/02/2024] In questa lezione si parla di applicazioni degli algoritmi di visita dei grafi in profondità e in ampiezza. Si parla di componenti connesse e fortemente connesse e come trovarle. Scopriamo cosa sono i punti di articolazione e gli archi ponte e come trovarli. Infine scopriamo cosa sono i DAG e come trovarne l'ordinamento topologico.

- [Rivelare grafici aciclici](#rivelare-grafici-aciclici)
- [Componenti connesse](#componenti-connesse)
  - [Ricerca componenti connesse](#ricerca-componenti-connesse)
    - [Implementazione](#implementazione)
  - [Ricerca componenti fortemente connesse](#ricerca-componenti-fortemente-connesse)
    - [Implementazione algoritmo di Kosaraju](#implementazione-algoritmo-di-kosaraju)
    - [Kernel DAG](#kernel-dag)
- [Connettività](#connettività)
  - [Punti di articolazione](#punti-di-articolazione)
  - [Archi ponte](#archi-ponte)
- [DAG](#dag)
  - [Ordinamenti](#ordinamenti)
  - [Implementazione](#implementazione-1)
    - [Ordinamento topologico inverso](#ordinamento-topologico-inverso)
    - [Ordinamento topologico diretto](#ordinamento-topologico-diretto)


# Rivelare grafici aciclici
> DEF (grafo aciclico): Un grafo è aciclico se non contiene cicli. 

Un grafo è aciclico (bi implica) in una visita in profondità non si incontrano archi etichettati B.

(NOTA: trovare i cicli è molto difficile, non tratteremo questo problema)

# Componenti connesse
Ricordiamo in un grafo non orientato cosa vuol dire essere connesso e fortemente connesso:
> DEF (grafo connesso): Un grafo è connesso se esiste un cammino tra ogni coppia di vertici.

> DEF (grafo fortemente connesso): Un grafo orientato è fortemente connesso se esiste un cammino orientato tra ogni coppia di vertici.


## Ricerca componenti connesse
Come trovare il più grande sottografo connesso? Si fa una visita in profondità. Ogni albero che si ottiene è una componente connessa. Quindi basta trovare l'albero più grande.

### Implementazione
Useremo un vettore di interi `cc` per rappresentare a quale componente connessa appartene ogni nodo del grafo. Useremo una funzione ricorsiva `dfsRcc` per fare una DFS, ma non una DFS completa (che crea gli alberi ecc...), una DFS che mette soltanto `id` nel vettore `cc` in corrispondenza dei nodi visitati.

```c
// DFS ricorsiva per trovare le componenti connesse
void dfsRcc(Graph G, int v, int id, int *cc) {
    link t;
    cc[v] = id;
    for (t = G->ladj[v]; t != G->z; t = t->next)
        if (cc[t->v] == -1) {dfsRcc(G, t->v, id, cc);}
}

// wrapper
int GRAPHcc(Graph G) {
    // inizializzazione variabili
    int v, *cc;
    int id = 0; // identificativo della componente connessa
    
    cc = malloc(G->V * sizeof(int));
    for (v = 0; v < G->V; v++) cc[v] = -1;
    
    // chiama la DFS su ogni nodo (perchè se il grafico non è connesso, bisogna fare così)
    for (v = 0; v < G->V; v++)
        if (cc[v] == -1){ dfsRcc(G, v, id++, cc); }

    // stampa i risultati
    printf("Connected component(s) \n");
    for (v = 0; v < G->V; v++)
        printf("node %s in cc %d\n",STsearchByIndex(G->tab,v),cc[v]);
  return id;
}
```

## Ricerca componenti fortemente connesse
Come trovare il più grande sottografo fortemente connesso? Ci sono due algoritmi: Kosaraju e Tarjan. Analizzeremo solo il primo, ecco gli step:
- trasporre il grafo (cioè invertire la direzione degli archi)
- eseguire DFS sul grafo trasposto, calcolando i tempi di scoperta (che non ci serviranno) e di fine elaborazione (che ci serviranno)
- eseguire DFS sul grafo originale per tempi di fine elaborazione decrescenti (cioè partendo dal nodo con tempo di fine elaborazione maggiore e proseguendo in ordine decrescente).
- gli alberi dell’ultima DFS sono le componenti fortemente connesse.

### Implementazione algoritmo di Kosaraju
- `sccR` è un vettore di interi usato per marcare i nodi visitati dalla DFS del grafo trasposto.
- `sccG` è un vettore di interi usato per indicare ogni nodo a quale componente fortemente connessa appartiene.
- `time0` è un contatore che avanza ogniqualvolta un nodo viene terminato.
- `time1` è un contatore di componenti fortemente connesse.
- `postR` è un vettore che viene riempito con i nodi completati dalla DFS del grafo trasposto. Quindi percorrendolo all'indietro si ottiene l'ordine di tempo di elaborazione decrescente dei nodi.
- `postG` è un vettore che non serve a nulla.
```c
// funzione per trasporre un grafo
Graphreverse(Graph G) {
    int v;
    link t;
    Graph R = GRAPHinit(G->V);
    for (v=0; v < G->V; v++)
        for (t= G->ladj[v]; t != G->z; t = t->next)
            GRAPHinsertE(R, t->v, v);
    return R;
}
```
```c
void SCCdfsR(Graph G,int w,int *scc,int *time0,int time1,int *post) {
    link t;
    scc[w] = time1; // assegna il vertice corrente alla componente fortemente connessa
    // scandisce la lista di adiacenze del vertice w
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (scc[t->v] == -1){ SCCdfsR(G, t->v, scc, time0, time1, post); }
    // aggiunge il nodo al vettore post
    post[(*time0)++]= w;
}

// wrapper
int GRAPHscc(Graph G) {
    // inizializzazione variabili
    int v, time0 = 0, time1 = 0, *sccG, *sccR, *postG, *postR;
    sccG = malloc(G->V * sizeof(int));
    sccR = malloc(G->V * sizeof(int));
    postG = malloc(G->V * sizeof(int));
    postR = malloc(G->V * sizeof(int));
    for (v=0; v < G->V; v++) { sccG[v]=-1; sccR[v]=-1; postG[v]=-1; postR[v]=-1;}
    // inversione del grafo
    Graph R = GRAPHreverse(G);
    // visita in profondità del grafo trasposto
    for (v=0; v < G->V; v++)
        if (sccR[v] == -1) SCCdfsR(R, v, sccR, &time0, time1, postR);
    // visita in profondità del grafo originale, secondo l'ordine di tempo di elaborazione decrescente
    time0 = 0; time1 = 0;
    for (v = G->V-1; v >= 0; v--)
        if (sccG[postR[v]]==-1){
            SCCdfsR(G,postR[v], sccG, &time0, time1, postG);
            time1++;
        }
    // stampa i risultati
    printf("strongly connected components \n");
    for (v = 0; v < G->V; v++)
        printf("node %s in scc %d\n",STsearchByIndex(G->tab,v),sccG[v]);
    return time1;
}
```


### Kernel DAG
Una volta trovate, si potrebbe pensare che ogni vertice nella componente fortemente connessa sia equivalente a ogni altro. Quindi si potrebbe sostituire ogni vertice della componente fortemente connessa con un solo vertice, e si otterrebbe un grafo più piccolo. Questo grafo è un DAG, se non lo fosse, allora avrebbe un cilco, ma gli elementi dl ciclo dovrebbero essere contati nella componente fortemente connessa. Assurdo quindi è un DAG. Questo grafo è chiamato DAG nucleare o kernel del grafo originale.

# Connettività
Dato un grafo non orientato e connesso, determinare se perde la proprietà di connessione a seguito della rimozione di un arco o di un nodo. Questo problema ha molte applicazioni pratiche, come la verifica della connettività di una rete di computer, la verifica della connettività di una rete di trasporto, ecc...

> DEF(archi ponte (o bridge)): Un arco è un arco ponte se la rimozione di quell'arco rende il grafo non connesso.

> DEF(punto di articolazione): Un nodo è un punto di articolazione se la rimozione di quel nodo rende il grafo non connesso. (ovviamente rimozione del nodo implica la rimozione degli archi su di esso incidenti)

![](<punti di articolaz.png>)

## Punti di articolazione
Come trovare i punti di articolazione:
- Si fa una DFS e si analizza l'albero generato.
- La radice dell'albero è un punto di articolazione se e solo se ha almeno due figli.
- Un nodo intermedio dell'albero A è un punto di articolazione se e solo se almeno un suo figlo è tale che lui e i suoi antenati NON hanno archi Back che puntano a un antenato proprio di A.
- Le foglie dell'albero non sono punti di articolazione.

## Archi ponte
Come trovare gli archi ponte:
- Si fa una DFS e si analizza l'albero generato.
- Un arco di tipo Back NON può essere un arco ponte (perchè c'è un altro cammino che connette i suoi due nodi incidenti).
- Un arco di tipo Tree che collega due nodi A e B è un arco ponte se e solo se non esiste un arco Back che collega un discendente di  B ad un antenato proprio di A.

Algoritmo alternativo (banale) per trovare gli archi ponte:
- Si rimuove un arco alla volta e si verifica se il grafo diventa non connesso.

# DAG
> DEF(DAG): Un grafo orientato è un DAG (Directed Acyclic Graph) se non contiene cicli.

È molto importante nei problemi di scheduling, cioè ogni qualvolta c'è un elenco di compiti da svolgere e c'è una relazione di precedenza tra i compiti.

Nel DAG esistono due tipi di nodi:
> DEF(nodi sorgente (o source)): Un nodo è sorgente se non ha archi entranti.
> DEF(nodi pozzo (o sink)): Un nodo è pozzo se non ha archi uscenti.

Scheduling del vestirsi:
![](<esempio dag.png>)

## Ordinamenti
Nel dag esistono due tipi di ordinamenti:
- Ordinamento topologico: Un ordinamento topologico di un DAG è un ordinamento dei nodi (cioè tutti i nodi messi su una linea retta) in cui se esiste un arco da A a B, allora A compare prima di B.
- Ordinamento topologico inverso: Un ordinamento topologico inverso di un DAG è un ordinamento dei nodi in cui se esiste un arco da A a B, allora B compare prima di A (l'opposto dell'ordinamento topologico).

Potremmo chiederci, l'ordinamento topologico è unico? Non per forza. Abbiamo i seguenti due teoremi:

Se esiste un cammino hamiltoniano orientato, l'ordinamento topologico è unico.

Se non esiste un cammino hamiltoniano orientato, l'ordinamento topologico non è unico.

Nel caso non ti ricordi cosa è un cammino hamiltoniano, è un cammino che passa per tutti i nodi del grafo una e una sola volta (ma non si richiude su se stesso, quello è il ciclo di hamilton).

![](<camm top dag.png>)

Qundi ogni DAG ha almeno un ordinamento topologico. Se è unico, il nostro algoritmo ne troverà solo uno e pace.

## Implementazione
### Ordinamento topologico inverso
DAG come lista di adiacenze. Usiamo un vettore `pre` per memorizzare il tempo di scoperta di un nodo (-1 se non scoperto). Usiamo un vettore `ts` per memorizzare l'ordinamento topologico inverso. Ogni volta che un nodo viene completato, lo si aggiunge al vettore `ts`.

```c
// DFS modificata
void TSdfsR(Dag D, int v, int *ts, int *pre, int *time) {
    link t; pre[v] = 0;
    // scandisce la lista di adiacenze del vertice v
    for (t = D->ladj[v]; t != D->z; t = t->next)
        if (pre[t->v] == -1) TSdfsR(D, t->v, ts, pre, time);

    // una volta completato aggiunge il nodo al vettore ts
    ts[(*time)++] = v;
}

// wrapper
void DAGrts(Dag D) {
    // inizializzazione variabili
    int v, time = 0, *pre, *ts;
    for (v=0; v < D->V; v++) { pre[v] = -1; ts[v] = -1; }
    // chiama la DFS su ogni nodo
    for (v=0; v < D->V; v++)
        if (pre[v]== -1) TSdfsR(D, v, ts, pre, &time);
    // stampa i risultati
    printf("DAG nodes in reverse topological order \n");
    for (v=0; v < D->V; v++)
        printf("%s ", STsearchByIndex(D->tab, ts[v]));
    printf("\n");
}
```

### Ordinamento topologico diretto
La funzione wrapper è la stessa, ma la funzione `TSdfsR` cambia. Invece di scorrere la lista di adiacenze del vertice `v`, si usa la matrice di adiacenze. Si scorre la colonna `v` della matrice di adiacenze (cioè si scorrono tutti i nodi che hanno un arco entrante da `v`) e si chiama la funzione ricorsiva su di essi se non sono stati visitati. Boh
```c
void TSdfsR(Dag D, int v, int *ts, int *pre, int *time) { int w;
    pre[v] = 0;
    for(w =0;w<D->V;w++)
        if (D->madj[w][v]  != 0)
            if (pre[w] == -1)
                TSdfsR(D, w, ts, pre, time);
    ts[(*time)++] = v;
    }
```