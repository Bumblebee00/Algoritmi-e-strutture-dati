#include "greedy.h"

void MergeSortR(int *array1, int *array2, int left, int right, struct diagArr diagList) {
    int middle;

    if (left >= right)
        return;

    middle = (left + right) / 2;

    MergeSortR(array1, array2, left, middle, diagList);
    MergeSortR(array1, array2, middle + 1, right, diagList);
    Merge(array1, array2, left, middle, right, diagList);
}

void Merge(int *array1, int *array2, int left, int middle, int right, struct diagArr diagList) {
    int i, j, k;

    i = left; // indice del sottoarray sinistro
    j = middle + 1; // indice del sottoarray destro

    for (k = left; k <= right; k++) {
        if (i > middle)
            array2[k] = array1[j++];
        else if (j > right)
            array2[k] = array1[i++];
        else if (mostDense(array1[i], array1[j], diagList))
            array2[k] = array1[i++];
        else
            array2[k] = array1[j++];
    }

    for (k = 0; k <= right; k++)
        array1[k] = array2[k];
}

int mostDense(int x, int y, struct diagArr diagList) {
    elemento el1 = diagList.vec[x];
    elemento el2 = diagList.vec[y];

    return (el1.points / el1.dif > el2.points / el2.dif);
}

void sortDensity(int nStart, struct diagArr diagList, int *startings) {
    int *helper = calloc(nStart, sizeof(int));
    MergeSortR(startings, helper, 0, nStart - 1, diagList);
}

/*
Strategia greedy:
- Ordino gli elementi in base alla densità (punteggio/difficoltà).
- Scelgo gli elementi più densi per le prime mosse.
- Per ogni elemento scelto, scelgo il successivo più denso che sia compatibile con l'elemento precedente.
- Se non ci sono elementi compatibili, scelgo l'elemento più denso tra quelli rimasti.
- Ripeto finché non ho riempito tutte le diagonali o non ci sono più elementi.
*/
void greedySol(struct diagArr diagList) {
    int *entries = NULL;
    int *elements = NULL;
    int **solution = NULL;
    int nStart = 0; // Numero di elementi che possono essere scelti come prima mossa
    int nEl = 0; // Numero di elementi che possono essere scelti come seconda mossa
    int j = 0, k = 0;

    // rimuove gli elementi troppo difficili
    removeTooDiff(entries, nStart, elements, nEl, diagList);

    // crea i vettori entries e elements
    for (int i = 0; i < diagList.nEl; i++) {
        if (diagList.vec[i].notFirst == 0)
            nStart++;
        else
            nEl++;
    }
    entries = calloc(nStart, sizeof(int));
    elements = calloc(nEl, sizeof(int));
    for (int i = 0; i < diagList.nEl; i++) {
        if (diagList.vec[i].notFirst == 0) {
            entries[j++] = i;
        }
        else {
            elements[k++] = i;
        }
    }

    // ordina entries e elements in base alla densità
    sortDensity(nEl, diagList, elements);
    sortDensity(nStart, diagList, entries);

    // riempe entries e elements con gli elementi compatibili come descritto sopra
    solution = fillSolution(entries, elements, nEl, nStart, diagList);

    printSol(solution, diagList);

    // controlla se la soluzione è valida
    float totDif = 0;
    float diagDif[DIAGS] = {0};
    int dimDiags[DIAGS] = {0};
    for (int i = 0; i < DIAGS; i++) {
        for (int j = 0; j < MAXEL && solution[i][j] != -1; j++) {
            totDif += diagList.vec[solution[i][j]].dif;
            diagDif[i] += diagList.vec[solution[i][j]].dif;
            dimDiags[i]++;
        }
    }
    
    // if (checkSolution(solution, totDif, diagDif, diagList, dimDiags)){ printf("Soluzione valida\n"); }
    // else{ printf("Purtroppo la soluzione non è valida\n"); }

    free(elements);
    free(entries);
    for (int i = 0; i < DIAGS; i++)
        free(solution[i]);
    free(solution);
}

