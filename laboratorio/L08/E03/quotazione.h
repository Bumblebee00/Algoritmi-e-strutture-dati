// un quasi ADT per la quotazione giornaliera e un ADT di I classe per collezione di quotazioni giornaliere (a scelta se in un solo modulo o in due). Per la collezione di quotazioni si faccia uso di un BST (con data come chiave di ricerca e ordinamento). Per gli inserimenti di dati nel BST sono sufficienti gli inserimenti in foglia
#include "tempo.h"
#include<stdlib.h>
#include<stdio.h>
#ifndef QUOTAZIONE_H
#define QUOTAZIONE_H

struct transazione{
    tempo data;
    int v; // il valore del titolo nella transazione
    int n; // quantità di titoli scambiati in tale transazione
};
typedef struct transazione* transazioni;

struct QuotazioneGiornaliera{
    tempo data;
    float quotazione;
};
typedef struct QuotazioneGiornaliera* Quotazione;

/*
BST oridnato per data:
più recenti a destra, più antichi a sinistra
    2006
   /   \
2005    2007
*/
typedef struct BSTQuotazioniGiornaliere* Quotazioni;

// funzioni per ADT Quotazione
void printQuotazione(Quotazione q);
Quotazione calcolaQuotazione(transazioni transazioni, int n_transazioni, tempo data);

// funzioni per ADT Quotazioni
Quotazioni BSTinit();
void BSTaddInLeaf(Quotazioni BST, Quotazione quotazione);
void printBST(Quotazioni BST);
Quotazione BSTsearch(Quotazioni BST, tempo data);
Quotazione searchMaxValoreBST(Quotazioni BST, tempo data1, tempo data2, int mode);
// bilancia l'albero rendendolo quasi completo (tutti i livelli completi, tranne l’ultimo riempito da sinistra a destra)
void bilanciaBST(Quotazioni BST);
int deltaMaxCammino(Quotazioni BST);
#endif