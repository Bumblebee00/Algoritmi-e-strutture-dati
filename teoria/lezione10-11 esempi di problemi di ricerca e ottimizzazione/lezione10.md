[13/11/2023] In questa lezione parliamo di applicazioni/esmpi di algoritmi di ricerca e ordinamento. ( e ripassato il quicksort, vedi `Merge sort e Quick sort.md`). Indice completo del file markdown:

- [Lampadine](#lampadine)
  - [Algoritmo](#algoritmo)
  - [Strutture dati usate](#strutture-dati-usate)



## Lampadine
Ci sono `n` lampadine e `m` interruttori. Ogni interruttore controlla più lampadine, e ne scambia lo stato da acceso a spento e viceversa. Inizialmente tutte le lampadine sono spente. Vogliamo trovare il più piccolo insieme di interruttori che accenda tutte le lampadine.  Dato che cerchiamo un sottoinsieme di cardinalità minima, è un problema di ottimizzazione.\
Quindi una lampadina è accesa se e solo se il numero di interruttori premuti che la controllano, è dispari. (Altenativamente possiamo fare xor tra lo stato di ogni lampadina e lo stato di ogni interruttore che la controlla. Se il risultato è 1, la lampadina è accesa, altrimenti è spenta)

### Algoritmo
Creiamo il powerset degli interruttori e per ogni sottoinsieme verifichiamo se accende tutte le lampadine. Se sì, lo aggiungiamo alla lista delle soluzioni. Alla fine restituiamo la soluzione di cardinalità minima.
Realizziamo l'iniseme delle parti, la tecnica più adatta in questo caso è quella delle combinazioni semplici (rispetto a disposizioni ripetute), perchè crea prima i sottoinsiemi di cardinalità 1, poi 2, 3, ... fino a n. È la più adatta perchè appena trovo un sottoinsieme che funziona, è sicuro che sia di cardinalità minima.

### Strutture dati usate
Una matrice di interi `mat[m][n]` che rappresenta la relazione tra interruttori e lampadine. Se `matrice[i][j]` è 1, l'interruttore `i` controlla la lampadina `j`, altrimenti no.\
Un vettore di interi `sol[m]` che rappresenta la soluzione corrente.

```c
int main(void) {
    int n, m, k, i, trovato=0, *sol, *mark, **mat;

    //...leggi n, m e la matrice mat da file...

    sol = calloc(n, sizeof(int));
    mark = calloc(n, sizeof(int));

    printf("Powerset mediante combinazioni semplici\n\n");

    for (k=1; k <= n && trovato==0; k++) {
        if(powerset_comb(0, sol, n, k, 0, inter, m))
            trovato = 1;
    }

    // ...libera tutti...
}

int powerset_comb(int pos, int *sol, int n, int k, int start, int **mat,  int m) {
    int i;
    if (pos >= k) {
        if (verifica(mat, m, k, sol)) {
            // ... stampa sol ...
            return 1;
        }
        return 0;
    }

    for (i = start; i < n; i++) {
        sol[pos] = i;
        if (powerset_comb(pos+1, sol, n, k, i+1, mat, m))
            return 1;
    }
    return 0;
}

int verifica(int **mat, int m, int k, int *sol) {
    // ... verifica se gli interruttori in sol accendono tutte le lampadine ...
    // si può implementare sia con il metodo della disparità, sia con il metodo xor
}
```