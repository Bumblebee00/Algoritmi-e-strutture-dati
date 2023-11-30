[29/11/23]

# Tabelle di simboli
Sono simili alle code generalizzate ma un po strane
Definizione: ADT che supporta operazioni di:
- insert: inserisci un dato (item) (STinsert)
- delete: cancella il dato con una certa chiave (STdelete).
- search: ricerca dato con certa chiave (STsearch). Qui sta la sostanziale differenza dalle altre code. Non priorità non cronoliogia, ma chiave.

E detta dizionario
Altre operazioni:
- inizializzare la tabella
- distruggere la tabella
- contare il numero di dati
- visualizzare della tabella
- se sulla chiave è definita una relazione d’ordine:
  - ordinare la tabella
  - selezionare la chiave di rango r (r-esima più piccola chiave)


| Applicazione | scopo | chiave | valore ritornato |
| --- | --- | --- | --- |
| dizionario | la definizione | parola | definizione |
| indice libro | pagine rilevanti | termine | lista pagine |
| DNS | indirizzo IP dato URL | URL | IP address |
| DNS inverso | URL dato indirizzo IP | IP address | URL |
| file system | file su disco | nome file | localizzazione disco |
| web search | pagine web | parola chiave | lista di pagine |

Per semplicità gestiremo chiavi quasi ADT con nome e chiave. La tabella invece sarà un ADT di prima classe
```c
// ST.h
typedef struct symboltable *ST;

ST STinit(int maxN);
void STfree(ST st);
int STcount(ST st);
void STinsert(ST st, Item val);
Item STsearch(ST st, Key k);
void STdelete(ST st, Key k);
Item STselect(ST st, int r);
void STdisplay(ST st);
```

## Varie implementazioni
Possibili versioni dell’ADT tabella di simboli
- tabelle ad accesso diretto (versione più becera e stupida della tabella di simboli)
- strutture lineari (vettore/lista ordinato/non ordinato)
In seguito tratteremo anche:
- strutture ad albero
- alberi binari di ricerca (BST) e loro varianti
- tabelle di hash.

### Complessità del caso peggiore
| Implementazioni | Inserimento | Ricerca | Selezione |
| --- | --- | --- | --- |
| Tabelle ad accesso diretto | 1 | 1 | maxN |
| Array non ordinato | 1 | n | non possibile |
| Array ordinato e ricerca lineare | n | n | 1 |
| Array ordinato e ricerca binaria | n | logn | 1 |
| Lista non ordinata | 1 | n | non possibile |
| Lista ordinata | n | n | n |
| BST | n | n | n |
| RB-tree | logn | logn | logn |
| Hashing | 1 | 1 | non possibile |

### Complessità del caso medio
| Implementazioni | Inserimento | Ricerca | Selezione |
| --- | --- | --- | --- |
| Tabelle ad accesso diretto | 1 | 1 | maxN |
| Array non ordinato | 1 | n/2 | non possibile |
| Array ordinato e ricerca lineare | n/2 | n/2 | n/2 |
| Array ordinato e ricerca binaria | n/2 | logn | logn |
| Lista non ordinata | 1 | n/2 | non possibile |
| Lista ordinata | n/2 | n/2 | n/2 |
| BST | logn | logn | logn |
| RB-tree | logn | logn | logn |
| Hashing | 1 | 1 | non possibile |


## Tabelle ad accesso diretto
Definiamo l'insieme universo U con tutte le chiavi, e M = cardinalità(U) = maxN elementi
Assumiamo una corrispondenza biunivoca tra ciascuna delle chiavi k in U e gli interi tra 0 e M-1 (funzione int GETindex(Key k)). L’intero funge da indice in un vettore
- vettore st->a[] di dimensione maxN:
- se la chiave k è nella tabella, essa è in posizione st->a[GETindex(k)], altrimenti st->a[GETindex(k)] contiene l’elemento vuoto
- si memorizza un insieme di N chiavi (N ≤ M). La cardinalità è N ritornata dalla funzione st->size.

### Esempi di GEt Index
Se le chiavi sono le lettere maiuscole dell’alfabeto inglese A..Z (M = 26)
```c
int GETindex(Key k) {
  int i;
  i = k - 'A';
  return i;
}
```
Se le chiavi sono stringhe di lunghezza l fissa e corta, ogni lettera è un valore intero tra 0 e 25, e la chiave è la somma di tutte queste lettere
```c
int GETindex(Key k) {
  int i = 0, b = 26;
  for ( ; *k != '\0'; k++)
    i = (b * i + (*k - ((int) 'A')));
  return i;
}
```

