#include<stdio.h>
#include<stdlib.h>

typedef struct {int u; int v; } Arco;

// prototipi
void trovaVertexCover(int N, Arco *archi);
void trovaVertexCoverR(int N, Arco *archi, int iE, int *mark);

int N; // numero di vertici del grafo
int E; // numero di archi del grafo
int **foundVertexCovers;
int foundVertexCovers_size = 1;

int main(){
    FILE *fp = fopen("grafo.txt", "r");
    if (fp == NULL){ printf("Non sono riuscito a aprire grafo.txt"); }
    fscanf(fp, "%d %d\n", &N, &E);

    Arco archi[E];
    for (int i=0; i<E; i++){ fscanf(fp, "%d %d\n", &archi[i].u, &archi[i].v); }
    fclose(fp);

    foundVertexCovers = malloc(sizeof(int*));
    foundVertexCovers[0] = malloc(sizeof(int));
    foundVertexCovers[0][0] = -1;
    
    trovaVertexCover(N, archi);

    printf("Trovati %d vertex cover:\n", foundVertexCovers_size);
    for (int i=0; i<foundVertexCovers_size; i++){
        printf("Vertex cover %d: ", i+1);
        for (int j=0; foundVertexCovers[i][j] != -1; j++){
            printf("%d ", foundVertexCovers[i][j]);
        }
        printf("\n");
    }
}

// wrapper 😎
void trovaVertexCover(int N, Arco *archi){
    int mark[N]; // a vector that represents if the node is already counted (1) or not (0)
    for (int i=0; i<N; i++){ mark[i] = 0; }
    
    trovaVertexCoverR(N, archi, 0, mark);
}

void trovaVertexCoverR(int N, Arco *archi, int iE, int *mark){
    if (iE >= N){
        int tmp[N];
        int tmpLenght = 0;
        for (int i=0; i<N; i++){
            if (mark[i]>0){
                tmp[tmpLenght] = i;
                tmpLenght++;
            }
        }

        // check if the vertex cover is already in the list
        int notFound = 1;
        for (int i=0; i<foundVertexCovers_size; i++){
            int found = 1;
            for (int j=0; foundVertexCovers[i][j] != -1; j++){
                if (foundVertexCovers[i][j] != tmp[j]){
                    found = 0;
                    break;
                }
            }
            if (found){
                notFound = 0;
                break;
            }
        }
        if (notFound){
            foundVertexCovers_size++;
            foundVertexCovers = realloc(foundVertexCovers, sizeof(int*) * foundVertexCovers_size);
            foundVertexCovers[foundVertexCovers_size-1] = malloc(sizeof(int)*(tmpLenght+1));
            for (int i=0; i<tmpLenght; i++){
                foundVertexCovers[foundVertexCovers_size-1][i] = tmp[i];
            }
            foundVertexCovers[foundVertexCovers_size-1][tmpLenght] = -1;
        }
    } else {

        int verticePartenza = archi[iE].u;
        int verticeArrivo  = archi[iE].v;

        iE++;

        mark[verticePartenza]++;
        trovaVertexCoverR(N, archi, iE, mark);

        mark[verticePartenza]--;
        mark[verticeArrivo]++;
        trovaVertexCoverR(N, archi, iE, mark);
        mark[verticeArrivo]--;
    }
}