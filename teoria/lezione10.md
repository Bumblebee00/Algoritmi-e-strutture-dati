[13/11/2023] In questa lezione facciamo un piccolo ripasso sul quicksort e poi parliamo di applicazioni/esmpi di algoritmi di ricerca e ordinamento.

# QuickSort
Si sceglie un elemento del vettore (pivot) e si riordinano gli elementi in modo che tutti quelli minori del pivot siano a sinistra e tutti quelli maggiori a destra. Si ripete ricorsivamente la procedura sui due sottovettori. A differenza del merge sort, la divisione non è esattamente a metà. A differenza del merge sort non è necessario un vettore ausiliario, perchè gli elementi vengno scambiati a due a due.

## Pseudocodice
(?)

## Codice
```c
void QuickSort(Item A[], int N) {
    int l=0, r=N-1;
    quicksortR(A, l, r);
}
void quicksortR(Item A[], int l, int r ){
    int q;
    if (l >= r) terminazione
    return;
    q = partition(A, l, r);
    quicksortR(A, l, q-1);
    quicksortR(A, q+1, r);
    return;
}
```
```c
int partition (Item A[], int l, int r ){
  int i = l-1, j = r;
  Item x = A[r];
  for ( ; ; ) {
while(ITEMlt(A[++i], x));
    while(ITEMgt(A[--j], x));
    if (i >= j)
      break;
    Swap(A, i, j);
  }
  Swap(A, i, r);
  return i;
}

void Swap(Item *v, int n1,
          int n2) {
  Item temp;
  temp  = v[n1];
  v[n1] = v[n2];
  v[n2] = temp;
  return;
}
```
## Caratteristiche
| pro | contro |
| --- | ------ |
| in loco, non richiede un altro vettore | non stabile, cioè se due elementi sono uguali, l’ordine relativo tra di loro può cambiare |

## Complessità
L'efficienza dell'algoritmo dipende dal bilanciamento delle partizioni. a ogni passo partition ritorna:
- caso peggiore: un vettore da n-1 elementi e l’altro da 1 elemento
- caso migliore: due vettori da n/2 elementi
- caso medio: due vettori di dimensioni diverse.
Il bilanciamento è legato alla scelta del pivot.

### Caso peggiore
il pivot = minimo o massimo in vettore già ordinato in ordine opposto a quello desiderato
T(1) = 1
T(n) = T(n-1) + n + 1
     = ...(?)... = O(n^2)

### Caso migliore
T(1) = 1
T(n) = 2T(n/2) + n
     = ...(?)... = O(n*logn)

### Caso medio
La probabilià dei capitare nel caso peggiore è 1/(n!)
Se invece capito in un caso molto sfortunato, ma non il peggiore ...(?)

T(n) = ...(?)... = O(n*logn)

## Scelta del pivot
L'unica cosa importante è non capitare nel caso peggiore.

# Esempi di algoritmi di ricerca e ordinamento

## Lampadine
Un interruttore controlla più lampadine, e ne scambia lo stato da acceso a spento e viceversa. Si parte da tutte le lampadine spente, vogliamo trovare il più piccolo insieme di interruttori che accenda tutte le lampadine.  Dato che cerchiamo un sottoinsieme di cardinalità minima, è un problema di ottimizzazione.\
Quindi una lampadina è accesa se e solo se il numero di interruttori che la controllano, accesi, è dispari.
Altenativamente possiamo fare xor tra lo stato di ogni lampadina e lo stato di ogni interruttore che la controlla. Se il risultato è 1, la lampadina è accesa, altrimenti è spenta.

### Soluzione
Creiamo il powerset degli interruttori e per ogni sottoinsieme verifichiamo se accende tutte le lampadine. Se sì, lo aggiungiamo alla lista delle soluzioni. Alla fine restituiamo la soluzione di cardinalità minima.
Realizziamo l'iniseme delle parti, la tecnica più adatta in questo caso è quella delle combinazioni, perchè crea prima le combinazioni di cardinalità 1, poi 2, 3, ... fino a n. È la più adatta perchè appena trovo un sottoinsieme che funziona, è sicuro che sia di cardinalità minima.

```c
???
```

# Longest increasing sequence
