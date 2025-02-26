[11/12/23] In questa lezione si introducono gli di alberi binari. Poi si definisocno gli alberi binari di ricerca, nei quali vale (sottoalbero sinistro) < radice < (sottoalbero destro). Si definiscono le operazioni di base sugli alberi binari di ricerca come inserimento in foglia e in radice, ricerca, visita, minimo, massimo, rotazione a destra e sinistra. 

- [Albero binario](#albero-binario)
  - [Valutazione di espressioni](#valutazione-di-espressioni)
- [Alberi binari di ricerca (bst)](#alberi-binari-di-ricerca-bst)
  - [ADT di prima classe](#adt-di-prima-classe)
  - [Implementazione](#implementazione)
    - [BSTsearch](#bstsearch)
    - [BSTmin e BSTmax](#bstmin-e-bstmax)
    - [BSTinsert in foglia](#bstinsert-in-foglia)
    - [BSTvisit](#bstvisit)
    - [Rotazione a destra e sinistra del BST](#rotazione-a-destra-e-sinistra-del-bst)
    - [BSTinsert (in radice)](#bstinsert-in-radice)


# Albero binario
un albero binario è una terna contente una radice, un puntatore al figlio sinistro e uno al figlio destro.
```c
typedef struct node* link;
struct node {
    Item item;
    link left;
    link right;
};
```
si può misurare l'albero contando i nodi o misurando l'altezza.

si può visitare l'albero in tre modi:
- pre-order: prima la radice, poi il figlio sinistro, poi il destro
- in-order: prima il figlio sinistro, poi la radice, poi il destro
- post-order: prima il figlio sinistro, poi il destro, poi la radice

Un albero è detto completo se tutti i livelli sono completi tranne l'ulitmo che è completo da sinistra a destra

Un albero è detto bilanciato se la differenza di profondità tra sottoalbero destro e sinsitstro è al massimo 1, per tutti i nodi

Complessità di qualsiasi funzinoe ricorsiva su un albero binario: O(n) (n è il numero di nodi).
Se l'albero è completo (ogni nodo ha 0 o 2 figli) lo si può vedere come divide and conquer con a = 2 e b = 2
D(n) = C(n) = 1
T(n) = 1 + 2T(n/2)
T(1) = 1

O(n)

Se è totalmente sbialnciato (ogni nodo ha un solo figlio) lo si può vedere come decrease and conquer con a = 1 e decrease amount = 1
D(n) = C(n) = 1
T(n) = 1 + T(n-1)
T(1) = 1

O(n)

Ora mostreremo alcuni esempi d'uso:

## Valutazione di espressioni
![](<Screenshot 2023-12-12 alle 17.18.20.png>)
L'attraversamento in post-order delll'albero mostrato nell'esmpio mostra prima i due operandi e poi l'operatore, si chiama notazione polacca inversa (notazione Polacca normale è la visita in pre-order), e produce una striga come `AB+CD-*E*`. Nota come non siano necessarie le parentesi. Attraversandolo in-order si ottiene la notazione normale, che invece richiede le parentesi: `((A+B)*(C-D))*E`.

se abbiamo una stringa in notazione polacca (tipo `*+5 12 3`), possiamo costruire l'albero binario corrispondente con un algoritmo ricorsivo:
```c
int eval() {
  int x = 0;
  while (a[i] == ' ')
      i++;
  if (a[i] == '+') {
    i++;
    return eval() + eval ();
  }
  if (a[i] == '*') {
    i++;
    return eval() * eval ();
  }
  while ((a[i] >= '0') && (a[i] <= '9'))
    x = 10 * x + (a[i++]-'0') ;
  return x;
}
```
# Alberi binari di ricerca (bst)
La sua propritetà è che la radice è maggiroe di tutto cio che c'è nel sottoalbero sinistro e minore di tutto ciò che c'è nel sottoalbero destro.

Nota: la visita in order di un BST da numeri in ordine crescente

## ADT di prima classe
```c
typedef struct  binarysearchtree *BST;

BST BSTinit() ;
void BSTfree(BST bst);
int BSTcount(BST bst);
int BSTempty(BST bst);
Item BSTsearch(BST bst, Key k);
void BSTinsert_leafI(BST bst, Item x);
void BSTinsert_leafR(BST bst, Item x);
void BSTinsert_root(BST bst, Item x);
Item BSTmin(BST bst);
Item BSTmax(BST bst);
void BSTvisit(BST bst, int strategy);
```

## Implementazione
Non come vettore, perchè non è completo e ci potrebbero essere potenzialmente molti buchi.

```c
#include <stdlib.h>
#include "Item.h"
#include "BST.h"

typedef struct BSTnode* link;
struct BSTnode { Item item; link l; link r;};
struct binarysearchtree { link root; link z; };

static link NEW(Item item, link l, link r) {
  link x = malloc(sizeof *x);
  x->item = item; x->l = l; x->r = r;
  return x;
}

BST BSTinit( ) {
  BST bst = malloc(sizeof *bst) ;
  bst->root= ( bst->z = NEW(ITEMsetNull(), NULL, NULL));
  return bst;
}
```
```c
void BSTfree(BST bst) {
  if (bst == NULL)
    return;
  treeFree(bst->root, bst->z);
  free(bst->z);
  free(bst);
}
static void treeFree(link h, link z) {
  if (h == z)
    return;
  treeFree(h->l, z);
  treeFree(h->r, z);
  free(h);
}
```
```c
int BSTcount(BST bst) {
  return countR(bst->root, bst->z);
}
static int countR(link h, link z) {
  if (h == z)
   return 0;
 return countR(h->l, z) + countR(h->r, z) + 1;
}
```
```c
int BSTempty(BST bst) {
  if (BSTcount(bst) == 0)
    return 1;
  return 0;
}
```

Tutte le funzioni saranno O(h) (h è l'altezza dell'albero), quindi O(log n) se l'albero è bilanciato, O(n) se è sbilanciato.
### BSTsearch
- se l'albero è vuoto, restituisci NULL
- se la chiave cercata è minore della chiave della radice, cerca nel sottoalbero sinistro
- se la chiave cercata è maggiore della chiave della radice, cerca nel sottoalbero destro
- se la chiave cercata è uguale alla chiave della radice, restituisci l'item della radice

```c
Item BSTsearch(BST bst, Key k) {
  return searchR(bst->root, k, bst->z);
}

Item searchR(link h, Key k, link z) {
  if (h == z)
    return ITEMsetNull();
  int cmp = KEYcompare(k, KEYget(h->item));
  if (cmp < 0)
    return searchR(h->l, k, z);
  if (cmp > 0)
    return searchR(h->r, k, z);
  return h->item;
}
```

### BSTmin e BSTmax
se l'albero è vuoto, restituisci NULL
se il sottoalbero sinistro è vuoto, restituisci l'item della radice
altrimenti cerca nel sottoalbero sinistro
```c
Item BSTmin(BST bst) {
  return minR(bst->root, bst->z);
}

Item minR(link h, link z) {
  if (h == z)
    return ITEMsetNull();
  if (h->l == z)
    return (h->item);
  return minR(h->l, z);
}
```
```c
Item BSTmax(BST bst) {
  return maxR(bst->root, bst->z);
}

Item maxR(link h, link z) {
  if (h == z)
return ITEMsetNull(); if (h->r == z)
    return (h->item);
  return maxR(h->r, z);
}
```

### BSTinsert in foglia
Versione ricorsiva e iterativa. La versione ricorsiva è più semplice, ma la versione iterativa è più efficiente in termini di spazio.
Versione ricorsiva:
```c
void BSTinsert_leafR(BST bst, Item x) {
  bst->root = insertR(bst->root, x, bst->z);
}

static link insertR(link h, Item x, link z) {
  // se l'albero è vuoto, restituisci un nuovo nodo
  if (h == z)
    return NEW(x, z, z);
  // se il nodo da inserire è minore della radice, inseriscilo nel sottoalbero sinistro
  if (KEYcmp(KEYget(x), KEYget(h->item))==-1)
    h->l = insertR(h->l, x, z);
  // se il nodo da inserire è maggiore della radice, inseriscilo nel sottoalbero destro
  else
    h->r = insertR(h->r, x, z);
  return h;
}
```

Versione iterativa:
```c
void BSTinsert_leafI(BST bst, Item x) {
  link p = bst->root, h = p;
  if (bst->root == bst->z) {
    bst->root = NEW(x, bst->z, bst->z);
    return;
  }
  while (h != bst->z) {
    p = h;
    h = (KEYcmp(KEYget(x),KEYget(h->item))==-1) ? h->l : h->r;
  }
  h = NEW(x, bst->z, bst->z);
  if (KEYcmp(KEYget(x), KEYget(p->item))==-1)
    p->l = h;
  else
    p->r = h;
}
```

### BSTvisit
```c
void BSTvisit(BST bst, int strategy) {
  if (BSTempty(bst))
    return;
  treePrintR(bst->root, bst->z, strategy);
}

// ITEMstore è una funzione che stampa l'item
static void treePrintR(link h, link z, int strategy) {
  if (h == z)
    return;
  if (strategy == PREORDER)
    ITEMstore(h->item);
  treePrintR(h->l, z, strategy);
  if (strategy == INORDER)
    ITEMstore(h->item);
  treePrintR(h->r, z, strategy);
  if (strategy == POSTORDER)
    ITEMstore(h->item);
}
```

### Rotazione a destra e sinistra del BST
Esempio di rotazione a destra:
![ciao](<rotazione a destra di bst.png>)

### BSTinsert (in radice)
- Si inserisce in foglia
- Si ruota fino a quando il nodo inserito non diventa la radice

```c
void BSTinsert_root(BST bst, Item x) {
  bst->root = insertT(bst->root, x, bst->z);
}

static link insertT(link h, Item x, link z) {
  if (h == z)
    return NEW(x, z, z);
  if (KEYcmp(KEYget(x), KEYget(h->item))==-1) {
    h->l = insertT(h->l, x, z);
    h = rotR(h);
  }
  else {
    h->r = insertT(h->r, x, z);
    h = rotL(h);
  }
  return h;
}
```