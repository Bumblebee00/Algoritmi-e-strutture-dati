#ifndef MAIN_H
#define MAIN_H
// atttività. ha un inizio e una fine
typedef struct { int inizio, fine; } att;
#endif

// prototipo per wrapper che trovi un sottoinsieme di attività compatibili che massimizza la somma delle durate. chiamerà la funzione ricorsiva per costruite il powerset.
void attSel(int n, att* v);
// funzione ricorsiva che crea il powerset, prunando se due set si sovrappongono
void powersetPruned(int pos, att* val, int* sol, int n, int* max, int *maxSol, att* lastSelected);
// criterio di pruning
int overlap(att*, att*);

// utility
int calculateDuration(int* sol, att* v, int n);
void printSubset(int* sol, att* val, int n);
att* leggiFile(char* path, int* n, att* v);