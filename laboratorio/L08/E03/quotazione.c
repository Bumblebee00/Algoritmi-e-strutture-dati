#include "quotazione.h"

struct BSTQuotazioniGiornaliere{
    link root;
};

typedef struct BSTNode* link;
struct BSTNode{
    Quotazione valore;
    link l;
    link r;
    link p;
    int N; // dimensione del sottoalbero
};


Quotazione calcolaQuotazione(transazioni transazioni, int n_transazioni, tempo data){
    Quotazione q = malloc(sizeof(struct QuotazioneGiornaliera));
    q->data = data;
    int totTransazioni = 0;
    for (int i=0; i<n_transazioni; i++){
        q->quotazione += transazioni[i].v * transazioni[i].n;
        totTransazioni += transazioni[i].n;
    }
    q->quotazione /= totTransazioni;
    return q;
}


void printQuotazione(Quotazione q){
    if (q==NULL){ return; }
    printf("(data: %d/%d/%d, quotazione: %f)", q->data->anno, q->data->mese, q->data->giorno, q->quotazione);
}


Quotazioni BSTinit(){
    Quotazioni BST = malloc(sizeof(struct BSTQuotazioniGiornaliere));
    BST->root = NULL;
    return BST;
}

link BSTaddInLeafR(link nodo, Quotazione quotazione){
    if (nodo == NULL){
        link nuovoNodo = malloc(sizeof(struct BSTNode));
        nuovoNodo->valore = quotazione;
        nuovoNodo->l = NULL;
        nuovoNodo->r = NULL;
        nuovoNodo->p = NULL;
        nuovoNodo->N = 1;
        return nuovoNodo;
    }

    if (tempoCompare(nodo->valore->data, quotazione->data) > 0){
        nodo->l = BSTaddInLeafR(nodo->l, quotazione);
        nodo->l->p = nodo;
    } else {
        nodo->r = BSTaddInLeafR(nodo->r, quotazione);
        nodo->r->p = nodo;
    }
    (nodo->N)++;
    return nodo;
}

void BSTaddInLeaf(Quotazioni BST, Quotazione quotazione){
    BST->root = BSTaddInLeafR(BST->root, quotazione);
}

// se la chiave (data) è minore della chiave della radice, cerca nel sottoalbero sinistro
// se è maggiore cerca nel sottoalbero destro
Quotazione BSTsearchR(link root, tempo data){
    if (root == NULL){ return NULL; }
    int temp = tempoCompare(data, root->valore->data);
    if (temp == 0){ return root->valore; }
    else if (temp > 0){
        return BSTsearchR(root->r, data);
    } else {
        return BSTsearchR(root->l, data);
    }
}

Quotazione BSTsearch(Quotazioni BST, tempo data){
    return BSTsearchR(BST->root, data);
}

void printBSTR(link nodo){
    if (nodo->l != NULL){ printBSTR(nodo->l); }
    printQuotazione(nodo->valore); printf(", ");
    if (nodo->r != NULL){ printBSTR(nodo->r); }
}

// attraversamento in ordine
void printBST(Quotazioni BST){
    printf("BST di quotazioni: [");
    printBSTR(BST->root);
    printf("] (quotazioni di %d giornate)\n", BST->root->N);
}

// dato che il bst è ordinato per data e non per quotazione, non possiamo fare trucchietti tipo: vado sempre a destra se cerco il max
// quindi si visita tutto il bst in order, fintanto che i nodi sono compresi nell'intervallo di date, e si cerca il max
// Nota: data1 è più antica di data2
void searchMaxBSTR(link root, tempo data1, tempo data2, Quotazione* max, int mode){
    if (root->l != NULL && tempoCompare(data1, root->l->valore->data) <= 0){
        searchMaxBSTR(root->l, data1, data2, max, mode);
    }
    if (tempoCompare(data1, root->valore->data) <= 0 && tempoCompare(data2, root->valore->data) >= 0){
        int sign = mode ? -1 : 1;
        // se non c'è ancora un max (o min)
        if (*max == NULL){
            *max = root->valore;
        } else if (root->valore->quotazione*sign > (*max)->quotazione*sign){
            // se il root è maggiore del max (o minore del min)
            *max = root->valore;
        }
    }
    if (root->r != NULL && tempoCompare(data2, root->r->valore->data) >= 0){
        searchMaxBSTR(root->r, data1, data2, max, mode);
    }
}

Quotazione searchMaxValoreBST(Quotazioni BST, tempo data1, tempo data2, int mode){
    Quotazione max = NULL;
    searchMaxBSTR(BST->root, data1, data2, &max, mode);
    return max;
}

link rotR(link h) {
    if (h==NULL || h->l==NULL){ return NULL; }
    link x = h->l;
    h->l = x->r;
    if (x->r != NULL){ x->r->p = h;}
    x->r = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}

link rotL(link h) {
    if (h==NULL || h->r==NULL){ return NULL; }
    link x = h->r;
    h->r = x->l;
    if (x->l != NULL){ x->l->p = h;}
    x->l = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}

// riorganizza l’albero avendo l’item con la k-esima chiave più piccola nella radice
link BSTpartitonR(link nodo, int k){
    if (nodo == NULL){ return nodo; }
    if (nodo->l == NULL){ return nodo; }
    int t = nodo->l->N;
    if (t>k){
        nodo->l = BSTpartitonR(nodo->l, k);
        nodo = rotR(nodo);
    } else if (t<k){
        nodo->r = BSTpartitonR(nodo->r, k-t-1);
        nodo = rotL(nodo);
    }
    return nodo;
}

link bilanciaBSTR(link nodo){
    if (nodo == NULL){ return NULL;}
    int r = (nodo->N+1)/2 - 1;
    nodo = BSTpartitonR(nodo, r);
    nodo->l = bilanciaBSTR(nodo->l);
    nodo->r = bilanciaBSTR(nodo->r);
    return nodo;
}

// bilancia l'albero rendendolo quasi completo (tutti i livelli completi, tranne l’ultimo riempito da sinistra a destra)
void bilanciaBST(Quotazioni BST){
    BST->root = bilanciaBSTR(BST->root);
}