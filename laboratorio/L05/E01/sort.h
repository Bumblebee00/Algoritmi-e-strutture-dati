#include "main.h"

// wrapper 😎. ordina per tempo di inizio crescente le attività
void MergeSort(att *v, int n);
// funzione ricorsiva
void MergeSortR(att *v, att *help, int l, int r);
// unisce i due vettori ordinati
void Merge(att *v, att *help, int l, int m, int r);