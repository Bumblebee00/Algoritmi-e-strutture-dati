Tratteremo di algoritmi di tipo ottimo (O(n) o O(nlogn)) (merge sort e quick sort). ma prima una premessa sul tipo di dati che ordiniamo.

## Tipo di dato astratto adt

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

    ...

    #define maxKey 100
    typedef int Item;

    Item ITEMscan();
    int  ITEMeq(Item A, Item B);
    int  ITEMneq(Item A, Item B);
    int  ITEMlt(Item A, Item B);
    int  ITEMgt(Item A, Item B);
    void ITEMshow(Item A);
    Item ITEMrand();

    ...

    #include <item.h>

    int ITEMeq(Item A, Item B) {
        return (A == B);
    }

    int ITEMneq(Item A, Item B) {
        return (A != B);
    }

    int ITEMlt(Item A, Item B) {
        return (A < B);
    }

    int ITEMgt(Item A, Item B) {
        return (A > B);
    }

    Item ITEMscan(){
        Item A;
        printf(“item = "); scanf("%d", &A);
        return A;
    }
    
    void ITEMshow(Item A) {
        printf(“%6d \n", A);
    }

    Item ITEMrand() {
        Item A= maxKey*((float)rand()/RAND_MAX);
        return A;
    }

    ...

# Merge Sort
(Von Neumann, 1945)
Prendi un vettore, se non è ordinato dividi et impera. (vedi esempio a pagina 9 delle slides)
Ricorsione
- condizione di terminazione: con 1 (l=r) o 0 (l>r) elementi il vettore è ordinato
- merge sort su sottovettore SX
- merge sort su sottovettore DX
Ricombinazione:
- fondi i due sottovettori ordinati in un vettore ordinato.

### Funzione ricorsiva
    // wrapper, cosicchè l'utente debba solo passare il vettore da ordinare
    void MergeSort(Item A[], Item B[], int N) {
    int l=0, r=N-1;
    MergeSortR(A, B, l, r);
    }

    void MergeSortR(Item A[], Item B[], int l, int r) {
    int q;
    if (r <= l) // condizione di terminazione
        return;
    q = (l + r)/2;
    MergeSortR(A, B, l, q);
    MergeSortR(A, B, q+1, r);
    Merge(A, B, l, q, r);
    }

### 2-way merge
Ipotesi: la dimensione del vettore A è una potenza di 2; N = 2^p. fusione di 2 (2-way) sottovettori di A ordinati di ugual
dimensione per ottenere un vettore ordinato di dimensione doppia. vettore ausiliario B di dimensione N con indice l ≤ k ≤ r per memorizzare i risultati delle fusioni passato come parametro.
Approccio: scorrere i sottovettori sinistro e destro mediante gli indici i e j. se A[i] (elemento di sinistra) è minore di A[j] (elemento di destra) allora aggiungilo al vettore temporaneo B e incrementa i (1), altrimenti aggiungi A[j] e incrementa j (2). se uno dei due sottovettori è finito, aggiungi tutti gli elementi rimanenti dell’altro sottovettore (3).

    void Merge(Item A[], Item B[], int l, int q, int r) {
    int i, j, k;
    i = l;
    j = q+1;
    for(k = l; k <= r; k++)
        if (i > q)
            B[k] = A[j++]; // (3)
        else if (j > r)
            B[k] = A[i++]; // (3)
        else if (ITEMlt(A[i], A[j]) || ITEMeq(A[i], A[j])  ) // (4)
            B[k] = A[i++]; // (1)
        else
            B[k] = A[j++]; // (2)
    for ( k = l; k <= r; k++ )
        A[k] = B[k];
    return;
    }

### Pro e contro del merge sort
#### Contro:
- Non in loco: richiede un altro vettore B di N elementi
#### Pro:
- è stabile: se due elementi sono uguali, l’ordine relativo tra di loro non cambia (grazie al 4). Quesot è importente perchè i due item sono uguali solo per quanto riguarda la chiave, non in generale

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

# Quick Sort (Hoare, 1962)
(anche visto nella lezione 10)
Come il merge sort ma anzichè dividere il vettore A[l..r] a metà, lo divide così:
- dato un elemento pivot x = A[q]
- crea un vettore sinistro con tutti gli elementi minori del pivot (A[l..q-1]) (non è necessariamente la metà in lunghezza del vettore originale)
- crea un vettore destro con tutti gli elementi maggiori del pivot (A[q+1..r])
- il pivot va in posizione q
Poi sui sottovettori destro e sinistro si ripete la procedura ricorsivamente (condizione di terminazione: vettore di lunghezza 1). Non c'è fase di ricombinazione perchè il vettore è già ordinato.

### Partizione alla Hoare
- pivot x = A[r]
- facciamo due cicli while, uno che parte da sinistra e uno da destra (i e j)
- il primo si ferma quando trova un elemento maggiore del pivot, il secondo quando trova un elemento minore del pivot
- quando ho trovato questi due elementi, scambia i due elementi
- quando i e j si incontrano, ho finito, quindi scambia il pivot con l'elemento in posizione j. così il pivot è nella sua posizione giusta nel vettore, e tutti gli elementi a sinistra sono minori del pivot, tutti quelli a destra sono maggiori del pivot.

Si osservi che, se il pivot compare in più istanze, è irrilevante che esse si trovino alla fine della partition nel sottovettore sinistro o in quello destro, l’importante è che l’istanza scelta come pivot finisca nella posizione finale.

    // wrapper
    void QuickSort(Item A[], int N) {
    int l=0, r=N-1;
    QuickSortR(A, l, r);
    }

    void QuickSortR( Item A[], int l, int r ) {
    int q;
    if (r <= l)
        return;
    q = partition(A, l, r);
    QuickSortR(A, l, q-1);
    QuickSortR(A, q+1, r);
    return;
    }

    int partition ( Item A[], int l, int r ) {
    int i, j;
    Item x = A[r];
    i = l-1;
    j = r;
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

### Pro e contro del quick sort
#### Pro:
- in loco: non richiede un altro vettore
#### Contro:
- non è stabile: se due elementi sono uguali, l’ordine relativo tra di loro può cambiare

### Complessità
Caso migliore: il pivot divide il vettore in due parti uguali, e allora il quick sort è come il merge sort, quindi O(n*logn)
Caso peggiore: il pivot divide il vettore in due parti di dimensione 1 e n-1, e allora il quick sort è come l'insertion sort, quindi O(n^2)
Caso medio: O(n*logn)

Come scelgo il pivot? a caso, o prendo il primo elemento, o l'ultimo, o la mediana tra i tre.

# Tabella Riassuntiva
| Algoritmo | In loco | Stabile | Caso migliore | Caso peggiore | Caso medio |
| --- | --- | --- | --- | --- | --- |
| Insertion sort | Sì | Sì | O(n) | O(n^2) | O(n^2) |
| Selection sort | Sì | No | O(n^2) | O(n^2) | O(n^2) |
| Merge sort | No | Sì | O(n*logn) | O(n*logn) | O(n*logn) |
| Quick sort | Sì | No | O(n*logn) | O(n^2) | O(n*logn) |

