NOTA: questa lezione tratta gli stessi argomenti di lezione 16, ma con le slides di cabodi anzichè camurati. inoltre non è completa

[4/12/23]

- [ADT Heap](#adt-heap)
  - [Operazioni](#operazioni)
  - [Implementazione](#implementazione)

# ADT Heap
In italiano catasta. come una catasta per terra. non si può prendere l'elemento più in basso perchè crolla tutto. L'heap sostanzialmente è un albero binario. (cos'è un albero binario? è una terna formata da radice, sottoalbero destro, sottoalbero destro). La **proprietà funzionale** dell'heap è che per ogni terna, la chiave contenuta nei sottoalberi è <= della chaive della radice. La sua **proprietà strutturale** è che l'aalbero è completo a sinistra. (cos'è un albero completo a sinistra? è un albero binario in cui tutti i livelli sono pieni tranne l'ultimo che può essere pieno o meno, ma se è meno è pieno a sinistra).

![esempio di heap](esempio%20heap.png)

## Operazioni
- `HEAPifiy(Heap h, int i);` (HEAPificazione) che trasforma un albero in un heap
- `HEAPbuild(Heap h);` che trasforma un array in un heap
- `HEAPsort(Heap h);` che trasforma un heap in un array ordinato
- funzioni di servizio
  - inizializzazione
  - ordinamento
  - display
  - free

## Implementazione
Potremmo implementare questo albero binario con una struttura dati vettore, e usare opportune funzioni `padre`, `figlioSinistro`, `figlioDestro` che dato l'indice di un elemento ritornano l'indice del padre o figlio destro o figlio sinistro.

```c
typedef struct {
  int *A;
  int heapsize; // numero di elementi nell'heap
  int length; // lunghezza dell'array
} Heap;
```
```c
int padre(int i) {
  return (i-1)/2;
}

int figlioSinistro(int i) {
  return 2*i + 1;
}

int figlioDestro(int i) {
  return 2*i + 2;
}
```

non è detto che sia l'implementazione migliore dell'heap, ma è una delle più semplici.