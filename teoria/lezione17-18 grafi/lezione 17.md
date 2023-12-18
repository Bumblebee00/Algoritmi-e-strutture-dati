[18/12/23] In questa lezione abbiamo parlato di grafi, e di come rappresentarli in memoria. Abbiamo visto due rappresentazioni: con matrice di adiacenza e con liste di adiacenza. Abbiamo visto i vantaggi e gli svantaggi di entrambe, e abbiamo visto come implementare le funzioni base di un grafo (load, store, insert, remove, ...). Abbiamo visto anche come generare grafi a caso.

- [Grafo](#grafo)
  - [Problemi con grafi](#problemi-con-grafi)
    - [Problemi facili](#problemi-facili)
    - [Problemi trattabili](#problemi-trattabili)
    - [Problemi intrattabili:](#problemi-intrattabili)
      - [Ciclo di Hamilton](#ciclo-di-hamilton)
      - [Colorabilità](#colorabilità)
  - [ADT Grafo](#adt-grafo)
    - [Funzioni base](#funzioni-base)
    - [Rapprsentazione con matrice di adiacenza](#rapprsentazione-con-matrice-di-adiacenza)
      - [Codice](#codice)
      - [Vantaggi e svantaggi](#vantaggi-e-svantaggi)
    - [Rappresentazione con liste di adiacenza](#rappresentazione-con-liste-di-adiacenza)
      - [Codice](#codice-1)
      - [Vantaggi](#vantaggi)
      - [Svantaggi](#svantaggi)
  - [Generazinoe di grafi (a caso)](#generazinoe-di-grafi-a-caso)
  - [Cammino semplice](#cammino-semplice)
    - [Codice](#codice-2)
  - [Cammino di Hamilton](#cammino-di-hamilton)
    - [Codice](#codice-3)
  - [Cammino di Eulero](#cammino-di-eulero)

# Grafo
> DEF (grafo pesato): Un grafo pesato è un grafo in cui ogni arco ha un peso associato.

> DEF (grafo orientato): Un grafo orientato è un grafo in cui gli archi sono orientati.

## Problemi con grafi

### Problemi facili
> DEF (grafo connesso): Un grafo è connesso se esiste un cammino tra ogni coppia di vertici.
- determinare se un grafo è connesso 
- determinare la presenza di un ciclo
> DEF (grafo fortemente connesso): Un grafo è fortemente connesso se esiste un cammino orientato tra ogni coppia di vertici.
- individuare le componenti fortemente connesse
> DEF (albero ricoprente): Un albero ricoprente è un sottografo che contiene tutti i vertici del grafo e che è un albero, cioè non contiene cicli.
- individuare gli alberi minimi ricoprenti 
- calcolare i cammini minimi
> DEF (grafo bipartito): Un grafo è bipartito se i vertici possono essere divisi in due insiemi X e Y tali che ogni arco ha un estremo in X e uno in Y.
- determinare se un grafo è bipartito
- trovare un cammino di Eulero (definizione dopo)

### Problemi trattabili
> DEF (grafo planare): Un grafo è planare se può essere disegnato su un piano in modo che i suoi archi non si intersechino.
- planarità di un grafo
- matching

### Problemi intrattabili:
(cioè trattabili ma in tempo esponenziale)
- cammini a lunghezza massima
- colorabilità
- clique massimale
- ciclo di Hamilton
- problema del commesso viaggiatore (ciclo semplice che minimizza la somma dei pesi degli archi)

problemi a complessità non nota:
- isomorfismo di grafi

#### Ciclo di Hamilton
Dato un grafo non orientato G = (V, E), esiste un ciclo semplice che visita ogni vertice una e una sola volta?

![](<esempio ciclo di hamilton.png>)

#### Colorabilità
Dato un grafo non orientato G =(V,E), quale è il minimo numero di colori k necessario affinché nessun vertice abbia lo stesso colore di un vertice ad esso adiacente?

Si dimostra che per grafi planari k <= 4 (Teorema di Appel e Haken, 1976).

## ADT Grafo
In teroia basterebbe una sola struttura dati sia per pesati e non, sia per orientati e non. infatti non pesato si mette tutti peso = 1, non orientato si mette doppio arco ta due nodi.

> DEF (grafi statici): Un grafo statico è un grafo in cui il numero di vertici e di archi è fisso.

> DEF (grafi semi-statici): Non si aggiungono né si cancellano vertici, si possono aggiungere o cancellare archi

> DEF (grafi dinamici): Si possono aggiungere o cancellare vertici e archi.

In questo corso si considerano solo grafi semi-statici, in cui i vertici vengono cancellati "logicamente", aggiungendo un campo per marcare se è cancellato o meno.

Inoltre nei grafi ci saranno solo interi come indice, e il valore del vertice sarà memorizzato in una tabella di simboli (che può essere esterna o interna all'ADT grafo).

```c
// da chiave (nome) a intero (indice)
STsearch
// da chiave (indice) a stringa (nome)
STsearchByIndex
```

Useremo un approccio alla Sergewick: L'arco dovrebbe essere nascosto all'utente ma si definisce nel .h perchè siamo stupidi, e la tabella di simboli è un ADT di I classe

![](<adt grafo.png>)

### Funzioni base

```c
Graph GRAPHload(FILE *fin) {
    int V, i, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    Graph G;
    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);
    for (i=0; i<V; i++) {
        fscanf(fin, "%s", label1);
        STinsert(G->tab, label1, i);
    }
    // fintanto che la fscanf riesce a leggere 3 elementi
    while(fscanf(fin,"%s %s %d", label1, label2, &wt) == 3) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >=0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    return G;
}
```
```c
void GRAPHstore(Graph G, FILE *fout) {
    int i;
    Edge *a;
    a = malloc(G->E * sizeof(Edge));

    GRAPHedges(G, a); // dipende dalla rappresentazione

    fprintf(fout, "%d\n", G->V);
    for (i = 0; i < G->V; i++)
        fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));
    for (i = 0; i < G->E; i++)
        fprintf(fout, "%s  %s %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);
}
```

```c
// qua bisognia porre attenzione al fatto che alla funzione insertE si passa un edge, non due interi. si va sul sottile qua
void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}
void GRAPHremoveE(Graph G, int id1, int id2) {
    removeE(G, EDGEcreate(id1, id2, 0));
}
```

### Rapprsentazione con matrice di adiacenza
possiamo rappresentare un grafo in svariati modi, ognuno con i suoi pro e contro. Iniziamo a vedere la rappresentazione con matrice di adiacenza.

Dato G = (V, E), la matrice di adiacenza è una matrice VxV in cui l'elemento (i,j) è 1 se esiste un arco da i a j, 0 altrimenti.

Nota: per i grafi non orientati la matrice è simmetrica.
Nota: per i grafi pesati si memorizza il peso al posto di 1 (quindi il peso 0 non è permesso).
Nota: abbiamo assunto che tra ogni coppia di vertici ci sia al più un arco (uno o zero, ma non due o più). In questo caso abbiamo un...
> DEF (multigrafo): un grafo in cui tra due vertici possono esserci più archi.
L'esempio più famoso di multigrafo sono i ponti di Königsberg.

$$
A_{ij} = \begin{cases}
    w_{ij} & \text{se esiste un arco da i a j} \\
    0 & \text{altrimenti}
\end{cases}
$$

![](<esempio di matrice di adicenza.png>)

#### Codice
![](<graph dot c matrice di adiacenza.png>)

```c
Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;
    G->madj = MATRIXint(V, V, 0);
    G->tab = STinit(V);
    return G;
}

void GRAPHfree(Graph G) {
    int i;
    for (i=0; i<G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    STfree(G->tab);
    free(G);
}
```

BAROCCHISMO ALERT !!! abbiamo creato un arco (nella funzione) `GRAPHinsertE` solo per splittarlo di novo in due interi. si va proprio per il sottile qua...
![](<insert edge matrice di adiacenza.png>)
Anche nel remove c'è il barocchismo.
![](<remove edge matrice di adiacenza.png>)

#### Vantaggi e svantaggi
- Complessità in spazio: O(V^2). Per grafi densi è ottimo, per grafi sparsi è pessimo.
Nota: gli archi totali sono V*(V-1)/2 se non orientato, V*(V-1) se orientato.
- No costi in memora aggiuntivi per memorizzare i grafi pesati.
- Accesso efficiente (O(1)) alla topologia del grafo (cioè è facile capire se c'è un edge tra due vertici).

### Rappresentazione con liste di adiacenza
Dato G = (V, E), la lista di adiacenza è: un vettore A di V elementi ( o una lista se non conosco a priori V ), dove A[i] contiene il puntatore alla lista dei vertici adiacenti a i.

![](<esempio di lista di adiacenza.png>)

Nota: se il grafo è pesato, nella lista di adiacenza memorizziamo il peso dell'arco.
![](<graph dot c lista di adiacenza.png>)

#### Codice
```c
Graph GRAPHinit(int V) {
    int v;
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;
    G->z = NEW(-1, -1,  NULL);
    G->ladj = malloc(G->V*sizeof(link));
    for (v = 0; v < G->V; v++)
        G->ladj[v] = G->z;
    G->tab = STinit(V);
    return G;
}

void GRAPHfree(Graph G) {
    int v;
    link t, next;
    for (v=0; v < G->V; v++)
        for (t=G->ladj[v]; t != G->z; t = next) {
        next = t->next;
        free(t);
        }
    STfree(G->tab);
    free(G->ladj); free(G->z); free(G);
}
```

```c
void  GRAPHedges(Graph G, Edge *a) {
    int v, E = 0;
    link t;
    for (v=0; v < G->V; v++)
        for (t=G->ladj[v]; t != G->z; t = t->next)
            if (v < t->v) // questo if solo per grafi non orientati
                a[E++] = EDGEcreate(v, t->v, t->wt);
}
```
![](<insert e lista di adiacenza.png>)

```c
static void removeE(Graph G, Edge e) {
    int v=e.v,w=e.w; linkx,p;
    for (x = G->ladj[v], p = NULL; x != G->z; p = x, x = x->next) {
        if (x->v == w) {
            if (x == G->ladj[v]) G->ladj[v] = x->next;
            else p->next = x->next;
            break;
        }
    }
    // solo se non orientato --- inizio
    for (x = G->ladj[w], p = NULL; x != G->z; p = x, x = x->next) {
        if (x->v == v) {
            if (x == G->ladj[w]) G->ladj[w] = x->next;
            else p->next = x->next;
            break;
        }
    }
    // solo se non orientato --- fine
    G->E--;   free(x);
}
```

#### Vantaggi
Elementi complessivi nelle liste:
- grafo non orientato: 2E
- grafo orientato: E

Complessità spaziale: S(n) = O(max(|V|, |E|)) = O(|V+E|). è vantaggioso per grafi sparsi

#### Svantaggi
per verificare l’adiacenza di 2 vertici v e w devo scansionare la lista di adiacenza di v. molto lungo.
Si usa memoria addizionale per i pesi dei grafi pesati.

## Generazinoe di grafi (a caso)
In generale i grafi sono modelli di situazioni reali e vengono formiti come dati di ingresso. In caso contrario, si possono generare dei grafi senza alcuna relazione ad un problema specifico, ma solo per testare gli algoritmi. Come possiamo generare un grafo a caso?

Tecnica 1: archi casuali
- Vertici come interi tra 0 e |V|-1
- generazione di un grafo casuale a partire da E coppie casuali di archi (interi tra 0 e |V|-1)
- possibili archi ripetuti (multigrafo) e cappi
- grafo con |V| vertici e |E| archi (inclusi cappi e archi ripetuti)

> DEF (grafo completo): Un grafo completo è un grafo in cui ogni coppia di vertici è collegata da un arco.

Tecnica 2: archi con probabilità p
- si considerano tutti i possibili archi V*(V-1)/2
- tra questi si selezionano quelli con probabilità p
- p è calcolato in modo che
    $E = p * (V*(V-1)/2)$
    quindi
    $p = 2 *E/(V*(V–1))$
- si ottiene un grafo con in media E archi
- non ci sono archi ripetuti.

```c
int randV(Graph G) {
    return G->V * (rand() / (RAND_MAX + 1.0));
}

Graph GRAPHrand1(Graph G, int V, int E) {
    while (G->E < E)
        GRAPHinsertE(G, randV(G), randV(G));
    return G;
}
Graph GRAPHrand2(Graph G, int V, int E) {
    int i, j; double p = 2.0 * E / (V * (V-1));
    for (i = 0; i < V; i++)
        for (j = i+1; j < V; j++)
            if (rand() < p * RAND_MAX)
                GRAPHinsertE(G, i, j);
    return G;
}
```

## Cammino semplice
Dato un grafo non orientato G =(V, E) e 2 suoi vertici v e w, esiste un cammino semplice che li connette? Non è richiesto trovarli tutti.

Se il grafo non orientato è connesso il cammino esiste per definizione, basta trovarne uno qualsiasi senza altri vincoli se non essere semplice. Non serve backtrack.

Se il grafo non orientato non è connesso il cammino esiste per definizione se i vertici sono nella stessa componente connessa, altrimenti non esiste. Non serve backtrack.

Algoritmo:
- qualunque vertice t adiacente al vertice corrente v, determinare ricorsivamente se esiste un cammino semplice da t a w

Uso un array visited[maxV] per marcare i nodi già visitati. cammino visualizzato in ordine inverso. complessità T(n) = O(|V+E|)

Guarda l'esempio pag 53-58

### Codice
???

## Cammino di Hamilton
Dato un grafo non orientato G =(V, E) e 2 suoi vertici v e w, se esiste un cammino semplice che li connette visitando ogni vertice una e una sola volta, questo si dice cammino di Hamilton. (se v = w si dice ciclo di Hamilton).

Algoritmo:
- qualunque vertice t adiacente al vertice corrente v, determinare ricorsivamente se esiste un cammino semplice da t a w
- ritorno con successo se e solo se la lunghezza del cammino è V-1
Si usa set della cella dell’array visited per marcare i nodi già visitati. Si fa il reset della cella dell’array visited quando ritorna con insuccesso (backtrack).

complessità esponenziale!

### Codice
???

## Cammino di Eulero
Dato un grafo non orientato G =(V, E) e 2 suoi vertici v e w, si dice cammino di Eulero un cammino (anche non semplice) che li connette attraversando ogni arco una e una sola volta. Se v coincide con w, si parla di ciclo di Eulero.

> DEF (grado di un vertice): Il grado di un vertice è il numero di archi incidenti su di esso.

Cose dimostrate da Eulero nel 1736:
- Un grafo non orientato ha un ciclo di Eulero se e solo se è connesso e tutti i suoi vertici sono di grado pari
- Un grafo non orientato ha un cammino di Eulero se e solo se è connesso e se esattamente due vertici hanno grado dispari.