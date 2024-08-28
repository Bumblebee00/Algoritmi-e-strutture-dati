[26/08/2024]

- [Tabelle di hash](#tabelle-di-hash)
  - [Funzioni di hash](#funzioni-di-hash)
      - [Metodo moltiplicativo](#metodo-moltiplicativo)
      - [Metodo modulare](#metodo-modulare)
      - [Metodo moltiplicativo modulare](#metodo-moltiplicativo-modulare)
      - [???](#)
  - [Collisioni](#collisioni)
    - [Linear chaining](#linear-chaining)
      - [Complessità](#complessità)
    - [Open addressing](#open-addressing)
      - [Linear probing](#linear-probing)
        - [Insert](#insert)
        - [Search](#search)
        - [Delete](#delete)
      - [Quadratic probing](#quadratic-probing)
      - [Double hashing](#double-hashing)
  - [Confronto tra alberi e tabelle di hash](#confronto-tra-alberi-e-tabelle-di-hash)


# Tabelle di hash
Finora gli algoritmi di ricerca si erano basati sul confronto. Nelle tabelle di hash invece la chiave di ricerca viene trasformata in un indice della tabella. Usate per inserzione, ricerca, cancellazione, non per ordinamento e selezione.

```c
// ST.h
typedef struct symboltable *ST;

ST STinit (int maxN, float r) ;
void STinsert (ST st, Item val);
Item STsearch (ST st, Key k);
void STdelete (ST st, Key k);
void sTdisplay (ST st);
void STfree (ST st);
int STcount (ST st);
int STempty (ST st);
```

## Funzioni di hash
nelle tabelle di hash la chiave di ricerca $k \in U = \{ 0, 1, ..., card(U) - 1 \}$. La tabella è creata con un vettore di lunghezza $M$ con $M > card(U)$. La funzione di hash $h: U \rightarrow \{ 0, 1, ..., M-1 \}$ mappa la chiave in un indice della tabella. Esempi di funzioni di hash sono:

#### Metodo moltiplicativo
$h(k) = M * (k - s) / (t - s)$

dove k è un float appartenente all'intervallo [s, t], M è la dimensione della tabella.

#### Metodo modulare
$h(k) = k \mod M$

dove k è un intero. Meglio scegliere M come numero primo, se per esempio scegliessimo $M = 2^p$ la funzione di hash userebbe solo gli ultimi $p$ bit della chiave, se scegliessimo $M = 10^p$ la funzione di hash userebbe solo le ultime $p$ cifre decimali della chiave.

se la chiave è una stringa ci sono vari metodi per passare da stringhe a numeri interi:
- considerare la stringa come un numero in base 128 (ASCII)
- metodo di Horner: le lettere sono coefficenti di un polinomio (che viene poi calcolato per un certo valore di x con il metodo di horner), la chiave è il valore del polinomio

#### Metodo moltiplicativo modulare
$h(k) = (a * k) \mod M$

dove $a$ è un float appartenente all'intervallo [0, 1].

#### ???
```c
int hash (char *v, int M){
  int h = 0, base = 127; // numero primo per avere probabilità di collisione minore
  for (; *v != '\0'; v++)
    h = (base * h + *v) % M;
  return h;
}
```

```c
int hashU( char *v, int M) {
  int h, a = 31415, b = 27183;
  for ( h = 0; *v != '\0'; v++, a = a*b % (M-1))
    h = (a*h + *v) % M;
  return h;
}
```

## Collisioni
Le collisioni sono inevitabili, si possono risolvere in vari modi:
- concatenamento: ogni cella della tabella è una lista di elementi
- indirizzamento aperto: se la cella è occupata si cerca la prossima cella libera

### Linear chaining
Più elementi possono risiedere nella stessa locazione della tabella con una lista concatenata.
```c
// ST.c
#include "ST.h"

typedef struct STnode *link;

struct STnode { Item item; link next; };

// heads è un vettore di liste con nodo sentinella in coda
// z è un nodo sentinella
// N è il numero di elementi nella tabella
// M è la dimensione della tabella
struct symbtab { link *heads; int M, N; link z; };

static link NEW(Item item, link next) {
  link x = malloc(sizeof *x);
  x->item = item;
  x->next = next;
  return x;
}

// r è la lunghezza media delle liste desiderata
ST STinit (int maxN, float r) {
  int i;
  ST st;

  st = malloc(sizeof(*st));
  st->N = 0;
  st->M = STsizeset(maxN, r);
  st->heads = malloc(st->M*sizeof(link));
  st->z = NEW(ITEMSetNull(), NULL);
  
  for (i=0; i < st->M; i++)
    st-›heads[i] = st->z;
  
  return st;
}

static int STsizeSet(int maxN, float r) {
  int primes[16] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
  int i = 0;
  int size;
  size = maxN /r;
  if (size < primes[15]) {
    for (i = 0; i<16; i++)
      if (size <= primes[i])
        return primes[i];
  } else
  printf("Too many entries!\n"); return -1;
}

// vedi le altre a pag 27-30 delle slides
```

#### Complessità
Def(fattore di carico $\alpha$): $\alpha = N/M$

Ipotizzando:
- Liste non ordinate
- N elementi memorizzati in tabella di dimensione M
- Hashing semplice uniforme, cioè h ha egual probabilità di generare gli M valori di uscita

Ecco le varie operazioni con rispettive complessità:
- Inserimento: O(1)
- Ricerca: in media O(1 + $\alpha$), nel caso peggiore O(N)

### Open addressing
```c
// ST.c
struct symboltable { Item *a; int N; int M;};

ST STinit(int maxN, float alpha) {
    int i;
    ST st = malloc(sizeof(*st));
    st->N = 0;
    st->M = STsizeSet(maxN, alpha);

    st->a = malloc(st->M * sizeof(Item) );
    for (i = 0; i < st->M; i++)
        st->a[i] = ITEMsetNull();
    return st;
}
```

In caso di collisione si cerca una cella non ancora occupata mediante probing. Ci sono diversi tipi di probing:
- linear probing: si prova h(k), poi h(k)+1, h(k)+2, ...
- quadratic probing: si prova h(k), poi $[ h(k) + c_i*i + c_2*i^2 ] \% M$ con i da 1 in avanti
- double hashing: si hanno due funzioni di hash h1(k) e h2(k), si prova h1(k), poi $[ h1(k) + i*h2(k) ] \% M$ con i da 1 in avanti


#### Linear probing
##### Insert
calcola i = h(k), se libero inserisci chiave, altrimenti incrementa i di 1 modulo M, ripeti fino a trovare una cella vuota.
```c
void STinsert(ST st, Item item) {
    int i = hash(KEYget(&item), st->M);
    while (full(st, i))
        i = (i+1)%st->M;
    st->a[i] = item;
    st->N++;
}
int full(ST st, int i) {
    if (ITEMcheckNull(st->a[i]))
        return 0;
    return 1;
}
```

##### Search
calcola i = h(k), se trovata chiave, termina con successo, altrimenti incrementa i di 1 modulo M o ripeti fino a cella vuota (insuccesso).
```c
// cerca la chiave k nella tabella st e restituisce l’item corrispondente se presente
Item STsearch(ST st, Key k) {
    int i = hash(k, st->M);
    while (full(st, i)) {
        if (KEYeq(k, KEYget(&st->a[i])))
            return st->a[i];
        i = (i+1)%st->M;
    }
    return ITEMsetNull();
}
```

##### Delete
è un operazione difficile perchè intrerrompe la catena di collisioni, infatti l'open addressing non è adatto per cancellazioni. Ci sono due metodi:
- cancellazione fisica: si cancella l'elemento e si inserisce un elemento sentinella che conta piena in ricerca e vuota in inserzione
Nell’ADT si introduce un vettore status di interi: 0 se la cella è vuota, 1 se è occupata, -1 se cancellata.
La funzione CheckFull controlla se la cella i è piena (status=1). La funzione CheckDeleted controlla se la cella è cancellata (status=-1).
```c
struct symboltable { Item *a; int *status; int N; int M;};
static int CheckFull(ST st, int i);
static int CheckDeleted(ST st, int i);
```

- reinserire le chiavi del cluster sottostante la chiave cancellata

```c
void STdelete(ST st, Key k) {
    int j, i = hash(k, st->M);
    Item tmp;
    while (full(st, i)){
        if (KEYcmp(k, KEYget(&st->a[i]))==0)
            break;
        else
            i = (i+1) % st->M;
    }
    if (ITEMcheckNull(st->a[i]))
        return;
    st->a[i] = ITEMsetNull();
    st->N--;
    for (j = i+1; full(st, j); j = (j+1)%st->M, st->N--) {
        tmp = st->a[j];
        st->a[j] = ITEMsetNull();
        STinsert(st, tmp);
    }
}
```

#### Quadratic probing
```c
#define c1 1
#define c2 1

void STinsert(ST st, Item item) {
    int i = 0, start = hash(KEYget(&item), st->M), index=start;
    while (full(st, index)) {
        i++;
        index = (start + c1*i + c2*i*i)%st->M;
    }
    st->a[index] = item;
    st->N++;
}
```

se M = 2^K, scegliere c1 = c2 = 1⁄2 per garantire che siano generati tutti gli indici tra 0 e M-1.

se M è primo, e se $\alpha$ < 1⁄2 i seguenti valori
- c1 = c2 = 1⁄2
- c1 = c2 = 1
- c1 = 0, c2 = 1
garantiscono che, con inizialmente start = h(k) e poi index = (start + c1i + c2i2) modulo M (come nel codice) si abbiano valori distinti per 1 < i < (M-1)/2.

#### Double hashing
```c
void STinsert(ST st, Item item) {
    int i = hash1(KEYget(&item), st->M);
    int j = hash2(KEYget(&item), st->M);

    while (full(st, i))
        i = (i+j)%st->M;
    
    st->a[i] = item;
    st->N++;
}
```

per evitare che i sia uguale a i dell'iter. prec. e si entri in un ciclo infinito, si deve avere che $h2(k) \neq 0$ e $h2(k) \neq M$. Esempio di h2: $h2(k) = 1 + k \mod (97)$.

## Confronto tra alberi e tabelle di hash
Tabelle di hash:
- più facili da realizzare
- unica soluzione per chiavi senza relazione d’ordine
- più veloci per chiavi semplici
Alberi (BST e loro varianti):
- meglio garantite le prestazioni (per alberi bilanciati)
- permettono operazioni su insiemi con relazione d’ordine