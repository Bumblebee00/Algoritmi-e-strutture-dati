// un ADT di I classe per il titolo e uno per collezione di titoli (a scelta se in un solo modulo o in due). Per la collezione di titoli si faccia uso di una lista ordinata (si usi il codice del titolo come chiave di ordinamento)
#include "quotazione.h"
#define MAX 20

typedef struct titolo_s* Titolo;
typedef struct collezioneDiTitoli_s* Titoli;

// aggiunge una nuova quotazione al bst (in foglia)
void updateTitolo(Titolo t, Quotazione Quotazione);

Titoli initList();
void printList(Titoli lista);
Titolo ListSearch(Titoli lista, char *code);
// aggiunge in nodo in ordine di codice, e crea il bst quotazioni
Titoli addNode(Titoli lista, char *code, Quotazione Quotazione);