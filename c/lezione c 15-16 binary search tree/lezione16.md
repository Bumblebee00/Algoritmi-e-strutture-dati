[11/12/23] in questa lezione si parla di ???

- [Estensione dei BST elementari](#estensione-dei-bst-elementari)
  - [Successore e predecessore](#successore-e-predecessore)
  - [BST insert in foglia](#bst-insert-in-foglia)
    - [Ricorsiva](#ricorsiva)
    - [Iterativa](#iterativa)
  - [BSTselect](#bstselect)
  - [Rotazione a destra e sinistra del BST](#rotazione-a-destra-e-sinistra-del-bst)
  - [BST insert in radice](#bst-insert-in-radice)
  - [BST partition](#bst-partition)
  - [BST delete](#bst-delete)
  - [Bilanciamento](#bilanciamento)
- [Order statistic BST](#order-statistic-bst)
  - [Interval BST](#interval-bst)


# Estensione dei BST elementari
Si possono aggiungere:
- puntatore al padre
- dimensione del sottoalbero

il padre del nodo radice è il tappo `z`

Con queste estensioni, alcune delle funzioni viste prima rimangono unmodified, altre vanno modificate leggermente, e altre che non erano possibili (o lo erano molto inefficientemente) diventano possibili.

## Successore e predecessore
Il successore di un nodo `x` è il nodo `s` che contiene il valore più piccolo tra tutti i nodi che contengono un valore più grande del nodo `x`. Cioè mettendo tutti i nodi in un array ordinato secondo la chiave, il successore `s` è l'elemento successivo a `x` nell'array. Analogamente il predecessore è l'elemento precedente a `x` nell'array.

> DOMANDA CHE FARA ALL'ORALE DI SICURO!!!:

Dov'è quindi il successore del nodo `x`?
È nel sottoalbero destro, più a sinistra possibile, se il sottoalbero esiste. Per arrivarci facciamo un passo a destra, e poi tutti a sinistra. Se il sottoalbero non esiste invece, il nodo `x` è il ramo destro di suo padre (ed è anche maggiore di suo padre). Qundi si continua così risalendo l'albero sperando di risalire fino a un nodo il cui valore è maggiore di `x`. Se si arriva al tappo `z` vuol dire che `x` è il nodo con la chiave massima, e quindi non ha successore.

![](<successore in bst.png>)

```c
Item searchPred(link h, key k, link z) {
    link p;
    if (h == z) return ITEMsetNul1 () ;
    if (KEYmp(k, KEYget (h->item))==0) {
        if (h->1 != z) return max (h->1, z);
        else {
            p = h->p;
            // finchè c'è un padre e il figlio sinistro del padre è h
            while (p != z && h == p->l) {h = p; p = p->p;}
            return p->item;
        }
    }
    if (KEYcmp(k, KEYget (h->item))==-1)
        return searchPred(h->1, k, z);
    return searchpred (h->r, k, z);
}
Item BSTpred (BST bst, Key k) {
    return searchPred (bst->root, k, bst->z);
}
```

## BST insert in foglia
codice a pag 131
### Ricorsiva
come la versione basic, ma si tiene conto del puntatore al padre e alla dimensione
### Iterativa


## BSTselect
Selezione dell'item con la r-esima chiave più piccola (quindi rango r = chiave in posizione r nell'ordinamento, ad esempio se r=0 item con chiave minima). Definiamo t come il numero di nodi del sottoalbero sinistro. Lo pseudocodice della select è:
- t = r: ritorno la radice del sottoalbero
- t > r: ricorsione nel sottoalbero sinistro alla ricerca della k-esima chiave più piccola
- † < r: ricorsione nel sottoalbero destro alla ricerca della (r-t-1)-esima chiave più piccola

complessità O(n) se nel nodo non c'è annotata la dimensione del sottoalbero, O(log n) se c'è

## Rotazione a destra e sinistra del BST
> non se la ricorda neanche cabodi qundi non bisogna impararla a memoria, se chiede all'orale basta dire che si va a cercare su internet

molte modifiche rispetto al BST elementare
è complicata perchè ci sono tre cambi di padre e tre cambi di dimansioni.

```c
link rotR(link h) {
  link x = h->l;
  h->l = x->r;
  x->r->p = h;
  x->r = h;
  x->p = h->p;
  h->p = x;
  x->N = h->N;
  h->N = 1;
  h->N += (h->l) ? h->l->N : 0;
  h->N += (h->r) ? h->r->N : 0;
  return x;
}
```

```c
link rotL(link h) {
  link x = h->r;
  h->r = x->l;
  x->l->p = h;
  x->l = h;
  x->p = h->p;
  h->p = x;
  x->N = h->N;
  h->N = 1;
  h->N += (h->l) ? h->l->N : 0;
  h->N += (h->r) ? h->r->N : 0;
  return x;
}
```

## BST insert in radice
leggere modifiche rispetto al BST elementare

## BST partition
è un sottoprodotto della select, cioè potremmo usare quello pseudocodice per fare un altra cosa.
La BSTpartition riorganizza l'albero avendo l'item con la k-esima chiave più piccola nella radice. definendo sempre t come il numero di nodi del sottoalbero sinistro, ecco lo pseudocodice:
- porre il nodo come radice di un sottoalbero:
  - t > k: ricorsione nel sottoalbero sinistro, partizionamento rispetto alla k-esima chiave più piccola, al termine rotazione a destra
  - t < k: ricorsione nel sottoalbero destro, partizionamento rispetto alla (k-t-1)-esima chiave più piccola, al termine rotazione a sinistra

```c
link partR(link h, int r) {
  int t = h->l->N;
  if (t > r) {
    h->l = partR(h->l, r);
    h = rotR(h);
  }
  if (t < r) {
    h->r = partR(h->r, r-t-1);
    h = rotL(h);
  }
  return h;
}
```

## BST delete
se devo concellare una foglia è banale, se devo cancellare un nodo con un solo figlio, lo sostituisco con il figlio, se devo cancellare un nodo con due figli, è più complicato. Per farlo si lascia la topologia dell'albero intatta, e fa risalire un nodo foglia al posto del nodo eliminato. il nodo foglia che si fa risalire è il successore o il predecessore del nodo eliminato.

è come una partition con l'elemento di rango 0

???

## Bilanciamento
I BST bilanciati sono BST in cui la differenza tra il numero di nodi del sottoalbero sinistro e destro è limitata. I B-tree sono un esempio di BST perfettamente bilanciato, in cui la differenza è sempre 0 o 1. Un abero 2,3 o 4 RB-tree ha uno sbilanciamento di 2,3 o 4.

si può fare il bilanciamento dopo ogni operazione, o solo dopo un tot. noi adesso vediamo la versione dopo un tot. vediamo l'algoritmo di Day, Stout e Warren, di complessità O(n), che costruisce un albero quasi completo (tutti i livelli completi, tranne l’ultimo riempito da sinistra a destra, come l'heap).

```c
static link balanceR(link h, link z) { int r;
  if (h == z)
    return z;
  r = (h->N+1)/2-1;
  h = partR(h, r);
  h->l = balanceR(h->l, z);
  h->r = balanceR(h->r, z); return h;
}
void BSTbalance(BST bst) {
  bst->root = balanceR(bst->root, bst->z);
}
```

# Order statistic BST

## Interval BST
Sono dei BST nel quale la chiave è un intervallo $[low, high] \subset \R$, e non un solo valore. il confrono degli intervalli viene fatto sul low. inoltre c'è un altra annotazione, oltre a quella del numero di nodi del sottoalbero, che è il massimo high tra tutti i nodi del sottoalbero.