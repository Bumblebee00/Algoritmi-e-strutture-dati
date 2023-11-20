[20/11/23] In questa lezione abbiamo parlato di cosa sono i tipi di dati astratti e come potremmo implementarli.
Indice completo del file markdown:
- [Tipi di dati astratti](#tipi-di-dati-astratti)
  - [Tipo di dati standard](#tipo-di-dati-standard)
  - [Tipo di dati definiti dall'utente](#tipo-di-dati-definiti-dallutente)
  - [Quasi ADT](#quasi-adt)
    - [Esemio: quasi ADT per numeri complessi](#esemio-quasi-adt-per-numeri-complessi)
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
Nota: a volte può avere senso non dare neanche un nome alla lista: nel caso in cui ce ne sia solo una si fa variabile globale il primo nodo e via

## Set