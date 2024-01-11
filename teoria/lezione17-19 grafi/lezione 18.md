[18/12/2023]

- [Gli algoritmi di visita dei grafi](#gli-algoritmi-di-visita-dei-grafi)
  - [Visita in profondità (versione base)](#visita-in-profondità-versione-base)
    - [Strutture dati necesarie](#strutture-dati-necesarie)
  - [Visita in profondità (versione estesa)](#visita-in-profondità-versione-estesa)
    - [Strutture dati necesarie](#strutture-dati-necesarie-1)
  - [Visita in profondità (versione completa)](#visita-in-profondità-versione-completa)
    - [Codice](#codice)
    - [Complessità](#complessità)
  - [Visita in ampiezza](#visita-in-ampiezza)
    - [Strutture dati necesarie](#strutture-dati-necesarie-2)
    - [Codice](#codice-1)
- [Numeri di Erdos](#numeri-di-erdos)

# Gli algoritmi di visita dei grafi
???

## Visita in profondità (versione base)
Dato un grafo (connesso o non connesso), a partire da un vertice s, visita tutti i vertici del grafo (raggiungibili da s e non). (nota: alcuni libri invece chiamano la visita in profondità quella che da un vertice visita solo i vertici raggiungibili da esso)

Il principio base della visita in profondità è espandere l’ultimo vertice scoperto che ha ancora vertici non ancora scoperti adiacenti. Cosa sono i vertici scoperti? Sono i vertici che sono stati visitati e che sono stati aggiunti alla coda. Per ogni vertice, la visita in profondità visita tutti i vertici adiacenti a esso prima di passare al prossimo vertice.

vedi l'esempio a pag 5-7

### Strutture dati necesarie
- grafo non pesato come lista delle adiacenze
- vettore `pre` dove per ciascun vertice si registra l'ordine di scoperta (numerazione in preordine dei vertici)

```c
// funzione ricorsiva che trova i vertici raggiungibili da s
static void simpleDfsR(Graph G, Edge e, int *cnt, int *pre) {
    link t; int w = e.w;
    pre[w] = (*cnt)++;
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (pre[t->v] == -1)
            simpleDfsR(G, EDGEcreate(w, t->v), cnt, pre);
}
```

```c
void GRAPHsimpleDfs(Graph G, int id) {
    int v, cnt=0, *pre;
    pre = malloc(G->V * sizeof(int));
    if ((pre == NULL)) return;
    for (v=0;v<G->V;v++) pre[v]=-1;
    
    simpleDfsR(G, EDGEcreate(id,id), &cnt, pre);

    for (v=0; v < G->V; v++)
        if (pre[v]== -1)
            simpleDfsR(G, EDGEcreate(v,v), &cnt, pre);
  
    printf("discovery time labels \n");
    for (v=0; v < G->V; v++)
        printf("vertex %s : %d \n", STsearchByIndex(G->tab, v), pre[v]);
}
```

## Visita in profondità (versione estesa)
come l'altra ma con aggiunta di:
- nodi etichettati con etichetta tempo di scoperta / tempo di completamento (il tempo di completamento è il tempo in cui si è completata la visita di un nodo) (sempre con tempo non è proprio il tempo, ma diciamo l'indice di come è stato visitato in ordine. `cnt` per capirci)
- foresta di alberi (cioè più alberi) della visita in profondità, memorizzata in un vettore. Cioè degli alberi che rappresentano in che modo ho visitato i nodi.

vedi esempio a pag 13-25

### Strutture dati necesarie
- grafo non pesato come lista delle adiacenze
- vettori dove per ciascun vertice:
    - si registra il tempo di scoperta (numerazione in preordine dei vertici) pre[i]
    - si registra il tempo di completamento (numerazione in postordine dei vertici) post[i]
    - si registra il padre per la costruzione della foresta degli alberi della visita in profondità: st[i]
- contatore time per tempi di scoperta/completamento

```c
static void ExtendedDfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st) {
    link t;
    int w = e.w;
    st[e.w] = e.v;
    pre[w] = (*time)++;
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (pre[t->v] == -1)
            ExtendedDfsR(G, EDGEcreate(w, t->v), time, pre, post, st);
    post[w] = (*time)++;
}
```
```c
// wrapper
void GRAPHextendedDfs(Graph G, int id) {
    int v, time=0, *pre, *post, *st;
    pre/post/st = malloc(G->V * sizeof(int));
    for (v=0;v<G->V;v++) {
        pre[v]=-1; post[v]=-1; st[v]=-1;}
    
    extendedDfsR(G, EDGEcreate(id,id), &time, pre, post, st);

    for (v=0; v < G->V; v++)
        if (pre[v]==-1)
            extendedDfsR(G,EDGEcreate(v,v),&time,pre,post,st);
    
    printf("discovery/endprocessing time labels \n");
    for (v=0; v < G->V; v++)
        printf("%s:%d/%d\n",STsearchByIndex(G->tab,v),pre[v],post[v]);
    printf("resulting DFS tree \n");
    for (v=0; v < G->V; v++)
        printf("%s’s parent: %s \n",STsearchByIndex (G->tab, v),
                STsearchByIndex (G->tab, st[v]));
}
```

## Visita in profondità (versione completa)
In più si etichettano anche gli archi. In un grafo **non orientato**: li marchiamo con **T (tree)** se fanno parte dell'albero della visita in profondità, **B (back)** se non fanno parte dell'albero della visita in profondità.

Perchè si chiamano Back? bè perchè se non sono nell'albero, vuol dire che collegano un nodo w a un nodo v già scoperto prima (un antenato nell'albero di visita in profondità). Alla fine della ricorsione su v quindi l'etichetta di terminazione di v sarà maggiore della terminazione di w. L'etichetta di scoperta di v sarà minore della terminazione di w (sempre, anche prima di terminare il nodo v).

E se il grafo è orientato? ci sono due nove classificazioni: **F (forward)** e **C (cross)**. Potrebbe succedere che l'arco considerato prima, che collega w e un suo antenato v, punti dall'antenato v a w. In questo caso si chiama nodo forward. Se un nodo non è nessuna delle 4 precedenti, si chiama nodo cross.

vedi gli esempi a pag 34-48

### Codice
```c
void dfsR(Graph G, Edge e, int *time,
          int *pre, int *post, int *st){
link t;
int v, w = e.w;
Edge x;
if (e.v != e.w)
escludi arco fittizio
printf("(%s, %s):  T \n",STsearchByIndex(G->tab, e.v),
                     STsearchByIndex(G->tab, e.w));
st[e.w] = e.v;
pre[w] = (*time)++;
for (t = G->ladj[w]; t != G->z; t = t->next)
terminazione implicita della ricorsione
if (pre[t->v] == -1)
  dfsR(G, EDGEcreate(w, t->v), time, pre, post, st);
else {
  v = t->v;
  x = EDGEcreate(w, v);
  // grafi non orientati --- inizio
if (pre[w] < pre[v])
   printf("(%s, %s): B\n", STsearchByIndex(G->tab, x.v),
            STsearchByIndex(G->tab,x.w)) ;
            // grafi non orientati --- fine
            // grafi orientati --- inizio
 if (post[v] == -1)
   printf("(%s, %s): B\n", STsearchByIndex(G->tab, x.v),
           STsearchByIndex(G->tab, x.w));
 else
   if (pre[v] > pre[w])
     printf("(%s,%s):F\n",STsearchByIndex(G->tab, x.v),
             STsearchByIndex(G->tab, x.w));
   else
     printf("(%s,%s):C\n",STsearchByIndex(G->tab, x.v),
             STsearchByIndex(G->tab, x.w));
}
                // grafi orientati --- fine
  post[w] = (*time)++;
}
```

### Complessità
???
Inizializzazione: O(V)
Ricorsione: O(E)
Totale: O(V+E)
Con la matrice di adiacenza invece: O(V^2)

## Visita in ampiezza
A partire da un vertice s questo tipo di visita determina tutti i vertici raggiungibili da s, quindi non visita necessariamente tutti i vertici a differenza della DFS. calcola la distanza minima da s di tutti i vertici da esso raggiungibili
??? espande la frontiera

è un modo per fare le cose in serie ma come se fossero in parallelo.

vedi gli esempi a pagina 57-68

risolv anche il problema della distanza minima tra un nodo e una radice
### Strutture dati necesarie
### Codice

# Numeri di Erdos
Paul Erdos è stato un matematico ungherese che ha lavorato in molti campi della matematica, tra cui la teoria dei grafi. Ha scritto più di 1500 articoli, collaborando con più di 500 coautori. Per questo motivo, si è pensato di assegnare un numero di Erdos a tutti i matematici che hanno scritto un articolo con lui, e di assegnare un numero di Erdos a tutti gli altri matematici che hanno scritto un articolo con uno di questi matematici, e così via. Il numero di Erdos di Erdos è 0, il numero di Erdos di un matematico che ha scritto un articolo con Erdos è 1, il numero di Erdos di un matematico che ha scritto un articolo con un matematico che ha scritto un articolo con Erdos è 2, e così via. Il numero di Erdos di un matematico che non ha scritto un articolo con nessuno di questi matematici è infinito.