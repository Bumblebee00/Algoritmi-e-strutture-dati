[20/11/23] In questa lezione abbiamo parlato di cosa sono i tipi di dati astratti e come potremmo implementarli.

- [Tipo di dato astratto](#tipo-di-dato-astratto)
    - [Tipo di dati standard](#tipo-di-dati-standard)
    - [Tipo di dati definiti dall'utente](#tipo-di-dati-definiti-dallutente)
  - [Quasi ADT](#quasi-adt)
    - [Esempio: quasi ADT per numeri complessi](#esempio-quasi-adt-per-numeri-complessi)
    - [Tipo 1](#tipo-1)
    - [Tipo 2](#tipo-2)
    - [Tipo 3](#tipo-3)
    - [Tipo 4](#tipo-4)
    - [Funzioni di interfaccia di Item](#funzioni-di-interfaccia-di-item)
      - [Header](#header)
      - [Implementazione](#implementazione)
        - [Tipo 1](#tipo-1-1)
        - [Tipo 2](#tipo-2-1)
        - [Tipo 3](#tipo-3-1)
        - [Tipo 4](#tipo-4-1)
  - [ADT di I classe](#adt-di-i-classe)
    - [Esempio: ADT di I classe per numeri complessi](#esempio-adt-di-i-classe-per-numeri-complessi)
    - [Header](#header-1)
    - [Implementazione](#implementazione-1)
- [Usare ADT per collezioni](#usare-adt-per-collezioni)
  - [Lista non ordinata](#lista-non-ordinata)
  - [Set](#set)
    - [Implementazione con vettore ordinato](#implementazione-con-vettore-ordinato)
    - [Implementazione con lista ordinata](#implementazione-con-lista-ordinata)


# Tipo di dato astratto
astrastto: nasconde l'informazione in un livello inferiore. Sono utili perchènon si vuole che il client abbia accesso ai dettagli dell'implementazione.

### Tipo di dati standard
Tipi scalari (numeri e caratteri):
- int (signed, unsigned, long, short) o float (double, long double)
- char
Tipi strutturati (composti/aggregati)
- array (vettori/matrici: campi omogenei)
- struct (campi eterogenei)

### Tipo di dati definiti dall'utente
Valori:
- typedef permette di introdurre un nuovo nome per un tipo (da ricondurre a un tipo base, scalare o composto aggregato)
Operazioni
- una funzione permette di definire una nuova operazione su argomenti e/o dato ritornato.

Il C non ha un meccanismo semplice ed automatico di creazione di ADT. L’ADT è realizzato come modulo con una coppia di file interfaccia/implementazione. Enfasi su come nascondere i dettagli dell’implementazione al client.

## Quasi ADT
Interfaccia
- definizione del nuovo tipo con typedef
- raramente si appoggia su tipi base, in generale è un tipo composto, aggregato o contenitore (struct wrapper)
- Prototipi delle funzioni

Implementazione
- Il client include il file header, quindi vede i dettagli interni del dato e/o del wrapper

### Esempio: quasi ADT per numeri complessi
- nuovo tipo Complex
- struct con campi per parte reale e coefficiente dell’immaginario
-  funzione di prodotto tra 2 numeri complessi.
Il client che include complex.h vede i dettagli della struct (ma non li usa)

```c
// complex.h
typedef struct {
    double re; double im;
} Complex;

Complex prodotto(Complex a, Complex b);
```

```c
// complex.c
#include "complex.h"
Complex prodotto(Complex a, Complex b) {
    Complex c;
    c.re = a.re * b.re - a.im * b.im;
    c.im = a.re * b.im + a.im * b.re;
    return c;
}
```

```c
// main.c
#include <stdio.h>
#include "complex.h"
int main() {
    Complex a = {1, 2}, b = {3, 4}, c;
    c = prodotto(a, b);
    printf("%f %f\n", c.re, c.im);
    return 0;
}
```
NOTA: questo è un quasi ADT perchè il main può vedere il campo .re e .im\
il problema potrebbe essere che il main chiama .re, poi l'implementazione della libraria cambia, e il codice non compila più.

Ora per una cosa così semplici come i numeri complessi, è un po' troppo complicato. Ma per tipi di dati più complessi, come ad esempio una lista, è molto utile.

### Tipo 1
Il più semplice: non c'è la struct. Nessun problema di proprietà, in quanto non c’è allocazione dinamica.
```c
typedef int Item;
typedef int Key;
```

### Tipo 2
Stringa: item e chiave sono i puntatori al primo carattere della stringa.
```c
typedef char *Item;
typedef char *Key;
```

### Tipo 3
struct con tutto dentro
```c
typedef struct item {
    char name[MAXC];
    int num;
} Item;
typedef char *Key;
```
### Tipo 4
composto per riferimento: struct con puntatori. probabilmente richiede allocazione dinamica.
```c
typedef struct item {
    char *name;
    int num;
} Item;
typedef char *Key;
```

### Funzioni di interfaccia di Item
#### Header
```c
/* definizione di Item e Key */
int KEYcompare(Key k1, Key k2);
Key KEYscan();
Item ITEMscan();
void ITEMshow(Item val);
int ITEMless(Item val1, Item val2);
int ITEMgreater(Item val1, Item val2);
int ITEMcheckvoid(Item val);
Item ITEMsetvoid();
```
e per `KEYget()` ? cosa si passa come parametro? be se la chiave è un puntatore alla struct o a qualcosa dentro la struct, non possiamo passare la struct come parametro. perchè se lo passiamo come parametro la funzione se ne fa una copia interna, e non ha il puntatore a nulla di utile ( perchè la copia interna viene eliminata quano la funzione returna). quindi in questo caso dobbiamo passare il puntatore alla struct come parametro.
```c
Key KEYget(Item *pval);
```

#### Implementazione
##### Tipo 1
semplice intero
```c
Key KEYget(Item val) { return (val); }
int KEYcompare (Key k1, Key k2){ return (k1-k2); }
Item ITEMscan() {
    Item val;
    scanf("%d", &val);
    return val;
}
void ITEMshow(Item v) {
  printf("%d", val);
}
int ITEMless(Item val1, Item val2) {
    return (KEYget(val1)<KEYget(val2));
}
```

##### Tipo 2
stringa
```c
static char buf[MAXC]; // NOTA: essendo questa non definta in un header, è statica, e quindi non è visibile al client. qundi altri file (compreso il client) possono avere una variabile buf, senza problemi
Key KEYget(Item val) { return (val); }
int KEYcompare (Key k1, Key k2) {
    return (strcmp(k1,k2));
}
Item ITEMscan() {
    scanf("%s",buf); return strdup(buf);
}
void ITEMshow(Item val) { printf("%s", val); }
int ITEMless(Item val1, Item val2) {
    return (strcmp(KEYget(val1),KEYget(val2))<0);
}
```

##### Tipo 3
struct con stringa tutta dentro
```c
Key KEYget(Item *pval) { return (pval->name); }
int KEYcompare (Key k1, Key k2) { return (strcmp(k1,k2)); }

Item ITEMscan() {
    Item val;
    scanf("%s %d", val.name, &(val.num));
    return val;
}
void ITEMshow(Item val) {
    printf("%s %d", val.name, val.num);
}
int ITEMless(Item val1, Item val2) {
    return (strcmp(KEYget(&val1),KEYget(&val2))<0);
}
```

##### Tipo 4
struct con puntatori
```c
static char buf[MAXC];

Key KEYget(Item *pval) { return (pval->name); }
int KEYcompare (Key k1, Key k2) { return (strcmp(k1,k2)); }

Item ITEMscan() {
    Item val;
    scanf("%s %d", buf, &(val.num));
    val.name = strdup(buf);
    return val;
}

void ITEMshow(Item val) {
    printf("%s %d", val.name, val.num);
}

int ITEMless(Item val1, Item val2) {
    return (strcmp(KEYget(&val1),KEYget(&val2))<0);
}
```
Il tipo 4 (struttura mista) presenta un probelma: chi dealloca?


## ADT di I classe
Per impedire al client di vedere i dettagli della struct:
- il tipo di dato viene dichiarato nel file .h di interfaccia come struttura incompleta, o come puntatore a struct incompleta, non viene quindi definita la struct composto, aggregato o wrapper
- la struct viene invece completamente definita nel file .c
- il client utilizza unicamente puntatori alla struttura incompleta
- Il puntatore è opaco e si dice handle.



### Esempio: ADT di I classe per numeri complessi
Il client che include complex.h NON vede i dettagli della struct.
complex.h ha introdotto un nuovo tipo di dato Complex, che è un puntatore a struct incompleta.
poi complex.c definisce la struct e le funzioni.
```c
// complex.h
typedef struct complex_s *Complex;
Complex crea(void);
void distruggi(Complex c);
Complex prod(Complex c1, Complex c2);
```

```c
// complex.c
#include "complex.h"
struct complex_s { float Re; float Im; };

Complex crea(void) {
    Complex c = malloc(sizeof *c);
    return c;
}

void distruggi(Complex c) { free(c); }

Complex prod(Complex c1, Complex c2) {
    Complex c = crea();
    c->Re = c1->Re * c2->Re - c1->Im * c2->Im;
    c->Im = c1->Re * c2->Im + c2->Re * c1->Im;
    return c;
}
```

```c
// main.c
#include "complex.h"
int main (void) {
    Complex a, b, c;
    a = crea();
    b = crea();
    ...
    c = prod(a,b);
    ...
    distruggi(a);
    distruggi(b);
    distruggi(c);
}
```

### Header
```c
typedef struct item *Item;
typedef char *Key;
```
funzioni di interfaccia dipendenti da item
```c
Key KEYget(Item val);
Key KEYscan();
int KEYcompare(Key k1, Key k2);
Item ITEMnew();
void ITEMfree(Item val);
Item ITEMscan();
void ITEMshow(Item val);
int ITEMless(Item val1, Item val2); int ITEMgreater(Item val1, Item val2); int ITEMcheckvoid(Item val);
Item ITEMsetvoid();
```
### Implementazione
```c
// per i tipo 3
struct item {
    char name[MAXC];
    int num;
};
```
```c
// per il tipo 4
char buf[MAXC];
struct item {
    char *name;
    int num;
};
```
`KEYget`, `KEYcompare`, `ITEMless` e `ITEMshow` sono come nel quasi adt.
```c
// caso 3
Item ITEMnew(void) {
    Item val=(Item)malloc(sizeof(struct item));
    if (val==NULL)
        return ITEMsetvoid();
    val->name[0] = '\0';
    val->num = 0;
    return val;
}
void ITEMfree(Item val) {
    free(val);
}
```
```c
// caso 4
Item ITEMnew(void) {
    Item val=(Item)malloc(sizeof(struct item));
    if (val==NULL)
        return ITEMsetvoid();
    val->name = NULL;
    val->num = 0;
    return val;
}
void ITEMfree(Item val) {
    if (val->name!=NULL) free(val->name);
    free(val);
}
```
Item scan invece... boh


# Usare ADT per collezioni
Usiamo adt per generare code generalizzate / tabelle
## Lista non ordinata
```c
// list.h
typedef struct list* LIST;
void listInsHead (LIST l, Item val);
Item listSearch(LIST l, Key k);
void listDelKey(LIST l, Key k);
```
```c
// list.c
typedef struct node* link;
struct node { Item val; link next; };
struct list { link head; int N; };
void LISTinsHead (LIST l, Item val) {
    l->head = newNode(val,l->head);
    l->N++;
}
// implementazione delle altre funzioni
```
E utile perchè permete al client di creare più di un dato.\
Nota: a volte può avere senso non dare neanche un nome alla lista: nel caso in cui ce ne sia solo una si fa variabile globale il primo nodo e via

## Set
collezione di dati non ordinata senza duplicati, in cui sono disponibili le operazioni di unione, intersezione.
```c
// set.h
typedef struct set *SET;
SET SETinit(int maxN);
void SETfree(SET s);
void SETfill(SET s, Item val);
int SETsearch(SET s, Key k);
SET SETunion(SET s1, SET s2);
SET SETintersection(SET s1, SET s2); int SETsize(SET s);
int SETempty(SET s);
void SETdisplay(SET s);
```
L'insieme lo possiamo implementare con vettori ordinati, non ordinati o con liste ordinate o non ordinate. Con le liste la dimensione può crescere all'infinito, con i vettori no. La funzione `SETsearch` ha complessità O(n) per le liste (ord o non) e i vettori non ordinati O(log n) per i vettori ordinati (si può implementare la ricerca dicotomica). Le funzioni `SETunion` e `SETintersection` hanno complessità O(n) per le liste ordinate e i vettori ordinati, O(n^2) per le liste non ordinate e i vettori non ordinati.

### Implementazione con vettore ordinato
```c
// set.c
struct set { Item *v; int N; }; // dove N è il numero di elementi contenuti

// wrapper
SET SETinit(int maxN) {
    SET s = malloc(sizeof *s);
    s->v = malloc(maxN*sizeof(Item));
    s->N=0;
    return s;
}

void SETfree(SET s) {
    free(s->v);
    free(s);
}

// ricerca dicotomica
int SETsearch(SET s, Key k) {
    int l = 0, m, r = s->N -1;
    while (l <= r) {
        m = l + (r-l)/2;
        if (KEYeq(key(s->v[m]), k))
            return 1;
        if (KEYless(key(s->v[m]), k))
            l = m+1;
        else
            r = m-1;
    }
    return 0;
}

SET SETunion(SET s1, SET s2) {
    int i=0, j=0, k=0, size1=SETsize(s1);
    int size2=SETsize(s2);
    SET s;
    s = SETinit(size1+size2); // size init sovradimensionata, per essere pronti per il caso peggiore
    // simile al merge di merge sort
    for(k = 0; (i < size1) || (j < size2); k++){
        if (i >= size1) s->v[k] = s2->v[j++];
        else if (j >= size2) s->v[k] = s1->v[i++];
        else if (ITEMless(s1->v[i], s2->v[j]))
            s->v[k] = s1->v[i++];
        else if (ITEMless(s2->v[j], s1->v[i]))
            s->v[k] = s2->v[j++];
        else { s->v[k] = s1->v[i++]; j++; }
    }
    s->N = k;
    return s;
}

SET SETintersection(SET s1, SET s2) {
    int i=0, j=0, k=0, size1=SETsize(s1);
    int size2=SETsize(s2), minsize; SET s;
    minsize = min(size1, size2); // size init sovradimensionata, per essere pronti per il caso peggiore
    s = SETinit(minsize);
    while ((i < size1) && (j < size2)) {
        if (ITEMeq(s1->v[i], s2->v[j])) {
            s->v[k++] = s1->v[i++]; j++;
        }
        else if (ITEMless(s1->v[i], s2->v[j])) i++;
        else j++;
    }
    s->N = k;
    return s;
}
```

### Implementazione con lista ordinata
```c
typedef struct SETnode *link;

struct set { link head; int N; };
struct setNode { Item val; link next; };

SET SETinit(int maxN) {
    SET s = malloc(sizeof *s); s->head = NULL;
    s->N = 0;
    return s;
}
void SETfree(SET s) {
    link x, t;
    for (x=s->head; x!=NULL; x=t) {
    t = x->next; free(x); }
    free(s);
}

// ricerca lineare
int SETsearch(SET s, Key k) {
    link x;
    x = s->head;
    while (x != NULL) {
        if (KEYeq(key(x->val), k)) return 1;
    x = x->next;
    }
    return 0;
}

// O(nxm) dove n e m sono le dimensioni dei due insiemi
SET SETunion(SET s1, SET s2) {
    link x1, x2; int founds2, counts2=0;
    SET s = SETinit(s1->N + s2->N); // size init sovradimensionata
    
    // inseriamo nella soluzione tutti gli elementi di s1
    x1 = s1->head;
    while (x1 != NULL) { SETfill(s, x1->val); x1 = x1->next;}
    
    // poi aggiungiamo gli elementi di s2 che non sono in s1
    for (x2 = s2->head; x2 != NULL; x2 = x2->next) {
        x1 = s1->head;
        founds2 = 0;
        while (x1 != NULL) {
            if (ITEMeq(x1->val, x2->val)) founds2 = 1;
            x1 = x1->next;
        }
        if (founds2 == 0) { SETfill(s, x2->val); counts2++; }
    }
    s->N = s1->N + counts2;
    return s;
}

SET SETintersection(SET s1, SET s2) { link x1, x2; int counts=0; SET s; s = SETinit(s1->N + s2->N);
    x1 = s1->head;
    while (x1 != NULL) {
        x2 = s2->head;
        while (x2 != NULL) {
            if (ITEMeq(x1->val, x2->val)) { SETfill(s, x1->val); counts++; break;}
        x2 = x2->next;
        }
        x1 = x1->next;
    }
    s->N = counts;
    return s;
}

