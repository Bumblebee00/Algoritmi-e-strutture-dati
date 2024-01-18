#include "TS.h"
#include<stdio.h>

typedef struct arco_s { id from; id to; int wt; } Arco;
typedef struct grafo_s* Grafo;

Arco creaArco(id from, id to, int wt);

Grafo inizializzaGrafo(int N);
int cristallizzaGrafo(Grafo g); // non si potranno più aggiungere archi

int G_aggiungiInfoNodo(Grafo g, id info, int indice);
int G_aggiungiArco_ID(Grafo g, id from, id to, int weight); // aggiunge arco con id dei nodi
int G_rimuoviArco_ID(Grafo g, id from, id to); // rimuove arco con id dei nodi
int G_aggiungiArcoAM(Grafo g, Arco a); // aggiunge l'arco SOLO dalla matrice
int G_rimuoviArcoDaM(Grafo g, Arco a); // rimuove l'arco SOLO dalla matrice

int èDAG(Grafo g); // 1 è un DAG, 0 non è un DAG
id *G_IndividuaNodiSorgenti(Grafo g, int *n); // ritorna un array di id dei nodi sorgenti
int G_distanzaMassima(Grafo g, id from, id to); // ritorna la distanza massima tra due nodi

int getNumA(Grafo g);
id getIDfromIndex(Grafo g, int index);
Arco getArco_int(Grafo g, int i); // ottiene arco con indice delgi archi

void stampaGrafo(Grafo g, FILE *fp);