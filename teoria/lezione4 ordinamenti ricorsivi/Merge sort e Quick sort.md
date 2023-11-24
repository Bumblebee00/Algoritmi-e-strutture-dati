In questa lezione, all'inizio introduciamo il concetto di tipo di dato astratto (ADT) e poi parliamo di Merge Sort e Quick Sort. Indice completo del file markdown:
- [Tipo di dato astratto adt](#tipo-di-dato-astratto-adt)
  - [Esempio: scalare e chiave coincidente:](#esempio-scalare-e-chiave-coincidente)
- [Merge Sort](#merge-sort)
  - [Codice](#codice)
    - [Funzione ricorsiva](#funzione-ricorsiva)
    - [2-way Merge](#2-way-merge)
  - [Caratteristiche](#caratteristiche)
  - [Complessità](#complessità)
- [Quick Sort](#quick-sort)
  - [Pseudocodice](#pseudocodice)
  - [Codice](#codice-1)
  - [Caratteristiche](#caratteristiche-1)
  - [Complessità](#complessità-1)
    - [Caso peggiore](#caso-peggiore)
    - [Caso migliore](#caso-migliore)
    - [Caso medio](#caso-medio)
  - [Scelta del pivot](#scelta-del-pivot)
- [Tabella Riassuntiva](#tabella-riassuntiva)


# Tipo di dato astratto adt

Prima di tutto chiariamo cosa vogliamo ordinare:
Vorremmo in qualche modo **disgiungere i dati da ordinare dall'algoritmo di ordinamento**. ciò ci permette di concentrarci sull algoritmo più che sul tipo di dato.
Qundi per generalizzare, diciamo che volgiamo ordinare un oggetto di tipo Item (generele) (realizzato in c con una struct). Uno dei dati di item sarà la chiave, con cui ordiniamo, gli altri sono dati satelliti. Quindi ci serviranno funzioni per leggere/scrivere, generare valori casuali, accedere alla chiave, confrontare due item, stampare un item.

Item lo definiamo come **Abstract Data Structure, o ADT** (in future vedremo: ci sono adt di prima classe (si nascondono i dettagli all'utente) e quasi adt...). Per esempio potrebbero essere:
- semplice scalare e chiave coincidente
- vettore dinamico di caratteri e chiave coincidente
- scalare e vettore di caratteri sovradimensionato staticamente in una struct
- scalare e vettore di caratteri allocato dinamicamente in una struct.

### Esempio: scalare e chiave coincidente:
Per adesso ci limitiamo a un dato scalare, ma introduciamo lo stesso un tipo di dato item, perchè ci piace l'astrazione. questo è un quasi ADT, non un ADT ben fatto, perchè andando a vedere dentro il file .h posso vedere come è fatto il tipo di dato Item. (uno veramente ben fatto avrebbe un puntatore offuscato)

```c
#define maxKey 100
typedef int Item;

Item ITEMscan();
int  ITEMeq(Item A, Item B);
int  ITEMneq(Item A, Item B);
int  ITEMlt(Item A, Item B);
int  ITEMgt(Item A, Item B);
void ITEMshow(Item A);
Item ITEMrand();
```
```c
#include <item.h>

int ITEMeq(Item A, Item B) { return (A == B); }

int ITEMneq(Item A, Item B) { return (A != B); }

int ITEMlt(Item A, Item B) { return (A < B); }

int ITEMgt(Item A, Item B) { return (A > B); }

void ITEMshow(Item A) { printf("%6d \n", A); }

Item ITEMscan(){
    Item A;
    printf("item = "); scanf("%d", &A);
    return A;
}

Item ITEMrand() { Item A= maxKey*((float)rand()/RAND_MAX); return A; }
```

# Merge Sort
(Von Neumann, 1945)
Prendi un vettore, se non è ordinato dividi et impera. (vedi esempio a pagina 9 delle slides). La ricorsione avviene nel seguente modo:
- condizione di terminazione: con 1 (l=r) o 0 (l>r) elementi il vettore è ordinato
- merge sort su sottovettore SX
- merge sort su sottovettore DX

Ricombinazione:
- unisci i due sottovettori ordinati in un vettore ordinato. Esempio [1,3] untio a [2,5] diventa [1,2,3,5]

## Codice
### Funzione ricorsiva
```c
// wrapper😎, cosicchè l'utente debba solo passare il vettore da ordinare e non gli indici
void MergeSort(Item A[], Item B[], int N) {
    int l=0, r=N-1;
    MergeSortR(A, B, l, r);
}

void MergeSortR(Item A[], Item B[], int l, int r) {
    int q;
    if (r <= l) // condizione di terminazione
        return;
    q = (l + r)/2; // metà
    MergeSortR(A, B, l, q);
    MergeSortR(A, B, q+1, r);
    Merge(A, B, l, q, r);
}
```
### 2-way Merge
Ipotesi: la dimensione del vettore A è una potenza di 2; N = 2^p. fusione di 2 (2-way) sottovettori di A ordinati di ugual dimensione per ottenere un vettore ordinato di dimensione doppia. vettore ausiliario B di dimensione N con indice l ≤ k ≤ r per memorizzare i risultati delle fusioni passato come parametro.\
Approccio: scorrere i sottovettori sinistro e destro mediante gli indici i e j. se A[i] (elemento di sinistra) è minore di A[j] (elemento di destra) allora aggiungilo al vettore temporaneo B e incrementa i (1), altrimenti aggiungi A[j] e incrementa j (2). se uno dei due sottovettori è finito, aggiungi tutti gli elementi rimanenti dell’altro sottovettore (3).
```c
void Merge(Item A[], Item B[], int l, int q, int r) {
    int i, j, k;
    i = l;
    j = q+1;
    for(k = l; k <= r; k++)
        if (i > q)
            B[k] = A[j++]; // (3)
        else if (j > r)
            B[k] = A[i++]; // (3)
        else if (ITEMlt(A[i], A[j]) || ITEMeq(A[i], A[j]))
            B[k] = A[i++]; // (1)
        else
            B[k] = A[j++]; // (2)
    for ( k = l; k <= r; k++ )
        A[k] = B[k];
    return;
}
```

## Caratteristiche
| pro | contro |
| --- | ------ |
| è stabile: se due elementi sono uguali, l’ordine relativo tra di loro non cambia | Non in loco: richiede un altro vettore B di N elementi |

### Complessità
Ipotesi: n=2^p
Dividere: O(1)
Ricorsione: due sottoproblemi di dimensione metà
Terminazione: O(1)
Combina: O(n) nel caso peggiore

T(n) = 2T(n/2) + n
T(1) = 1

Risoluzione per unfolding:
T(n/2) = 2T(n/4) + n/2
T(n/4) = 2T(n/8) + n/4
...

T(n)= n + 2(2(2(T(n/8)) + n/4) + n/2) = ...
    = n*(1 + log2n)
    = O(n*logn)

# Quick Sort
(Hoare, 1962) Si sceglie un elemento del vettore (pivot) e si riordinano gli elementi in modo che tutti quelli minori del pivot siano a sinistra e tutti quelli maggiori a destra. Si ripete ricorsivamente la procedura sui due sottovettori. A differenza del merge sort, la divisione non è esattamente a metà. A differenza del merge sort non è necessario un vettore ausiliario, perchè gli elementi vengno scambiati a due a due. A differenza del merge sort, non c'è fase di ricombinazione.

## Pseudocodice
dato un vettore di n elementi v[0..n-1]
```c
QuickSort(v, n) {
    if (n <= 1) return;
    q = partition(v, n);
    QuickSort(v[0..q-1], q);
    QuickSort(v[q+1..n-1], n-q-1);
}

partition(v, n) {
    scelgo un elemento pivot
    int i=0, j=n-1;
    while (i < j) {
        itero i da 0 a n-1, fino a quando trovo un elemeto fuori posto (maggiore del pivot)
        itero j da n-1 a 0, fino a quando trovo un elemeto fuori posto (minore del pivot)
        scambio v[i] con v[j]
    }
    return indice del pivot;
}
```

## Codice
```c
void QuickSort(Item A[], int N) {
    int l=0, r=N-1;
    quicksortR(A, l, r);
}

void quicksortR(Item A[], int l, int r ){
    int q;
    if (l >= r) return;
    q = partition(A, l, r);
    quicksortR(A, l, q-1);
    quicksortR(A, q+1, r);
    return;
}

int partition (Item A[], int l, int r ){
    int i = l-1, j = r;
    Item x = A[r];
    for ( ; ; ) {
        // due cicli while, uno che parte da sinistra e uno da destra
        // il primo si ferma quando trova un elemento maggiore del pivot, il secondo quando trova un elemento minore del pivot
        while(ITEMlt(A[++i], x));
        while(ITEMgt(A[--j], x));
        
        if (i >= j)
            break;
        Swap(A, i, j);
    }
    // scambia il pivot con l'elemento in posizione j
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
- caso migliore: due vettori da n/2 elementi (allora il quicksort è come il merge sort)
- caso medio: due vettori di dimensioni diverse.
Il bilanciamento è legato alla scelta del pivot.

### Caso peggiore
il pivot = minimo o massimo in vettore già ordinato in ordine opposto a quello desiderato
T(1) = 1
T(n)=       T(n-1)       + n + 1
    = (T(n-2) + n-1 + 1) + n + 1
    = n + (n-1) + (n-2) + ... + 3 + 2 + 1 = n*(n+1)/2 = O(n^2)

### Caso migliore
T(1) = 1
T(n)= 2T(n/2) + n
    = 2(2T(n/4) + n/2) + n = 4T(n/4) + 2n
    = ...(?)... = O(n*logn)

### Caso medio
La probabilià dei capitare nel caso peggiore è 1/(n!)
Se invece capito in un caso molto sfortunato, ma non il peggiore:
T(n) = ...(?)... = O(n*logn)

## Scelta del pivot
L'unica cosa importante è non capitare nel caso peggiore.

# Tabella Riassuntiva
| Algoritmo | In loco | Stabile | Caso migliore | Caso peggiore | Caso medio |
| --- | --- | --- | --- | --- | --- |
| Insertion sort | Sì | Sì | O(n) | O(n^2) | O(n^2) |
| Selection sort | Sì | No | O(n^2) | O(n^2) | O(n^2) |
| Merge sort | No | Sì | O(n*logn) | O(n*logn) | O(n*logn) |
| Quick sort | Sì | No | O(n*logn) | O(n^2) | O(n*logn) |

