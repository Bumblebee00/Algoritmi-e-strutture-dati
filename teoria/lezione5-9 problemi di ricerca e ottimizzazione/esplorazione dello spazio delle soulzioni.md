[26/10/23] Questo file corrisponde alle lezioni 5-7.

- [Esplorazione dello spazio di soluzioni](#esplorazione-dello-spazio-di-soluzioni)
- [Rappresentazione delle soluzioni](#rappresentazione-delle-soluzioni)
  - [Principio di addizione](#principio-di-addizione)
  - [Principio di moltiplicazione](#principio-di-moltiplicazione)
- [Elementi di calcolo combiantorio](#elementi-di-calcolo-combiantorio)
  - [Disposizioni semplici](#disposizioni-semplici)
    - [Codice](#codice)
  - [Disposizioni con ripetizioni](#disposizioni-con-ripetizioni)
  - [Permutazioni semplici](#permutazioni-semplici)
    - [Codice](#codice-1)
  - [Permutazioni con ripetizioni](#permutazioni-con-ripetizioni)
    - [Codice](#codice-2)
  - [Combinazioni semplici](#combinazioni-semplici)
  - [Combinazioni con ripetizioni](#combinazioni-con-ripetizioni)
  - [Insime delle parti (Powerset)](#insime-delle-parti-powerset)
    - [Codice Dividi et Impera DA COMPLETARE!!!](#codice-dividi-et-impera-da-completare)
    - [Codice Disposizioni ripetute](#codice-disposizioni-ripetute)
    - [Codice combianzioni semplici](#codice-combianzioni-semplici)
  - [Partizioni di un insieme](#partizioni-di-un-insieme)
    - [Soluzione ricorsiva](#soluzione-ricorsiva)
    - [Soluzione iterativa](#soluzione-iterativa)
- [Esplorazione esaustiva dello spazio delle soluzioni](#esplorazione-esaustiva-dello-spazio-delle-soluzioni)
  - [Struttura dati per la soluzione](#struttura-dati-per-la-soluzione)
    - [Tipologie di strutture dati per oggetti interi](#tipologie-di-strutture-dati-per-oggetti-interi)
  - [Come realizzare il principio di moltiplicazione](#come-realizzare-il-principio-di-moltiplicazione)
    - [Principi base dell'esploarazione](#principi-base-dellesploarazione)

Per adesso abbiamo usato la ricorsione solo per risolvere semplici problemi matematici, con un procedimento matematico che porta, senza scelte e con un numero finito di passi, alla soluzione (fattoriale, determinante di una matrice, numeri di Fibonacci, di Catalan, di Bell). Ora affronteremo problemi di ricerca e ottimizzazione.
## Problemi di ricerca
Abbiamo un insieme di possibilità (che si chiamano soluzioni), tra queste andiamo a individuare quelle valide.
S = insieme soluzioni possiblii
V = insieme soluzioni valide
quindi V ⊆ S
Le domande che ci vogliamo chiedere sono:
- esistono soluzioni valide? V ≠ ∅
- Trovare una o tutte le soluzioni valide

Esempio:
- problema delle 8 regine: mettere 8 regine in una scacchiera 8x8 in modo che nessuna regina minacci un'altra. Sono 64 caselle e 8 regine, quindi 64^8 soluzioni possibili. Ma se metto una regina in una casella, non posso metterne un'altra nella stessa riga, colonna o diagonale. Quindi il numero di soluzioni valide è molto minore.
- sudoku: 9x9 caselle, 9 numeri da 1 a 9. Ogni riga, colonna e quadrato 3x3 deve contenere tutti i numeri da 1 a 9. Il numero di soluzioni possibili è 9^81, ma il numero di soluzioni valide è molto minore di 9^81.
- cammini semplice (cioè senza passare più volte per lo stesso nodo)  in un grafo

## Problemi di ottimizzazione
in questo caso S = V, quindi non ci sono soluzioni non valide. L'obiettivo è trovare la soluzione migliore tra tutte le soluzioni valide. La soluzione migliore è quella che massimizza o minimizza una funzione obiettivo/costo.
Qua bisognia enumerarle tutte per forza.

Esempio:
- massimizzare il numero di oggetti che posso mettere in uno zaino, senza superare il peso massimo che lo zaino può sopportare.
- trovare in un grafo tutti i cammini semplici partenti da un nodo a lunghezza massima.


in generale cose utili da fare sono:
- contare il numero di soluzioni valide
- trovare una soluzione valida
- trovare tutte le soluzioni valide
- trovare la soluzione ottima

# Esplorazione dello spazio di soluzioni
Adottiamo un approccio incrementale: partiamo da una soluzione vuota, poi estendiamo la nostra soluzione mediante scelte.

Algoritmo generico che usa una struttura dati SD:
Ricerca():
  metti la soluzione iniziale in SD
  finché SD non diventa vuota:
    estrai una soluzione parziale da SD;
    se è una soluzione valida, Return Soluzione
    applica le scelte lecite e metti le soluzioni parziali risultanti in SD
  Return fallimento.

Quando SD è:
- una coda (FIFO), la ricerca è in ampiezza (breadth-first)
- una pila (LIFO), la ricerca è in profondità (depth-first)
- una coda a priorità, la ricerca è best-first.

Se l’algoritmo:
- ha conoscenza specifica (euristica), si dice informato
- non conosce nulla del problema, si dice non informato
Se l’algoritmo è in grado di esplorare tutto lo spazio si dice completo.

Noi ci occuperemo di algoritmi di ricerca:
- in profondità
- non informato
- completo (valido solo per problemi più semplici)
- ricorsivo


# Rappresentazione delle soluzioni
Rappresentiamo lo spazio delle soluzioni come un **albero di ricerca**. le nostre soluzioni sono di dimensione n. a ogni nodo, ci sono k ramificazioni (al massimo) verso i figli. la radice è la soluzinoe iniziale vuota, i nodi intermedi sono etichettati con le soluzioni parziali, le foglie sono le soluzioni.

Esempio:
In un ristorante c’è un menu a prezzo fisso composto da antipasto, primo e secondo. Il cliente può scegliere tra 2 antipasti A0, A1; 3 primi P0, P1 e P2 e 2 secondi S0, S1. Quanti e quali pranzi diversi si possono scegliere con questo menu?
La soluzione è un pasto da 3 portate.

per modellare lo spazio delle soluzioni è molto utile il calcolo combinatorio, in particolare il principio di addizione e di moltiplicazione.

## Principio di addizione
Se ho due insiemi disgiunti A e B, il numero di elementi di A U B è la somma del numero di elementi di A e B.
Formulazione alternativa: se un oggetto può essere scelto in p0 modi da un gruppo S0 e in p1 modi da un gruppo S1, allora può essere scelto in p0+p1 modi da S0 U S1.

Esempio:
Ci sono 4 corsi di Informatica e 5 di Matematica. Uno studente ne può seguire 1 solo. In quanti modi può scegliere?
informatica = {i0, i1, i2, i3}
matematica = {m0, m1, m2, m3, m4, m5}
dato che sono insiemi disgiunti, vale il principio di addizione, il numero di modi è 4+5=9

## Principio di moltiplicazione
dati n insiemi S0, S1, ..., Sn-1, ciascuno di cardinalità p0, p1, ..., pn-1, il numero di n-uple (x0, ..., xn) [con x0 ∈ S0, ..., xn-1 ∈ Sn-1] è p0 * p1 * ... * pn-1

Esempio:
In un ristorante c’è un menu a prezzo fisso composto da antipasto, primo, secondo e dolce. Il cliente può scegliere tra 2 antipasti, 3 primi, 2 secondi e 4 dolci. Quanti pranzi diversi si possono scegliere con questo menu?
Antipasti = {a0, a1}
Primi = {p0, p1, p2}
Secondi = {s0, s1}
Dolci = {d0, d1, d2, d3}
numero di scelte possibili = 2 * 3 * 2 * 4 = 48

# Elementi di calcolo combiantorio
Si possono raggruppare k oggetti presi da un gruppo S di n elementi tenendo presente:
- l’unicità degli elementi: gli elementi del gruppo S sono tutti distinti, quindi S è un insieme? O è un multiinsieme (multiset)?
- l’ordinamento: 2 configurazioni sono le stesse a meno di un riordinamento?
- le ripetizioni: uno stesso oggetto del gruppo può o meno essere riusato più volte all'interno di uno stesso raggruppamento?

## Disposizioni semplici
S è un insieme di n elementi. Quante sono le disposizioni semplici di k elementi presi da S? non ci sono ripetizioni e l’ordine conta (k non può essere maggiore di n)
Ds(n,k) = n! / (n-k)! = n * (n-1) * ... * (n-k+1)

Esempio:
Quanti e quali sono i numeri che si possono comporre con 3 cifre distinte?
S = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
n = 10
k = 3
D(10,3) = 10! / (10-3)! = 10! / 7! = 10 * 9 * 8 = 720

### Codice
```c
int disp(int pos,int *val,int *sol,int *mark, int n, int k,int cnt){
    int i;
    // condizione di terminazione
    if (pos >= k){
        for (i=0; i<k; i++) printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }

    for (i=0; i<n; i++){
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[pos] = val[i];
            cnt = disp(pos+1, val, sol, mark, n, k,cnt); mark[i] = 0;
        }
    }
    return cnt;
}
```

## Disposizioni con ripetizioni
S è un insieme di n elementi. Quante sono le disposizioni con ripetizioni di k elementi presi da S? ci sono ripetizioni e l’ordine conta (k può essere maggiore di n)
Dr(n,k) = n^k

Esempio:
Quanti e quali sono i numeri di telefono (8 cifre) che si possono comporre senza la cifra 9?
S = {0, 1, 2, 3, 4, 5, 6, 7, 8}
n = 9
k = 8
Dr(9,8) = 9^8 = 43046721

Quanti e quali sono i numeri binari di 4 bit?
S = {0, 1}
n = 2
k = 4
Dr(2,4) = 2^4 = 16
Soluzione = {0000, 0001, 0010, 0011, 0100, 0101, 0110, 0111, 1000, 1001, 1010, 1011, 1100, 1101, 1110, 1111}

```c
int disp_rip(int pos,int *val,int *sol,int n,int k,int cnt){
  int i;
  if (pos >= k) {
    for (i=0; i<k; i++)
        printf("%d ", sol[i]);
      printf("\n");
      return cnt+1;
  }
  for (i = 0; i < n; i++) {
    sol[pos] = val[i];
    cnt = disp_rip(pos+1, val, sol, n, k, cnt);
  }
  return cnt;
}
```

## Permutazioni semplici
S è un insieme di n elementi. Quante sono le permutazioni possibili? non ci sono ripetizioni e l’ordine conta.
P(n) = n!

Esempio:
Quanti e quali sono gli anagrammi della parola “casa”?
S = {c, a, s, a}
n = 4
P(4) = 4! = 24

### Codice
```c
// DA AGGIUNGERE!!!
```

## Permutazioni con ripetizioni
S è un insieme di n elementi, di cui a elementi sono uguali tra loro, b elementi sono uguali tra loro, c elementi sono uguali tra loro, ecc. Quante sono le permutazioni possibili? non ci sono ripetizioni e l’ordine conta.
P(n,a,b,c,...) = n! / (a! * b! * c! * ...)

Esempio:\
(vedi `03anagrammi_distinti.c`)
Quanti e quali sono gli anagrammi della parola “mamma”? (3 elementi "m" sono uguali tra loro, 2 elementi "a" sono uguali tra loro)
S = {m, a, m, m, a}
n = 5
a = 3
b = 2
P(5,3,2) = 5! / (3! * 2!) = 10

### Codice
```c
... funzioneChiamante(){

    dist_val = malloc(n*sizeof(int));
    sol = malloc(n*sizeof(int));

    perm_r( ... dist_val, sol, ...);
}
/*
(nell'esempio dell'anagramma mamma)
pos è l'indice della ricorsione a cui siamo arrivati (da 0 a 4)
dist_val contiene i valori distinti da usare ([m,a])
sol è il vettore soluzione che viene riempito (alla fine di un ramo sarà [m,a,m,a,m])
mark contiene il numero di volte che ogni elemento distinto può ancora essere usato (inizia da [3,2])
n è la dimensione del vettore soluzione (5)
n_dist è la dimensione del vettore dist_val (2)
cnt è il contatore di soluzioni (inutile)
*/
int perm_r(int pos, int *dist_val, int *sol,int *mark, int n, int n_dist, int cnt) {
    int i;
    if (pos >= n) { // condizione di terminazione
        for (i=0; i<n; i++)
            printf("%d ", sol[i]);
            printf("\n");
            return cnt+1;
        }
    for (i=0; i<n_dist; i++) {
        if (mark[i] > 0) {
            mark[i]--;// marca l'elemento come usato
            sol[pos] = dist_val[i];
            cnt=perm_r(pos+1,dist_val,sol,mark,n, n_dist,cnt);
            mark[i]++;// smarca l'elemento
        }
    }
    return cnt;
}
```

## Combinazioni semplici
S è un insieme di n elementi. Quante sono le combinazioni semplici di k elementi presi da S? non ci sono ripetizioni e l’ordine non conta.
Cs(n,k) = n! / (k! * (n-k)!)

(il coefficiente binomiale si può definire ricorsivamente)

Esempio:
Quanti e quali sono i gruppi di 3 persone che si possono formare con 5 persone?
S = {alberto, bruno, carlo, dario, enrico}
n = 5
k = 3
Cs(5,3) = 5! / (3! * 2!) = 10

## Combinazioni con ripetizioni
???

## Insime delle parti (Powerset)
Dato un insieme S, l’insieme delle parti di S è l’insieme di tutti i sottoinsiemi di S.

Esempio:
S = {a, b, c, d}
P(S) = {{}, {a}, {b}, {c}, {d}, {a,b}, {a,c}, {a,d}, {b,c}, {b,d}, {c,d}, {a,b,c}, {a,b,d}, {a,c,d}, {b,c,d}, {a,b,c,d}}

### Codice Dividi et Impera DA COMPLETARE!!!
### Codice Disposizioni ripetute
Ogni sottoinsieme è rappresentato dal vettore della soluzione sol di n elementi:
- l’insieme delle scelte possibili per ogni posizione del vettore è {0, 1}, quindi k = 2. Il ciclo for è sostituito da 2 assegnazioni esplicite
- `sol[pos]` = 0 se l’oggetto pos-esimo non appartiene al sottoinsieme
- `sol[pos]` = 1 se l’oggetto pos-esimo appartiene al sottoinsieme
- nella stessa soluzione 0 e 1 possono comparire più volte
È scambiato il ruolo di n e k rispetto alla definizione di disposizioni ripetute (dove n era il numero di scelte e k la dimensione della soluzione).
Nota: è l'equivalente ricorsivo di contare in binario da 0 a (2^n)-1, perch a ogni chiamata ricorsiva il bit viene settato a 0 o 1.
```c
int powerset(int pos,int *val,int *sol,int n,int cnt) {
    int j;
    if (pos >= n) { // terminazione: stampa soluzione
        printf("{ \t");
        for (j=0; j<n; j++)
            if (sol[j]!=0){ printf("%d \t", val[j]); }
        printf("} \n");
        return cnt+1;
    }
    sol[pos] = 0;
    cnt = powerset(pos+1, val, sol, n, cnt);
    sol[pos] = 1;
    cnt = powerset(pos+1, val, sol, n, cnt);
    return cnt;
}
```

### Codice combianzioni semplici
Si realizza l'insieme delle parti come unione di insieme vuoto e insieme delle parti degli insiemi con j = 1, 2, 3, ...., n elementi.
  `Powerset(S)= {} U Cs(n,1) U Cs(n,2) U ... U Cs(n,n)`
Trattandosi di insiemi l’ordine non conta. Un wrapper si occupa dell’unione dell’insieme vuoto (non generato dalle combinazioni) e dell’iterare la chiamata alla funzione ricorsiva delle combinazioni.

```c
// wrapper, si occupa dell unione dell'insieme vuoto
int powerset(int *val, int n, int *sol){
    int cnt = 0, j;
    printf("{ }\n");
    cnt++;
    for(j = 1; j <= n; j++){ cnt += powerset_r(val, n, sol, j, 0, 0); }
    return cnt;
}

int powerset_r(int* val, int n, int *sol, int j, int pos,int start){ int cnt = 0, i;
    if (pos >= j){ // caso terminale, si è raggiunto il numero di elementi da inserire
        printf("{ ");
        for (i = 0; i < j; i++)
            printf("%d ", sol[i]);
        printf(" }\n");
        return 1;
    }
    for (i = start; i < n; i++){
        sol[pos] = val[i];
        cnt += powerset_r(val, n, sol, j, pos+1, i+1);
    }
    return cnt;
}
```

## Partizioni di un insieme
Dato un insieme S, una partizione di S è un insieme di sottoinsiemi di S, tali che:
- l’unione di tutti i sottoinsiemi è S
- l’intersezione di due sottoinsiemi è vuota
- ogni sottoinsieme è non vuoto

Il numero complessivo delle partizioni di un insieme I di n oggetti in k blocchi con 1 ≤ k ≤ n è dato dai numeri di Bell definiti dalla seguente ricorrenza:
B(0) = 1
B(n+1) = ∑i=0..n (n i) B(i)

Ecco i primi numeri di Bell: 1 1 2 5 15 52



# Esplorazione esustiva dello spazio delle soluzioni
La scomposizione in sottoproblemi è il passo più importante del progetto di una soluzione ricorsiva: bisogna identificare il problema risolto dalla singola
ricorsione, cioè suddividere il lavoro tra varie chiamate ricorsive. Si opera in maniera distribuita, senza visione unitaria della soluzione.
Abbiamo due tipi di approcci:
- ogni ricorsione sceglie un elemento della soluzione. Terminazione: la soluzione ha raggiunto la dimensione richiesta oppure non ci sono più scelte
- la ricorsione esamina uno degli elementi dell’insieme di partenza per decidere se e dove andrà aggiunto alla soluzione. (???)

## Strutture dati per la soluzione
[24/10/23]
distinguiamo in globali, cioè visibili a ogni chiamata ricoorsiva (dati del problema (matrice, mappa, grafo), vincoli, scelte disponibili, soluzione), e locali, cioè locali a ciascuna delle istanze della ricorsione(indici di livello di chiamata ricorsiva, copie locali di strutture dati, indici o puntatori a parti di strutture dati globali).
Nota: struttura dati globale non vuol dire per forza che usiamo una variabile globale in c. usare una variabile globale è sconsigliato ma non vietato quando le funzioni ricorsive operano su pochi e ben noti dati. è vantaggioso in quanto pochi parametri sono passati alle funzioni ricorsive.

### Tipologie di strutture dati per oggetti interi
- Se ho oggetti non interi uso tabelle di simboli per ricondursi ad interi. Per esmpio se ho stringhe, posso associare ogni stringa a un intero
- Se ho un insieme o insiemi di oggetti di partenza uso vettori. un vettore se ho un insieme, più (raggruppati in vettore di vettori) se ho più insiemi.
Molto probabilmente avrò degli indici e dei vincoli. Vincoli statici (uguali in ogni ricorsione) o dinamici (cambiano a ogni ricorsione. per esempio quando scelgo palline da un sacco, ho il vincolo di non scegliere di nuovo la pallina gia scelta).

## Come realizzare il principio di moltiplicazione
Devo creare l'albero. Ho bisognio di un vettore che per ogni scelta mi dica il numero di scelte possibili. Per esempio se posso scegliere tra due primi, tre secondi e due antipasti, il vettore sarà [2,3,2]. Albero di grado 3 (massimo numero nel vettore) e altezza 3 (lunghezza del vettore), 12 percorsi radice-foglie.

## Principi base dell'esploarazione
- Si prendono n decisioni in sequenza, ciascuna tra diverse scelte , il cui numero è fisso dato il livello di decisione, ma variabile di livello in livello.
- le scelte sono in corrispondenza biunivoca con un sottoinsieme degli interi (non necessariamente contigui).
- le scelte possibili sono memorizzate in un vettore `val`  di dimensione n di strutture `Livello`. Ogni struttura Livello continere un intero `num_scelte` che rappresenta il numero di scelte possibili per quel livello, e un vettore `scelte` di dimensione `num_scelte` che contiene le scelte possibili per quel livello.
- la soluzione è memorizzata in un vettore di interi `sol` di dimensione n.

Esempio dell'antipasto di prima:
val = [
  Livello(2, [0,1]),
  Livello(3, [0,1,2]),
  Livello(2, [0,1])
]

Esempio più generale in c:

    typedef struct {int *scelte; int num_scelte; } Livello;
    val = malloc(n*sizeof(Livello));
    for (i=0; i<n; i++)
      // definisci val[i].num_scelte (con un input o un calcolo)
      val[i].scelte = malloc(val[i].n_scelte*sizeof(int));
    sol = malloc(n*sizeof(int));

    int princ_molt(int pos, Livello *val, int *sol,int n, int cnt) {
      int i;
      // condizione di terminazione
      if (pos >= n) {
        for (i = 0; i < n; i++)
          printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
      }
      // questo ciclo esplora tutte le scelte di questo livello
      for (i = 0; i < val[pos].num_scelte; i++) {
        // i vettori sol crescono con la ricorsione (e quando sono completi si stampano)
        sol[pos] = val[pos].scelte[i];
        cnt = princ_molt(pos+1, val, sol, n, cnt);
      }
    return cnt;
    }
