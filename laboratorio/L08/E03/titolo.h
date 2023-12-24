// un ADT di I classe per il titolo e uno per collezione di titoli (a scelta se in un solo modulo o in due). Per la collezione di titoli si faccia uso di una lista ordinata (si usi il codice del titolo come chiave di ordinamento)
#include "quotazione.h"
#define MAX 20

typedef struct titolo_s* Titolo;
typedef struct collezioneDiTitoli_s* TitoliList;

typedef struct listNode_s *link;
struct listNode_s{
    Titolo titolo;
    link next;
};

// aggiunge una nuova quotazione al bst (in foglia)
void updateTitolo(Titolo t, Quotazione Quotazione);
void printTitolo(Titolo t);
// cerca nell'insieme di quotazioni di un titolo, quella con la data specificata
Quotazione SearchQuotazione(Titolo t, tempo data);
// search max (if mode==0, otherwise min) in a date interval
Quotazione SearchMax(Titolo t, tempo data1, tempo data2, int mode);

void bilanciaQuotazioni(Titolo t, int S);

TitoliList initList();
void printList(TitoliList lista);
// ritorna non il nodo corrspondente alla ricerca, ma direttamente l'ADT titolo
Titolo ListSearch(TitoliList lista, char code[MAX]);
// aggiunge in nodo in ordine di codice, e crea il bst quotazioni
void addNode(TitoliList lista, char code[MAX], Quotazione Quotazione);