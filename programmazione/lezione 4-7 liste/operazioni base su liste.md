[28/10/23]

# Sequenza lineare (detta anche lista)
struttura dati fatta a pezzettini, aggiunti e rimossi un po alla volta.
la lista non è solo un insieme di dati, ma un insieme di dati **ordinati**.
può essere ordinata ([1,2,3,4,5]) o non ordinata ([3,1,2,5,4])
può essere lineare (normale lista alla python) (il costo dia ccesos di un elemento è O(1) perchè in memoria è tutta di seguito) o concatenata

### Liste concatenate
i dati sono memorizzati in memoria in modo non sequenziale, ma ogni elemento ha un puntatore al successivo. quindi per accedere ad un elemento devo scorrere tutta la lista fino a quello che mi interessa. il costo di accesso è O(n) perchè devo scorrere tutta la lista.

### Operazioni desiderate
- ricerca di un elemento con campo chiave uguale a chiave desiderata
- inserimento di un elemento
- - in testa
- - in coda
- - in posizione arbitraria
- cancellazione di un elemento
- - in testa
- - in coda
- - in posizione arbitraria
- - che ha un certo valore di chiave

### Implementazione con vettore
Le liste possono essere realizzate mediante puntatori (allocazione dinamica):
- se è noto o stimabile il numero massimo di elementi, oppure sfruttando la ri-allocazione
- sfruttando la contiguità fisica degli elementi (elemento all’indice i successore di quello all’indice i-1 e predecessore di quello all’indice i+1)
- disaccoppiando contiguità fisica e relazione predecessore/successore mediante puntatori (lista concatenate mediante puntatori)

# Liste realizzate mediante concatenazione
Le liste possono essere realizzate mediante strutture ricorsive allocate individualmente:
- se non è noto o stimabile il numero massimo di elementi
- se la relazione è da predecessore a successore si hanno liste concatenate semplici
- se è in entrambi i versi si hanno liste concatenate doppie.

## Implementazione
Strutture dati dinamiche come sequenze di nodi. In C ogni nodo è una struct con:
- un numero arbitrario (fisso, una volta definite la struct) di dati, generalmente racchiusi in un campo val di tipo Item (si tratta di una covenzione, non di una regola)
- uno o due riferimenti (“link”) che puntano al nodo successivo e/o precedente
Inoltre ci deve essere da qualche parte u puntatore al primo nodo della lista (head) (ci può esserne uno al suo ultimo nodo (tail)).

### Definizione di Item e Key
    typedef struct {
        char nome[40];
        data_t nascita;
    } Item;
    
    typedef char *Key; // la chiave di solito è un pezzo dell'item, ma non preforza.

    Key KEYget(Item d);
    int KEYeq(Key k1, Key k2);
    int KEYless(Key k1, Key k2);
    int KEYgreater(Key k1, Key k2);

### Definire il Nodo
##### Tipologia 1
senza typefed
    struct node {
        Item val;
        struct node *next;
    };
##### Tipologia 2
con typedef, definisco il tipo node_t come alias per il mio struct, e il tipo link come alias per il mio puntatore a node_t
    typedef struct node {
        Item val;
        struct node *next;
    } node_t, *link;
##### Tipologia 3
con separazione tra typedef e dichiarazione della struct node
    typedef struct node *link;
    struct node {
        Item val;
        link next;
    };
##### Tipologia 4
    typedef struct node node_t;
            struct node {
            Item val;
            node_t *next;
    };
##### Tipologia 5
    typedef struct node *link;
    struct node {
        Item val;
        link next;
    };

### Ripassino sui puntatori
x->val è uguale a (*x).val

## Operazioni atomiche
#### Creare una lista vuota
    link head = NULL;
testare se la lista è vuota:
    if (head == NULL)
#### Allocazione di un nodo
si dichiara un puntatore al nodo come:
    link x;
e poi si alloca il nodo con:
    x = malloc(sizeof(node_t));
oppure
    x = malloc(sizeof(*x));
#### Inserimento di un nodo in mezzo
volgio inserire un nodo puntato da t dopo il nodo puntato da x
    t->next = x->next;
    x->next = t; // se facessi prima questo, perderei il puntatore al nodo successivo di x
#### Cancellazione di un nodo in mezzo
volgio cancellare il nodo puntato da t dopo il nodo puntato da x
    x->next = t->next; // oppure x->next = x->next->next;
    free(t);
#### Attraversamento di una lista
##### per operazioni semplici (non modifico la lista):
    for (link x = head; x != NULL; x = x->next) {
        // fai qualcosa con x->val
    }
##### per operazioni complesse (modifico la lista):
    link x, p, head;
    ...
    p = NULL;
    for (x=head; x!=NULL; p = x, x=x->next) {
        // fai qualcosa con x->val
    }
in questa versione, p è il predecessore di x. si può anceh scrivere solo con un puntatore solo.
    link p, head;
    ...
    for (p=head; p!=NULL && p->next!=NULL; p=p->next){
        // fai qualcosa con p->next->val
    }
##### per op complesse
questa è la modalità più complessa
    link *xp, head;
    ...
    for (xp=&head; *xp!=NULL; xp=&((*xp)->next)){
        // fai qualcosa con (*xp)->val
    }
quindi xp è un puntatore che punta a un puntatore (head o x->next). quindi *xp è il puntaotre x->next. qundi (*xp)->val è il valore di x->next->val, e (*xp)->next è il puntatore x->next->next. qundi per aggiornare il ciclo for, io faccio xp=&((*xp)->next), do a xp il puntatore al puntatore x->next->next.
##### attraversamento ricorsivo
    void listTravR(link h) {
        if (h == NULL)
            return;
        ITEMdisplay(h->val);
        listTravR(h->next);
    }
attraversamento all'indietro:
    void listTravR(link h) {
        if (h == NULL)
            return;
        listTravR(h->next);
        ITEMdisplay(h->val);
    }
