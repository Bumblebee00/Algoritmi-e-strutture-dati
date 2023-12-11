[23/11/2023] Indice completo del file markdown:

- [Code Generalizzate](#code-generalizzate)
  - [Stack](#stack)
    - [Implementazione con vettore quasi ADT](#implementazione-con-vettore-quasi-adt)
    - [Implementazione con vettore ADT di 1° calsse](#implementazione-con-vettore-adt-di-1-calsse)
    - [Implementazione con lista quasi ADT](#implementazione-con-lista-quasi-adt)
    - [Implementazione con lista ADT di 1° classe](#implementazione-con-lista-adt-di-1-classe)
  - [Queue](#queue)
    - [Implementazione con vettore O(n)](#implementazione-con-vettore-on)
    - [Implementazione con vettore O(1) (bufer circolare)](#implementazione-con-vettore-o1-bufer-circolare)
    - [Strategie per riconoscere la coda vuota](#strategie-per-riconoscere-la-coda-vuota)
  - [Queue di priorità](#queue-di-priorità)
    - [Complessità:](#complessità)
    - [Implementazione con lista ordinata](#implementazione-con-lista-ordinata)
  - [Gestione dulicati nelle pile e code](#gestione-dulicati-nelle-pile-e-code)


# Code Generalizzate
sono dei contenitori con operazioni di `insert` `search` e `delete`. La funzione delete può eliminare in base a 
- crterio cronologico (stack/pila se cancella il più recente o queue/coda se cancella il più vecchio)
- criterio di priorità, quindi in base al valore di una chiave
- contenuto, quindi in base al valore di un elemento (tabelle di simboli)

i casi speciali (inserire in coda piena o estrarre da coda vuota) sono gestiti con eccezioni, ma non li trattiamo in questa lezione perchè siamo chad.

## Stack
ADT di pila. supporta operazioni di `STACKpush` (inserimento in cima), `STACKpop` (preleva e cancella dalla cima). è detto LIFO (last in first out) perchè l'ultimo elemento inserito è il primo ad essere estratto. Lo possiamo implementare con un array o con una lista concatenata. L'implementazione con vettore viene utilizzata quando lo stack è quasi sempre pieno, quella con la lista invece quando lo stack cambia rapidamente dimensione. In ogni caso la complessità di `STACKpush` e `STACKpop` è O(1).

### Implementazione con vettore quasi ADT
```c
// stack.h
void STACKinit(int maxN);
int STACKempty();
void STACKpush(Item val);
Item STACKpop();
```
```c
// stack.c
static Item *s;  // il fatto che sia una variabile globale, vuol dire che il main può generare solo uno stack, non più di uno.
static int N;

void STACKinit(int maxN) {
    s = malloc(maxN*sizeof(Item));
    N=0;
}

int STACKempty() { return N == 0; }

void STACKpush(Item val) { s[N++] = val; }

Item STACKpop() { return s[--N]; }
```
### Implementazione con vettore ADT di 1° calsse
```c
// stack.h
typedef struct stack *STACK;
STACK STACKinit(int maxN);
int STACKempty(STACK s);
void STACKpush(STACK s, Item val);
Item STACKpop (STACK s);
```
```c
// stack.c
struct stack { Item *s; int N; };

STACK STACKinit(int maxN) {
    STACK sp = malloc(sizeof *sp);
    sp->s = malloc(maxN*sizeof(Item));
    sp->N=0;
    return sp;
}

int STACKempty(STACK sp) { return sp->N == 0; }

void STACKpush(STACK s, Item val) {
    sp->s[sp->N++] = val;
}

Item STACKpop(STACK s) { return sp->s[--(sp->N)]; }
```
### Implementazione con lista quasi ADT
Push si implementa con inserzione in testa, e pop come estrazione in testa
```c
// stack.h
typedef struct stack *STACK;
STACK STACKinit(int maxN);
int STACKempty();
void STACKpush(Item val);
Item STACKpop ();
```
```c
// stack.c
typedef struct STACKnode* link;
struct STACKnode {Item val; link next;};

static link head;


static link NEW (Item val, link next){
    link x = (link) malloc(sizeof *x);
    x->val = val;
    x->next = next;
    return x;
}

void STACKinit(int maxN) { head = NULL; }

int STACKempty() {return head == NULL; }

void STACKpush(Item val) { head = NEW(val, head); }

Item STACKpop() {
    Item tmp;
    tmp = head->val;
    link t = head->next;
    free(head);
    head = t;
    return tmp;
}
```

### Implementazione con lista ADT di 1° classe
```c
// stack.h
typedef struct stack *STACK;
STACK STACKinit(int maxN);
int STACKempty(STACK s);
void STACKpush(STACK s, Item val);
Item STACKpop (STACK s);
```
```c
// stack.c
typedef struct STACKnode* link;
struct STACKnode {Item val; link next;};

struct stack { link head; };

static link NEW (Item val, link next){
    link x = (link) malloc(sizeof *x);
    x->val = val;
    x->next = next;
    return x;
}

STACK STACKinit(int maxN) {
    STACK s = malloc(sizeof *s);
    s->head = NULL;
    return s;
}

int STACKempty(STACK s) { return s->head == NULL; }

void STACKpush(STACK s, Item val) { s->head = NEW(val, s->head); }

Item STACKpop (STACK s) {
    Item tmp;
    tmp = s->head->val;
    link t = s->head->next;
    free(s->head);
    s->head = t;
    return tmp;
}
```

## Queue
ADT di coda. supporta operazioni di `enqueue` (inserimento in coda), `dequeue` (preleva e cancella dalla testa). è detto FIFO (first in first out) perchè il primo elemento inserito è il primo ad essere estratto. Lo possiamo implementare con un array o con una lista concatenata.
I vantaggi di vettore e lista sono gli stessi di stack, anche in questo caso la complessità di `enqueue` e `dequeue` è O(1).

Per tutte implementazioni serve un head e un tail. Nel caso div ettore saranno indici, nel caso della lista saranno puntatori.

### Implementazione con vettore O(n)
`put` assegna alla prima cella libera, se esiste, in fondo al vettore con complessità O(1). L’indice tail contiene il numero di elementi nella coda. `get` da posizione fissa (head = 0), ma comporta scalare a sinistra tutti gli elementi restanti con costo O(n)

### Implementazione con vettore O(1) (bufer circolare)
`put` assegna alla prima cella libera, se esiste, in posizione indicata da indice tail.\
`get` da posizione variabile (head assume valori tra 0 e N-1). Le celle del vettore occupate da elementi si spostano per via di put e get (buffer circolare) (head e tail sono incrementati MODULO n).\
come si può capire se la queue è piena o vuota? si potrebbe fare una seconda vriabile con il numero di interi. oppure si realizza un vettore di dimensione nMax+1 e si usa una cella come sentinella.\
L'implementazione di questo metodo, e anche di quelli con liste e tutto quanto, sono da pag 87 a 94 delle slides.

### Strategie per riconoscere la coda vuota
bohhhh guarda le slides a pagina 85

## Queue di priorità
ADT che supporta operazioni di:
- insert: inserisci un elemento (PQinsert)
- extract: preleva (e cancella) l’elemento a priorità massima (o minima) (PQextractmax o PQextractmin).

Terminologia: la strategia di gestione dei dati è detta priority-first.

Si può implementare con vettore, lista e heap (trattato più avanti).

### Complessità:
Se k'implementazione è con vettore/lista NON ordinato:
- inserzione in testa alla lista o in coda al vettore -> O(1)
- estrazione/visualizzazione del massimo/minimo con scansione -> O(N)
- cambio di priorità: richiede ricerca dell’elemento con scansione -> O(N)
Altrimenti se è con vettore/lista ordinato:
- inserzione ordinata nella lista o nel vettore mediante scansione -> O(N)
- estrazione/visualizzazione del massimo/minimo se memorizzato in testa alla lista o in coda al vettore con accesso diretto -> O(1)
- richiede la ricerca dell'elemento

### Implementazione con lista ordinata
Noi tratteremo soltanto l'implementazione con liste ordinate.
```c
// PQ.h
typedef struct pqueue *PQ;
PQ PQinit(int maxN);
int PQempty(PQ pq);
void PQinsert(PQ pq, Item data); Item PQextractMax(PQ pq);
Item PQshowMax(PQ pq);
void PQdisplay(PQ pq);
void PQchange(PQ pq, Item data); // cambia la priorità
```
```c
typedef struct PQnode *link;
struct PQnode{ Item val; link next; };

struct pqueue { link head; };
link NEW(Item val, link next) {
    link x = malloc(sizeof *x);
    x->val = val;
    x->next = next;
    return x;
}

PQ PQinit(int maxN) {
    PQ pq = malloc(sizeof *pq);
    pq->head = NULL;
    return pq;
}

int PQempty(PQ pq) { return pq->head == NULL;}

Item PQshowMax(PQ pq) { return pq->head->val; }

void PQdisplay(PQ pq) {
    link x;
    for (x=pq->head; x!=NULL; x=x->next)
        ITEMdisplay(x->val);
    return;
}

void PQinsert (PQ pq, Item val) {
    link x, p;
    Key k = KEYget(val);
    if (pq->head==NULL ||KEYless(KEYget(pq->head->val),k)) {
        pq->head = NEW(val, pq->head);
        return;
    }
    for(x=pq->head->next, p=pq->head; x!=NULL&&KEYless(k,KEYget(x->val)); p=x, x=x->next);
        p->next = NEW(val, x);
    return;
}

Item PQextractMax(PQ pq) {
    Item tmp;
    link t;
    if (PQempty(pq)) {
        printf("PQ empty\n");
        return ITEMsetvoid();
    }
    tmp = pq->head->val;
    t = pq->head->next;
    free(pq->head);
    pq->head = t;
    return tmp;
}

void PQchange (PQ pq, Item val) {
    link x, p;
    if (PQempty(pq)) { printf("PQ empty\n"); return; }
    for(x=pq->head, p=NULL; x!=NULL; p=x, x=x->next) {
        if (ITEMeq(x->val, val)){
            if (x==pq->head) pq->head = x->next;
            else p->next = x->next; free(x);
            break;
        }
    }
    PQinsert(pq, val); return;
}
```

## Gestione dulicati nelle pile e code
o si aggiunge comunque un elemento con stessa chiave, perchè si tiene conto del fatto che ha tempo diverso, oppure anche se ha tempo diverso non ci possono essere due elementi con la stessa chiave. quindi si elimina il nuovo, il vecchio, o qualunque cosa si voglia.