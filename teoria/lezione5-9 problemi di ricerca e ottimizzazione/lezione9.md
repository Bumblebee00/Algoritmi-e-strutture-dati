[14/11/2023] In questa lezine abbiamo trattato di esplorazione dello spazio delle soluzioni nel caso sia necessaria solo una soluzione, e di pruning.
- [Esplorazione esaustiva dello spazio delle soluzioni, quando una singola soluzione è necessaria](#esplorazione-esaustiva-dello-spazio-delle-soluzioni-quando-una-singola-soluzione-è-necessaria)
  - [Uso di un flag](#uso-di-un-flag)
  - [Uso di un valore di ritorno](#uso-di-un-valore-di-ritorno)
- [Esempio: conto corrente](#esempio-conto-corrente)
  - [Soluzione](#soluzione)
- [Esempio: lo zaino](#esempio-lo-zaino)
  - [Soluzione](#soluzione-1)
    - [Calcolo del powerset + controllo](#calcolo-del-powerset--controllo)
    - [Main](#main)
- [Pruning](#pruning)
  - [Esempio semplice di pruning](#esempio-semplice-di-pruning)
    - [Senza pruning](#senza-pruning)
    - [Con pruning](#con-pruning)
  - [Esempio: lo zaino con il pruning](#esempio-lo-zaino-con-il-pruning)
# Esplorazione esaustiva dello spazio delle soluzioni, quando una singola soluzione è necessaria
La ricorsione è particolarmente utile quando si vogliono elencare tutte le soluzioni e questo è obbligatorio nei problemi di ottimizzazione. Se ne basta una sola, bisogna far sì che tutte le ricorsioni si chiudano, ricordando che ognuna torna a quella che l’ha chiamata. È infatti errato pensare di poter «forare» la catena delle ricorsioni, tornando subito a quella iniziale.\
Come procedere? Ci sono due mdodi:
- introduciamo un falg (che può essere implementata come variabile globale o come parametro della funzione ricorsiva passato by reference) che indica se la soluzione è stata trovata o meno
- la funzione rucorsia returna un valore che indica se la soluzione è stata trovata o meno

## Uso di un flag
(non trattiamo neanche l'implementazione con varaibile globale)
```c
int main(){
    ...
    int stop = 0;
    ...
    funz_ric(... , &stop);
    ...
}

void funz_ric(..., int *stop_ptr) {
    ...
    if (condizione di terminazione) {
        ...
        (*stop_ptr) = 1;
        return;
    }
    for (i=0; condizione su i && (*stop_ptr)==0; i++) {
        ...
        funz_ric(..., stop_ptr);
        ...
    }
    return;
}
```

## Uso di un valore di ritorno
```c
int main(){
    ...
    if (funz_ric(...)==0)
        printf(“soluzione non trovata\n”);
    ...
}
int funz_ric(.....) {
    if (condizione di terminazione)
        if (condizione di accettazione) {
            .....
            return 1;
        return 0;
    }
    for (ciclo sulle scelte) {
        scelta;
        if (funz_ric(.....))
            return 1;
        .....
    }
    return 0;
}
```

# Esempio: conto corrente
Input: vettore di interi di lunghezza nota n. Ogni intero rappresenta un movimento distinto su un conto bancario:
- \>0: entrata
- <0: uscita
Dato un ordine per i movimenti, il saldo corrente è il valore ottenuto sommando algebricamente al saldo precedente (inizialmente 0), tutti i movimenti fino al movimento corrente (chiaramente è indipendente dall'ordine). Vogliamo, tra tutti i possibili ordini, trovare quello nel quale la differenza tra saldo massimo e minimo (in tutto il tempo) è minima.

## Soluzione
(Vedi 08contocorrente.c)
Usiamo un algoritmo ricorsivo per elencare tutti i possibili ordinamenti (n!). Arrivati alla condizione di terminazione, calcoliamo il saldo massimo e minimo e lo confrontiamo con il minimo trovato finora. Se è minore, aggiorniamo il minimo trovato finora e ci salviamo l'ordinamento.\
```c
int min_diff = INT_MAX;

int main(void) {
    // val è il vettore dei movimenti
    // sol è il vettore che contiene l'ordinamento corrente
    // mark è il vettore che contiene le informazioni sulle scelte fatte
    // fin è il vettore che contiene l'ordinamento che genera la differenza minima
    int i, n, *val, *sol, *mark, *fin;

    printf("Inserisci n: ");
    scanf("%d", &n);

    // ...allco dinamicamente val, sol, mark, fin...
    // ...riempio val in qualche modo...

    for (i=0; i < n; i++) {
        sol[i]= -1;
        mark[i]= 0;
    }

    perm(0, val, sol, mark, fin, n);

    // ...stampa fin...
}

void perm(int pos, int *val, int *sol, int *mark, int *fin, int n) {
    int i;

    if (pos >= n) {
        check(sol, fin, n);
        return;
    }

    for (i=0; i<n; i++)
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[pos] = val[i];
            perm(pos+1, val, sol, mark, fin, n);
            mark[i] = 0;
        }
    return;
}

void check(int *sol, int *fin, int n) {
    int i, saldo = 0, max_curr = 0, min_curr = INT_MAX, diff_curr;

    for (i=0; i<n; i++) {
        saldo += sol[i];
        if (saldo > max_curr)
            max_curr = saldo;
        if (saldo < min_curr)
            min_curr = saldo;
    }
    diff_curr = max_curr - min_curr;
    if (diff_curr < min_diff) {
        min_diff = diff_curr;
        for (i=0; i<n; i++)
            fin[i] = sol[i];
    }
    return;
}
```

# Esempio: lo zaino
Dato un insieme di N oggetti ciascuno dotato di peso $w_{j}$ e di valore $v_{j}$, e dato un peso massimo cap, determinare il sottoinsieme S di oggetti tali che:
- il peso totale è minore o uguale a cap
- il valore totale è massimo

## Soluzione
Useremo il powerset generato da disposizioni ripetute. A ogni sottoinsieme controlliamo se è <= al cap, in caso affermativo calcoliamo il valore totale e lo confrontiamo con il massimo trovato finora.
(Vedi 09knapsack_no_pruning.c)
### Calcolo del powerset + controllo
```c
void powerset(int pos, Item *items, int *sol, int k, int cap, int c_cap, int c_val, int *b_val, int *b_sol){
    int j;

    if (pos >= k) { // condizione di terminazione
        if (c_cap <= cap) { // condizione di accettabilità
            if (c_val > *b_val) { // track del migliiore
                for (j=0; j<k; j++)
                    b_sol[j] = sol[j];
                *b_val = c_val;
            }
        }
        return;
    }

    sol[pos] = 1;
    c_cap += items[pos].size;
    c_val += items[pos].value;
    powerset(pos+1, items, sol, k, cap, c_cap, c_val, b_val, b_sol);
    sol[pos] = 0;
    c_cap -= items[pos].size;
    c_val -= items[pos].value;
    powerset(pos+1, items, sol, k, cap, c_cap, c_val, b_val, b_sol);
}
```
### Main
```c
int main(void) {
    int i, n, cap, *sol, *b_sol, b_val = 0;
    Item *items;

    printf("Inserisci n: ");
    scanf("%d", &n);
    printf("Inserisci cap: ");
    scanf("%d", &cap);

    // ...allocazione dinamica di items, sol, b_sol...
    // ...riempimento di items...

    powerset(0, items, sol, n, cap, 0, 0, &b_val, b_sol);

    // ...stampa b_sol...
}
```

# Pruning
A volte lo spazio di ricerca è toppo grande, perciò si scarta una parte dello spazio di ricerca, che si è sicuri non contenga soluzioni migliori di quelle già trovate. Questo si chiama pruning dell'albero di ricerca.
## Esempio semplice di pruning
S = {2, 1, 6, 4} (S ha n=4 elementi); X = 7\
trova tutti i sottoinsiemi di S che sommati danno X.\
### Senza pruning
Il modello del problema è il powerset, quindi O(n^2) nel caso senza pruning 
```c
int main(void) {
    int i, n, X, *S, *sol;

    // ... get n, X, S in input...

    printf("The subset(s) whose sum is %d is (are): \n", X);
    powerset(0, S, sol, n, X);
}

void powerset(int pos, int *S, int *sol, int n, int X) {
    int j, out;

    if (pos >= n) {
        out = check(sol, S, X, n);
        if (out==1) {
            //... print sol ...
        }
        return;
    }

    sol[pos] = 0;
    powerset(pos+1, S, sol, n, X);
    sol[pos] = 1;
    powerset(pos+1, S, sol, n, X);
}
```

### Con pruning
Useremo la creazione di powerset per disposizioni ripetute, quindi una funzione ricorsiva che crea il powerset aggiungendo elementi. Con il pruning vogliamo anticipare il più possibile la valutazione dei vincoli. Per farlo:
- **ordinamo S** in ordine crescente.
- introduciamo la variabile `p_sum` che contiene la somma dei valori degli elementi già inseriti nella soluzione (questa c'era anche nella).
- introduciamo la variabile `r_sum` che contiene la somma dei valori degli elementi non ancora inseriti nella soluzione.
- prendiamo un elemento `x` nella soluzione se `p_sum + x <= X` e `p_sum + r_sum >= X`. in caso contrario scartiamo completamete tutto questo ramo dell'albero (pruning).

```c
int main(void) {
    int i, n, total=0;
    int *sol, *S, X;

    // ... get n, X, S in input...
    // ...total = sum of all elements in S...

    MergeSort(S, n);

    if((total < X))
        printf("No solution possible \n");
    else {
        printf("The solution is:\n");
        sumset(0, S, sol, 0, total, X);
    }
}

int promising(int *S, int pos, int p, int r, int X) {
  return(p+r>=X)&&(p+S[pos]<=X);
}

void sumset(int pos, int *S, int *sol, int p, int r, int X) {
    int j;

    if (p==X) {
        // ...stampa sol...
        return;
    }

    if (promising(S,pos,p,r,X)) {
        sol[pos]=1;
        sumset(pos+1, S, sol, p+S[pos], r-S[pos], X);
        sol[pos]=0;
        sumset(pos+1, S, sol, p, r-S[pos], X);
    }
}
```


## Esempio: lo zaino con il pruning
come l'esempio senza pruning, ma prima di proseguire giù per un ramo, del powerset, controllo la condizione promising, che in questo caso sarà:
- `current_size + items[pos].size <= cap`