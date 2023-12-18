// un quasi ADT per la quotazione giornaliera e un ADT di I classe per collezione di quotazioni giornaliere (a scelta se in un solo modulo o in due). Per la collezione di quotazioni si faccia uso di un BST (con data come chiave di ricerca e ordinamento). Per gli inserimenti di dati nel BST sono sufficienti gli inserimenti in foglia
#include "tempo.h"
#include<stdlib.h>
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
    int quotazione;
};
typedef struct QuotazioneGiornaliera* Quotazione;

typedef struct BSTQuotazioniGiornaliere* Quotazioni;

Quotazioni BSTinit();
void BSTaddInLeaf(Quotazioni BST, Quotazione quotazione);

Quotazione calcolaQuotazione(transazioni transazioni, int n_transazioni, tempo data);
#endif