### Implementazione
```c
struct symbtab {Item *a; int N; int M;};

ST STinit(int maxN) {
  ST st; int i;
  st = malloc(sizeof(*st));
  st->a = malloc(maxN * sizeof(Item) );
  
  for (i = 0; i < maxN; i++) st->a[i] = ITEMsetvoid();
    st->M = maxN; st->N= 0; return st;
}

int STcount(ST st) {
  return st->N;
}

void STfree(ST st) {
  free(st->a);
  free(st);
}

void STinsert(ST st, Item val) {
  int index = GETindex(KEYget(val));
  st->a[index] = val;
  st->N++;
}

Item STsearch(ST st, Key k) {
  int index = GETindex(k);
  return st->a[index];
}

void STdelete(ST st, Key k) {
  st->a[GETindex(k)] = ITEMsetvoid();
  st->N--;
}

// assume che l'ordinamento degli indici sia lo stesso delle chaivi
Item STselect(ST st, int r) {
  int i;
  // per tutta la tabella conta gli item non vuoti
  for (i = 0; i < st->M; i++)
    if ((ITEMcheckvoid(st->a[i])==0) && (r-- == 0))
      return st->a[i];
  return NULL;
}
void STdisplay(ST st){
  int i;
  for (i = 0; i < st->M; i++)
     if (ITEMcheckvoid(st->a[i])==0)
       ITEMstore(st->a[i]);
}
```

### Vantaggi e svantaggi
- Complessità delle operazioni di inserimento, ricerca e cancellazione: O(1)
- Complessità delle operazioni di inizializzazione e selezione: O(M)
- Occupazione di memoria proporzionale a M
- applicabile per M piccolo
- spreco di memoria per N << M
- Molto usate in pratica per trasformare chiavi in interi e viceversa a costo unitario.

## Tabella di simboli con vettori
ADT di I classe

```c
struct symbtab {Item *a; int maxN; int size;};

ST STinit(int maxN) {
  ST st; int i;
  st = malloc(sizeof(*st));
  st->a = malloc(maxN * sizeof(Item) );
  for (i = 0; i < maxN; i++)
    st->a[i] = ITEMsetvoid();
  st->maxN = maxN;
  st->size = 0;
  return st;
}

int STcount(ST st) { return st->size; }

void STfree(ST st) { free(st->a); free(st); }

// come prima ma non discrimina tra chiavi vuote e non
void STdisplay(ST st){ int i;
  for (i = 0; i < st->size; i++)
    ITEMstore(st->a[i]);
}

void STdelete(ST st, Key k) {
  int i, j=0;
  while (KEYcmp(KEYget(&st->a[j]), k)!=0)
      j++;
  for (i = j; i < st->size-1; i++)
    st->a[i] = st->a[i+1];
  st->size--;
}
```

vedi slides

### Vanataggi e svantaggi vettore non ordinato
- Complessità delle operazioni di inserimento, ricerca e cancellazione: O(N)
- Complessità delle operazioni di inizializzazione e selezione: O(1)
- Occupazione di memoria proporzionale a N

### Vanataggi e svantaggi vettore ordinato
- Complessità delle operazioni di inserimento, ricerca e cancellazione: O(N)
- Si può implementare ricerca dicotomica con complessità O(logN)
- Complessità delle operazioni di inizializzazione e selezione: O(1)
- Occupazione di memoria proporzionale a N

## Tabella di simboli con liste
Ricerca preliminare alla cancellazione sempre lineare O(N)
Lista non ordinata:
- inserzione in testa per avere complessità O(1)
- la selezione non ha senso
Lista ordinata:
- inserzione con scansione con complessità O(N)

### Implementazione
vedi slides pag 128

### Vanataggi e svantaggi lista non ordinata
- Complessità delle operazioni di inserimento, ricerca e cancellazione: O(N)
- Complessità delle operazioni di inizializzazione e selezione: O(1)
- Occupazione di memoria proporzionale a N (non M)

## Gestione duplicati nelle tabelle di simboli
Si può ignorare il nuovo elemento, o dimenticare il vecchio