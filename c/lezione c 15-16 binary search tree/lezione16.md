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
> DOMANDA CHE FARA ALL'ORALE DI SICURO!!!
il successore è il più piccolo di tutti quelli che stanno dopo, il predecessore trova il massimo di tutti quelli che vengono prima.

Il successore di un nodo quindi è in basso a destra, se il sottoalbero esiste, per arrivarci facciamo un passo a destra, e poi tutti a sinistra.

Se il sottoalbero non esiste, il nodo è il massimo di qualcun'altro, quindi il predecessore di qualcunaltro, quindi per trovare il successore troviamo il primo antenato di h il cui figlio sinistro è anche un antenato di h.

da riscrivere

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

## BST insert in radice
leggere modifiche rispetto al BST elementare

## BST partition
è un sottoprodotto della select, cioè potremmo usare quello pseudocodice per fare un altra cosa.
La BSTpartition riorganizza l'albero avendo l'item con la k-esima chiave più piccola nella radice. definendo sempre t come il numero di nodi del sottoalbero sinistro, ecco lo pseudocodice:
porre il nodo come radice di un sottoalbero:
• t > k: ricorsione nel sottoalbero sinistro, partizionamento rispetto alla k-esima chiave più piccola, al termine rotazione a destra
• t < k: ricorsione nel sottoalbero destro, partizionamento rispetto alla (k-t-1)-esima chiave più piccola, al termine rotazione a sinistra

## BST delete
se devo concellare una foglia è banale, se devo cancellare un nodo con un solo figlio, lo sostituisco con il figlio, se devo cancellare un nodo con due figli, è più complicato. Per farlo si lascia la topologia dell'albero intatta, e fa risalire un nodo foglia al posto del nodo eliminato. il nodo foglia che si fa risalire è il successore o il predecessore del nodo eliminato.

è come una partition con l'elemento di rango 0

???

## Bilanciamento
I BST bilanciati sono BST in cui la differenza tra il numero di nodi del sottoalbero sinistro e destro è limitata. I B-tree sono un esempio di BST perfettamente bilanciato, in cui la differenza è sempre 0 o 1. Un abero 2,3 o 4 RB-tree ???

si può fare il bilanciamento dopo ogni operazione, o solo dopo un tot. noi adesso vediamo la versione dopo un tot. vedremo un algoritmo O(n)

# Order statistic BST

## Interval BST
Sono dei BST nel quale la chiave è un intervallo $[low, high] \subset \R$, e non un solo valore. il confrono degli intervalli viene fatto sul low. inoltre c'è un altra annotazione, oltre a quella del numero di nodi del sottoalbero, che è il massimo high tra tutti i nodi del sottoalbero.