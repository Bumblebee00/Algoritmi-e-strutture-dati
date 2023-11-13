do camompletare!!!

# Operazioni avanzate
come per esempio inserire un nodo in testa, cancellare un nodo in mezzo, ecc.
## Liste non ordinate
### Creazione di un nodo
bisognia fornire il puntatore al successivo e il valore del nodo

    link newNode(Item val, link next) {
        link x = malloc(sizeof *x);
        if (x==NULL)
                return NULL;
        else {
            x->val = val;
            x->next = next;
        }
        return x;
    }

### Inserimento in testa
Soluzione 1: creare un nuovo nodo e inserirlo in testa

    link listInsHead(link head, Item val) {
        link x = newNode(val, head);
        return x;
    }
    /* nel main: */
    ...
    link head;
    Item d;
    ... qua si aggiungono valori a d...
    head = listInsHead(head, d);

Soluzione 2: modificare il puntatore alla testa (passaggio by reference della variabile head)

    void listInsHead(link *head_p, Item val) {
        *head_p = newNode(val, *head);
    }
    /* nel main: */
    ...
    link head;
    Item d;
    ... qua si aggiungono valori a d...
    listInsHead(&head, d);

### Inserimento in coda O(n)
serve il puntatore all'ultimo nodo della lista. bisogna o ricavarselo (O(n)) o mantenerlo nel codice (O(1)).<br>
Soluzione 1:

    link listInsTail(link h, Item val) {
        link x;
        if (h==NULL)
            return newNode(val, NULL);
        for (x=h; x->next!=NULL; x=x->next); // ; è sintatticamente equivalente a {}
        x->next = newNode(val, NULL);
        return h;
    }
    /* nel main: */
    ...
    link head=NULL;
    Item d;
    ... qua si aggiungono valori a d...
    head = listInsTail(head, d);

Soluzione 2 (con passaggio by reference):

    void listInsTail(link *head_p, Item val) {
        link x = *head_p;
        if (x==NULL)
            *head_p = newNode(val, NULL);
        else {
            for (; x->next!=NULL; x=x->next);
            x->next = newNode(val, NULL);
        }
    }
    /* nel main: */
    ...
    link head=NULL;
    Item d;
    ... qua si aggiungono valori a d...
    listInsTail(&head, d);

Soluzione 3 (come sopra ma più elegante, senza l'if):   

    void listInsTailP(link *hp, Item val) {
        link *xp = hp;
        while (*xp != NULL)
            xp = &((*xp)->next);
        *xp = newNode(val, NULL);
    }
    /* nel main: */
    ...
    link head=NULL;
    Item d;
    ... qua si aggiungono valori a d...
    listInsTailP(&head, d);

### Inserimento in coda O(n)
uso di 2 variabili di tipo puntatore a puntatore a nodo hp e tp per accedere a primo e ultimo nodo

    void listInsTFast(link *hp,link *tp,Item val) {
        if (*hp==NULL)
            *hp = *tp = newNode(val, NULL); // assegnazione multipla, si può fare in c
        else {
            (*tp)->next = newNode(val, NULL);
            *tp = (*tp)->next;
        }
    }
    /* nel main: */
    ...
    link head=NULL, tail=NULL;
    Item d;
    ... qua si aggiungono valori a d...
    listInsTailFast(&head, &tail, d);

### Ricerca di una chaive
Non essendo modificata la lista, basta un solo puntatore per l’attraversamento.
- Se la chiave c’è, si ritorna il dato che la contiene
- Se la chiave non c’è, si ritorna il dato nullo tramite chiamata alla funzione ITEMsetvoid.

    Item listSearch(link h, Key k) {
        link x;
        for (x=h; x!=NULL; x=x->next) if (KEYeq(KEYget(x->val), k))
            return x->val;
        return ITEMsetvoid();
    }
    /* main */
    ...
    link head=NULL;
    Item d; Key k;
    ...
    d = listSearch(head,k);

### Cancellazione del primo nodo
Se la lista non è vuota, aggiorna la testa della lista con il puntatore al secondo dato che diventa il primo. Bisogna anche ricordare il primo dato per poi liberarlo con free (IMPORTANTE: normalmente dopo aver fatto free(h) l'allocatore non cancella subito la memoria, quindi funzinoerebbe anche senza usare la variaile temp, ma facendo free(h); h=h->next; Tuttavia non è impossibile che ciò accada, quindi è meglio usare temp). Il main assegna a head il nuovo puntatore alla testa.

    link listDelHead(link h) {
        link temp = h;
        if (h == NULL)
            return NULL;
        h = h->next;
        free(temp);
        return h;
    }
    /* nel main: */
    ...
    link head = NULL;
    ...
    head = listDelHead(head);

### Cancellazione di nodo con chiave data
    link listDelKey(link h, Key k) {
        link x, p;
        if (h == NULL)
            return NULL;
        // x serve per cercare, p per fare il bypass
        for (x=h, p=NULL; x!=NULL; p=x, x=x->next) {
            if (KEYeq(KEYget(x->val),k)) {
                if (x==h) // equivalente a p==NULL
                    h = x->next;
                else
                    p->next = x->next;
                free(x);
                break;
            }
        }
        return h;
    }

### Estrazione del nodo in testa
(dato in return)

    link listExtractHead(link *hp) {
        link x = *hp;
        if (x != NULL)
            *hp = x->next;
        return x;
    }
    /* nel main: */
    ...
    link head = NULL;
    ...
    head = listExtractHead(&head);

## Liste ordinate
ove i dati Item sono ordinati in base alla chiave. L'inserimento e la cancellazione con ricerca sono O(n) (come le liste non ordinate) (c'è il vantaggio che nella cancellazione, se si supera il valore desiderato, si può smettere la ricerca. questo in media dimezza i calcoli, ma rimane sempre O(n))

### Inserimento
Questa funzione è da usare solo se si è sicuri che la lista è ordinata. quello che fa è inserire il nodo in testa se il valore è minore del primo nodo, altrimenti cerca il posto giusto e lo inserisce lì.
```c
link SortListIns(link h, Item val) {
    link x, p;
    Key k = KEYget(val);
    if (h==NULL || KEYgreater(KEYget(h->val),k))
        return newNode(val, h);
    for(x=h->next, p=h; 
        x!=NULL && KEYgreater(k,KEYget(x->val));
        p=x, x=x->next);
        p->next = newNode(val, x);
    return h;
}
```

### Ricerca
Item SortListSearch(link h, Key k) {
    link x;
    for (x=h; x!=NULL && KEYgeq(k, KEYget(x->val)); x=x->next)
    if (KEYeq(KEYget(x->val), k))
        return x->val;
    return ITEMsetvoid();
}

### Cancellazione di nodo con chiave data

## Liste concatenate particolari
Si usano nodi fittizi in testa e in coda per:
- semplificare i test di lista vuota (quando head punta a tail, la lista è vuota)
- creare liste circolari imponendo la condizione che l’ultimo nodo punti al primo
- Liste concatenate doppie: ogni nodo punta sia al successivo che al precedente

### Alcuni elementi di liste concatenate doppie:
#### Definizione di nodo
    typedef struct node *link, node_t;
    struct node {
        Item val;
        link next;
        link prev;
    };
#### Aggiunta in mezzo
bisognia stare attenti all'ordine di aggiornamento dei puntatori, si rischia di perdere il puntatore al nodo successivo.

    link x, t; // voglia aggiungere t dopo x
    t->next = x->next;
    x->next->prev = t;
    x->next = t;
    t->prev = x;