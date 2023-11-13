# Invertire una lista
Soluzione1: uso di una lista ausiliaria, in cui inserisco gli elementi in ordine inverso rispetto alla lista originale. questo metodo svuota la lista originale, ma non la distrugge.
```c
link listReverseF(link x) {
    link y = x; // per non modificare x
    link r = NULL; // nuova lista, che riempo in ordine contrario rispetto a x
    Item tmp;
    while (y != NULL) {
        tmp = listExtrHeadP(&y);
        r = listInsHead(r, tmp);
    }
    return r;
}
```

Soluzione2: girare i puntatori.
```c
link listReverseF(link x) {
    link temp, y = x, r = NULL;
    while (y != NULL) {
        temp = y->next;
        y->next = r;
        r = y;
        y = temp;
    }
    return r;
}
```

# Sort delle liste
Premessa: ordinare le liste fa schifo perchè accedere all'elemento n è O(n), quindi tanto vale buttare tutto su un vettore, ordinare il vettore, e rimettere in lista.
## Insertion sort
Reminder: SortListIns questa funzione è da usare solo se si è sicuri che la lista è ordinata. quello che fa è inserire il nodo in testa se il valore è minore del primo nodo, altrimenti cerca il posto giusto e lo inserisce lì.

Soluzione1:
```c
link listSortF(link h) {
    link y = h, r = NULL;
    Item tmp;
    while (y != NULL) {
        tmp = listExtrHeadP(&y);
        r = SortListIns(r, tmp);
    }
    return r;
}
```

Soluzione2:
```c
for(t=h->next, h->next=NULL; t!=NULL; t=u){
    u = t->next; // salvo il prossimo elemento
    if (h->val > t->val) {
        t->next = h; // caso particolare: inserimento in testa
        h = t;
    } else {
        for (x=h; x->next != NULL; x=x->next)
            if (x->next->val > t->val){ break; }
        // inserimento in mezzo
        t->next = x->next;
        x->next = t;
    }
}
```

# Esempi
Dati:
- un elenco di cantanti (stringhe), memorizzato in un vettore
- un elenco di canzoni (stringhe per i titoli, interi che indicano l’indice del cantante nel vettore dei cantanti)
una canzone ha un solo cantante, ma un cantante può avere più canzoni. bisognia per ogni cantante, creare una lista di canzoni.

## Soluzione1
Per ogni canzone, aggiungo un nodo alla lista del cantante.
Reminder: la strdup() crea una copia della stringa passata come argomento. Equivale a:
```c
v = malloc((strlen(canz[i].titolo)+1)*sizeof(char));
strcpy(v, canz[i].titolo);
```

```c
typedef struct nodo_s {
    Item val; // sarà char *
    struct nodo_s *next;
} nodo_t, *link;

typedef struct canz_s{
    char *titolo;
    int id_cant;
} canz_t;

typedef struct cant_s{
  char *nome;
  link h;
} cant_t;

void generaElenco(cant_t *cant, int n_cant, canz_t *canz, int n_canz){
    int i, id_canz;
    Item v;
    // initalizza a null tutte le liste di cantanti
    for (i=0; i<n_cant; i++)
        cant[i].h = NULL;
    // itera sulle canzoni
    for (i=0; i<n_canz; i++) {
        id_canz = canz[i].id_cant;
        v = strdup(canz[i].titolo);
        cant[id_canz].h = newNode(v,cant[id_c].h);
    }
}
```

## Soluzione2
Ogni cantante, oltre al nome, ha un puntatore alla testa della lista delle sue canzoni
- La lista delle canzoni di un cantante è creata concatenando i nodi del vettore canz che hanno quel cantante come autore
- Non si creano ex novo nodi per la lista, non serve il tipo Item

```c
typedef struct canz_s{
    char *titolo;
    int id_cant;
    struct canz_successiva *next;
} canz_t, *link;

typedef struct cant_s{
    char *nome;
    link h;
} cant_t;
```

## Soluzione 3
Soluzione 3: con indici
- Ogni cantante, oltre al nome, ha un indice del dato in testa alla lista delle sue canzoni
- Ogni canzone, oltre a titolo e indice del cantante, contiene l’indice della canzone successiva nella lista di quel cantante
- La lista delle canzoni di un cantante è creata concatenando mediante gli indici i nodi del vettore canz che hanno quel cantante come autore
- Non si creano ex novo nodi per la lista, non serve il tipo Item

```c
typedef struct canz_s{
    char *titolo;
    int id_cant;
    int id_next;
} canz_t;

typedef struct cant_s{
    char *nome;
    int id_testa;
} cant_t;
```

## Soluzione 4
Ogni cantante, oltre al nome, ha un vettore dinamico delle sue canzoni (puntatore) e il numero delle sue canzoni
- Ogni canzone contiene titolo e indice del cantante
- Il numero di canzoni di ogni cantante è calcolato con un’iterazione
sulle canzoni
- La lista delle canzoni è realizzata tramite vettore di indici
- Non si creano ex novo nodi per la lista, non serve il tipo Item