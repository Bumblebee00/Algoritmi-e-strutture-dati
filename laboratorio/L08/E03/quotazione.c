#include "quotazione.h"

typedef struct BSTNode* link;
link BSTaddInLeafR(link root, Quotazione quotazione);

struct BSTNode{
    Quotazione valore;
    link l;
    link r;
};

struct BSTQuotazioniGiornaliere{
    link root;
};

Quotazione calcolaQuotazione(transazioni transazioni, int n_transazioni, tempo data){
    Quotazione q = malloc(sizeof(struct QuotazioneGiornaliera));
    q->data = data;
    for (int i=0; i<n_transazioni; i++){
        q->quotazione += transazioni[i].v * transazioni[i].n;
    }
    q->quotazione /= n_transazioni;
    return q;
}

Quotazioni BSTinit(){
    Quotazioni BST = malloc(sizeof(struct BSTQuotazioniGiornaliere));
    BST->root = NULL;
    return BST;
}

void BSTaddInLeaf(Quotazioni BST, Quotazione quotazione){
    BST->root = BSTaddInLeafR(BST->root, quotazione);
}

link BSTaddInLeafR(link root, Quotazione quotazione){
    if (root == NULL){
        link nuovoNodo = malloc(sizeof(struct BSTNode));
        nuovoNodo->valore = quotazione;
        nuovoNodo->l = NULL;
        nuovoNodo->r = NULL;
        return nuovoNodo;
    }

    if (tempoCompare(root->valore->data, quotazione->data) > 0){
        root->l = BSTaddInLeafR(root->l, quotazione);
    } else {
        root->r = BSTaddInLeafR(root->r, quotazione);
    }

    return root;
}

