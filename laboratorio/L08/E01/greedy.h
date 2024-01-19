#include <stdlib.h>
#include <stdio.h>

#define  CMAX 100
#define DIAGS 3
#define MAXEL 5

typedef struct elemento_s{
    char name[CMAX];  // nome
    int tipo;         // tipo di diagonale
    int dir_ingresso;           // tipo di ingresso
    int dir_uscita;          // tipo di uscita
    int notFirst;     // diagonale non come prima mossa o meno
    int last;         // diagonale finale o meno
    float points;       // punteggio
    float dif;          // difficoltà
} elemento;

struct diagArr{
    elemento *vec; // vettore di elementi
    int nEl;
};

extern float DD;
extern float DP;

void MergeSortR(int *vec1, int *vec2, int l, int r, struct diagArr listaDiag);
void Merge(int *vec1, int *vec2, int l, int m, int r, struct diagArr listaDiag);
int mostDense(int x, int y, struct diagArr listaDiag);
void sortDensity(int nStart, struct diagArr listaDiag, int *startings);
void greedySol(struct diagArr listaDiag);
void printSol(int **solMat, struct diagArr listaDiag);
int **fillSolution(int *entries, int *elements, int nEl, int nStart, struct diagArr listaDiag);
void removeTooDiff(int *entries, int nStart, int *elements, int nEl, struct diagArr listaDiag);
int checkSolution(int **sol, float totDif, float *diagDif, struct diagArr listaDiag, int *dimDiag);
int isNextValid(struct diagArr listaDiag, int i, int j, float totDif, float diagDif);