/*
REGOLE:
- Ci devono essere 3 diagonali, ciascuna con almeno un elemento.
- Ogni diagonale deve avere almeno un elemento acrobatico.
- Deve esserci almeno un elemento acrobatico in avanti e uno all'indietro nel programma.
- Almeno una diagonale deve avere due elementi acrobatici consecutivi.
- Se un elemento ha difficoltà 8 o più, il punteggio della diagonale viene moltiplicato per 1.5.
- Massimo 5 elementi per diagonale.
- La difficoltà totale delle diagonali deve essere inferiore a DD.
- La difficoltà totale del programma deve essere inferiore a DP.
*/
int **fillSolution(int *startElements, int *acrobaticElements, int numAcrobaticElements, int numStartElements, struct diagArr diagList) {
    int **solutionMatrix = (int **)calloc(DIAGS, sizeof(int *));
    float totalDifficulty = 0;
    float diagDifficulty[DIAGS] = {0};
    int diagDimensions[DIAGS] = {0};

    for (int i = 0; i < DIAGS; i++){ solutionMatrix[i] = calloc(MAXEL, sizeof(int)); }

    for (int i = 0; i < DIAGS; i++)
        for (int j = 0; j < MAXEL; j++)
            solutionMatrix[i][j] = -1;

    // Fill the first element with the cheapest start element to ensure the presence of an acrobatic sequence
    for (int i = 0; i < DIAGS; i++) {
        solutionMatrix[i][0] = startElements[numStartElements - i - 1];
        totalDifficulty += diagList.vec[solutionMatrix[i][0]].dif;
        diagDifficulty[i] += diagList.vec[solutionMatrix[i][0]].dif;
        diagDimensions[i]++;
    }

    // Fill the remaining elements
    for (int i = 0; i < DIAGS && totalDifficulty < DP; i++) {
        for (int j = 1; j < MAXEL && diagDifficulty[i] < DD; j++) {
            for (int k = 0; k < numAcrobaticElements && solutionMatrix[i][j] == -1; k++) {
                if (acrobaticElements[k] != -1 && isNextValid(diagList, solutionMatrix[i][j - 1], acrobaticElements[k], totalDifficulty, diagDifficulty[i])){
                    solutionMatrix[i][j] = acrobaticElements[k];
                    totalDifficulty += diagList.vec[solutionMatrix[i][j]].dif;
                    diagDifficulty[i] += diagList.vec[solutionMatrix[i][j]].dif;
                    diagDimensions[i]++;
                }
            }
            if (diagList.vec[solutionMatrix[i][j]].last == 1){ break; }
        }
    }
    return solutionMatrix;
}


int isNextValid(struct diagArr diagList, int i, int j, float totDif, float diagDif) {
    if (diagList.vec[j].dir_ingresso == diagList.vec[i].dir_uscita && diagDif + diagList.vec[j].dif <= DD &&
        diagDif + diagList.vec[j].dif <= DD && diagList.vec[i].last != 1)
        return 1;
    return 0;
}

void printSol(int **solMat, struct diagArr diagList) {
    printf("Soluzione trovata con approccio greedy:\n");
    float points = 0;
    for (int i = 0; i < DIAGS; i++) {
        printf("Diagonale %d:\n", i + 1);
        for (int j = 0; j < MAXEL && solMat[i][j] != -1; j++) {
            printf("%d) %s %.2f\n", j + 1, diagList.vec[solMat[i][j]].name, diagList.vec[solMat[i][j]].points);
            points += diagList.vec[solMat[i][j]].points;
        }
    }
    printf("Punteggio totale: %.2f\n\n", points);
}

void removeTooDiff(int *entries, int nStart, int *elements, int nEl, struct diagArr diagList) {
    for (int i = 0; i < nStart; i++) {
        if (diagList.vec[entries[i]].dif + diagList.vec[elements[nEl - 1]].dif > DD)
            entries[i] = -1;
    }

    for (int i = 0; i < nEl; i++) {
        if (diagList.vec[elements[i]].dif > DD)
            elements[i] = -1;
    }
}

int checkSolution(int **sol, float totDif, float *diagDif, struct diagArr diagList, int *dimDiag) {
    int acroBack = 0, acroFront = 0, acroSeq = 0;

    for (int i = 0; i < DIAGS; i++) {
        for (int j = 0; j < dimDiag[i]; j++) {
            if (diagList.vec[sol[i][j]].tipo == 1)
                acroBack = 1;

            if (diagList.vec[sol[i][j]].tipo == 2)
                acroFront = 1;
        }

        if (dimDiag[i] > 1)
            acroSeq = 1;
    }

    if (acroFront && acroBack && acroSeq)
        return 1;

    return 0;
}