#include<stdlib.h>
#define n_pietre 4

enum Pietra { ZAFFIRO, RUBINO, TOPAZIO, SMERALDO };

typedef struct node* link;

struct node{
    int mark[n_pietre];
    int key; // z + r + t + s
    int maxLenght; // result of computation
    link next;
};

link insertOrdinato(link head, int mark[n_pietre], int maxLenght);
/*
Ricerca dicotomica nella lista ordinata
ritorna -1 se l'elemento non è stato trovato, maxLenght se è stato trovato
*/
int find(link head, int mark[n_pietre]);