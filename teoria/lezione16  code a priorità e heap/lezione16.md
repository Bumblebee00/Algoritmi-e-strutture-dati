[11/12/23]

- [ADT Heap](#adt-heap)
  - [Implementazione funzioni base](#implementazione-funzioni-base)
  - [HEAPify](#heapify)
    - [Complessità](#complessità)
  - [HEAPbuild](#heapbuild)
    - [Complessità](#complessità-1)
  - [HeapSort](#heapsort)
- [Code a priorità](#code-a-priorità)
  - [Implementazione con HEAP](#implementazione-con-heap)
    - [PQinsert](#pqinsert)
  - [PQextractMax](#pqextractmax)
  - [PQchange](#pqchange)
- [Coda prioritaria di indici](#coda-prioritaria-di-indici)


# ADT Heap
L'HEAP è un albero bianrio che rispetta due proprietà:
- proprietà strutturale: l'albero è completo a sinistra (cioè tutti i livelli sono pieni tranne eventualmente l'ultimo riempito da sinistra a destra)
- proprietà funzionale: per ogni terna di nodi, la chiave contenuta nei sottoalberi è <= della chiave della radice (qunidi la chiave massima è sempre la radice)

Esempio di item contenente la chiave come intero, e un vaolre stringa:
![](<esempio di heap.png>)

## Implementazione funzioni base
Lo implementeremo con un vettore di quasi ADT Item contententi una chiave

```c
// HEAP.h
typedef struct heap *Heap;

Heap HEAPinit(int maxN);
Void HEAPfree(Heap h);
void HEAPfill(Heap h, Item val);
void HEAPsort(Heap h);
void HEAPdisplay(Heap h);
```

```c
// HEAP.c
#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "Heap.h"

struct heap { Item *A; int heapsize; };

int LEFT(int i) { return (i*2 + 1); }
int RIGHT(int i) { return (i*2 + 2); }
int PARENT(int i) { return ((i-1)/2); }

Heap HEAPinit(int maxN) {
    Heap h;
    h = malloc(sizeof(*h));
    h->A = malloc(maxN*sizeof(Item));
    h->heapsize = 0;
    return h;
}

void HEAPfree(Heap h) {
  free(h->A);
  free(h);
}

void HEAPfill(Heap h, Item item){
    int i;
    i  = h->heapsize++;
    h->A[i] = item;
    return;
}

void HEAPdisplay(Heap h){
    int i;
    for (i = 0; i < h->heapsize; i++)
        ITEMstore(h->A[i]);
}
```

## HEAPify
Funzione per modificare uno heap in cui la proprietà funzionale non è rispettata al nodo i. Prende in input un indice i e fa rispettare rispetta la proprietà funzionale. Pseudocodice:
- assegna ad A[i] il max tra A[i], A[LEFT(i)] e A[RIGHT(i)]
- se c’è stato scambio tra A[i] e A[LEFT(i)], applica ricorsivamente HEAPify su sottoalbero con radice LEFT(i)
(analogamente per scambio tra A[i] e A[RIGHT(i)])

```c
void HEAPify(Heap h, int i) {
  int l, r, largest;
  l = LEFT(i);
  r = RIGHT(i);
  if ((l<h->heapsize) && KEYcmp(KEYget(h->A[l]),KEYget(h->A[i]))==1)
    largest = l;
  else
    largest = i;
  if ((r<h->heapsize) && KEYcmp(KEYget(h->A[r]), KEYget(h->A[largest]))==1)
    largest = r;

  if (largest != i) {
    Swap(h, i,largest);
    HEAPify(h, largest);
  }
}
```

### Complessità
La complessità di HEAPify è O(logn) perchè il tempo di esecuzione è proporzionale all'altezza dell'albero.

## HEAPbuild
Trasforma un albero binario memorizzato in vettore in uno heap. Le foglie sono già heap, quindi partiamo dal penultimo livello e risaliamo fino alla radice chiamando heapify su ogni nodo. Iterare da n/2-1 a 0 ci garantisce di iniziare dall'ultimo nodo che ha un figlio, e di risalire fino alla radice. è facile capire perchè: ipotizziamo prima che l'albero sia con l'ultimo livello tutto riempito. L'ultimo livello nel vettore corrisponde agli indici da n/2 fino alla fine, quindi tutti gli altri nodi (sui quali noi chiamiamo HEAPify) sono prima. se poi togliamo i due figli dell'ultimo nodo del penultimo livello (che chiamiamo x), n/2 diminuisce di 1 rispetto a prima, e ciò corrispone al fatto che HEAPify non sarà chiamata sul nodo x ma su quello prima.

```c
void HEAPbuild (Heap h) {
    int i;
    for (i=(h->heapsize)/2-1; i >= 0; i--)
        HEAPify(h, i);
}
```

### Complessità
Intuitivamente si direbbe O(n logn), ma is può fare una stima più precisa:
$$
\begin{align*}
T(n) &= 2T(n/2) + log2(n)\\
T(n/2) &= 2T(n/4) + log2(n/2)\\
T(n/4) &= 2T(n/8) + log2(n/4)\\
\\
T(n) &= \sum_{i=0}^{log_2(n)} 2^i log_2(\frac{n}{2^i})\\
\end{align*}
$$
ora dato che:

$2^i log_2(\frac{n}{2^i}) = 2^i (log_2(n) - log_2(2^i)) = 2^i (log_2(n) - i)$

ricordandosi le due sommatorie:

$\sum_{i=0}^{log_2(n)} 2^i = 2^{log_2(n)+1}-1 = 2n-1$

$\sum_{i=0}^{k} i2^i = 2-2(k+1)2^k + 4k2^k$

sostituendo con $k=log_2(n)$:
$$
\begin{align*}
\sum_{i=0}^{log_2(n)} i2^i &= 2-2(log_2(n)+1)2^{log_2(n)} + 4log_2(n)2^{log_2(n)} =\\
&= 2 - 2n(log_2(n)+1) + 4n log_2(n) \\
&= 2 + 2n log_2(n) - 2n
\end{align*}
$$

Otteniamo:
$$
\begin{align*}
T(n) &= \sum_{i=0}^{log_2(n)} 2^i log_2(\frac{n}{2^i}) \\
&= \sum_{i=0}^{log_2(n)} 2^i log_2(n) - \sum_{i=0}^{log_2(n)} 2^i i \\
&= log_2(n) (2n -1) - (2+ 2n log_2(n) - 2n)\\
&= 2n log_2(n) - log_2(n) - 2 - 2n log_2(n) + 2n \\
&= 2n -2- log_2(n) \\
&= O(n)
\end{align*}
$$
Questo si può capire intuitivamente perchè metà delle chiamate heapif sono fatte su sottoalberi con un solo figlio, un quarto con sottoalberi con due figli... e così via solo due sono fatte su sottoalberi con n/2 figli e una è fatta sul sottoalbero intero.

## HeapSort
HeapSort è un algoritmo di ordinamento (di vettori, non di heap, non c'è un heap disordiato e uno ordinato) basato su heap. L'idea è di costruire uno heap con i dati da ordinare (HEAPbuild), e poi sfruttare la proprietà che l'elemento massimo è nella radice, e il minimo nella foglia più bassa. Una volta realizzato l'heap, si scambia la radice con l'ultimo elemento, si decrementa la dimensione dell'heap (in modo da far agire HEAPify solo sugli altri elementi, e non toccare la radice che abbiamo estratto), e si chiama HEAPify sulla radice. Si ripete finchè l'heap non ha lunghezza 0. Il vettore risultante è ordinato in modo crescente.

la complessità è O(nlogn) (vedi analisi di HEAPbuild), qundi come quicksort.

```c
void HEAPsort(Heap h) {
    int i, j;
    HEAPbuild(h);
    j = h->heapsize;
    for (i = h->heapsize-1; i > 0; i--) {
        Swap(h,0,i);
        h->heapsize--;
        HEAPify(h,0);
    }
    h->heapsize = j;
}
```
vedi esempio a pag 26-31

### Complessità
La complessità di HEAPsort è O(nlogn) perchè chiama HEAPify n volte, e HEAPify ha complessità O(logn). Il trucco che fa diminuire la compelssità di heapbuild, qui non si può applicare, in questo caso metà degli heapify sono fatti su un sottoalbero di altezza log2(n), un quarto su uno di altezza log2(n/2), ..., solo due su un sottoalbero di altezza 2 e solo una su un sottoalbero di altezza 1.

# Code a priorità
struttura dati PQ per mantenere un set di elementi di tipo Item, ciascuno dei quali include un campo priorità. Si può implementare con
- vettore/lista (oridnato/a)/(non ordinato/a)
- heap
 
Complessità:
| | PQinsert | PQshowMax| PQextractMax |
|---|---|---|---|
| vettore non ordinato | 1 | n | n |
| lista non ordinata   | 1 | n | n |
| vettore ordinato     | n | 1 | 1 |
| lista ordinata       | n | 1 | 1 |
| heap                 | logn | 1 | logn |

```c
// PQ.h
typedef struct pqueue *PQ;

PQ PQinit(int maxN);
void PQfree(PQ pq);
int PQempty(PQ pq);
void PQinsert(PQ pq, Item val);
Item PQextractMax(PQ pq);
Item PQshowMax(PQ pq);
void PQdisplay(PQ pq);
int PQsize(PQ pq);
void PQchange(PQ pq, Item val);
```

## Implementazione con HEAP
RICORDA: il tipo ITEM che sta nell'heap ha come chiave la priorità (ma anche altri campi, come per esempio il nome e il malanno se la coda a priorità è quella di un pronto soccorso).
```c
// PQ.c
#include <stdlib.h>
#include "Item.h"
#include "PQ.h"
struct pqueue { Item *A; int heapsize; };

static int LEFT(int i) { return (i*2 + 1); }
static int RIGHT(int i) { return (i*2 + 2); }
static int PARENT(int i) { return ((i-1)/2); }

PQ PQinit(int maxN){
    PQ pq = malloc(sizeof(*pq));
    pq->A = (Item *)malloc(maxN*sizeof(Item));
    pq->heapsize = 0;
    return pq;
}

void PQfree(PQ pq){
    free(pq->A);
    free(pq);
}

int PQempty(PQ pq) { return pq->heapsize == 0; }
int PQsize(PQ pq) { return pq->heapsize; }
Item PQshowMax(PQ pq) { return pq->A[0]; }

void PQdisplay(PQ pq) {
    int i;
    for (i = 0; i < pq->heapsize; i++)
        ITEMstore(pq->A[i]);
}
```

### PQinsert
Prima si aggiunge la nuova foglia in basso (rispettando la proprietà strutturale), poi si risale dal nodo corrente (inizialmente la foglia appena creata) fino al più alla radice. Si confronta la chiave del dato contenuto nel padre con la chiave del dato da inserire, facendo scendere il dato del padre nel figlio se la chiave da inserire è maggiore, altrimenti inserisce il dato nel nodo corrente.

Complessità: O(logn)

```c
void PQinsert (PQ pq, Item val) { int i;
    i  = pq->heapsize++;
    // itera a partire dal padre dell'ultima foglia
    while((i>=1) && (KEYcmp(KEYget(pq->A[PARENT(i)]),KEYget(val))==-1)){
        pq->A[i] = pq->A[PARENT(i)];
        i = (i-1)/2;
    }
    pq->A[i] = val;
    return;
}
```

Vedere esempio a pag 44-48

Esercizi tipo:
vettore contiene dati, trasformarlo in un HEAP.
C'è un HEAP vuoto in cui stiamo inserendo delle chiavi in sequenza

## PQextractMax
Funzione per modificare lo heap, estraendone il valore massimo, che è contenuto nella radice. Pseudocodice:
- scambia la radice con l'ultima delle foglie (quella più a destra nell'ultimo livello)
- riduce di 1 della dimensione dello heap
- ripristina le proprietà dello heap mediante applicazione di HEAPify.

in questo modo avremmo, nel nostro vettore, una cella in più non utilizzata, ma vabbè.

Complessità: O(logn)

```c
Item PQextractMax(PQ pq) { Item val;
    Swap (pq, 0,pq->heapsize-1);
    val = pq->A[pq->heapsize-1];
    pq->heapsize--;
    HEAPify(pq, 0);
    return val;
}
```

vedere l'esempio pag 51-53

## PQchange
Modifica la priorità di un elemento, tipo signor rossi con gamba rotta passa da codice rosso (priorità 5 per esempio) a codice verde (priorità 1 per esmpio). La posizione del signor rossi, cioè l'indice, nella lista/heap è trovata con una scansione (il nome sarà un altro campo di Item) (costo lineare). Se la priorità sale, il nodo risale dalla posizione data fino al più alla radice confrontando la chiave del padre con la chiave modificata, facendo scendere la chiave del padre nel figlio se la chiave modificata è maggiore, altrimenti la inserisce nel nodo corrente. Se la priorità scende si applica HEAPify al nodo corrente.

Complessità: O(n) (scansione per trovare il nome) + O(logn) = O(n)

la heapyfi viene anche chiamata FixDown. Invece il processo di risalita viene chiamato FixUp.

Vedere esempio pag 55-61

```c
void PQchange (PQ pq, Item val) {
    int i, found = 0, pos;
    for (i = 0; i < pq->heapsize && found == 0; i++)
        if (NAMEcmp(NAMEget(&(pq->A[i])), NAMEget(&val))==0) {
        found = 1;
        pos = i;
    }
    if (found==1) {
        while(pos>=1 && PRIOget(pq->A[PARENT(pos)])<PRIOget(val)){
            pq->A[pos] = pq->A[PARENT(pos)];
            pos = (pos-1)/2;
        }
        pq->A[pos] = val;
        Heapify(pq, pos);
    }
    else
        printf("key not found!\n");
    return;
}
```

È possibile migliorare da O(n) a O(logn)? Si basta sapere già dove si trova l'item di Signor Rossi. ma come si fa?
- L'item è un indice o ha tra i vari campi valori l'indice della sua posizione nel vettore
- Se la chiave dell'item è univoca, la si può usare come chiave di una tabella di hash (o bst bilanciato= che contiene la posizione dell'item nella pq.

# Coda prioritaria di indici
Non si inseriscono in coda gli item ma coppie (indice, priorità), quindi si adotta la versione di «chiave affiancata al dato» (la priorità è un parametro aggiuntivo) invece che «chiave parte del dato».
Il vettore pq->qp (posizione in coda) serve per implementare PQchange efficiente, identificando la posizione dell’elemento nello heap con costo O(1) (l’elemento è un indice) senza bisogno di una scansione lineare. Cioè nel vettore pq->qp, all'indice i, c'è l'indice dell'item i-esimo (esempio di pq->qp: [3, 11, ...] dove gli item sono: ["signor rossi", "signor neri", ...]). Quindi se voglio cambiare la priorità di un item, vado a vedere in pq->qp in che posizione è, e poi vado a modificare l'item in quella posizione.

