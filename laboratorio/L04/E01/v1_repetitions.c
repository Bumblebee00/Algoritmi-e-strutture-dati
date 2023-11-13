#include<stdio.h>

typedef struct {int u; int v; } Arco;

// prototipi
void trovaVertexCover(int N, Arco *archi);
void trovaVertexCoverR(int N, Arco *archi, int iE, int *mark);

int N; // numero di vertici del grafo
int E; // numero di archi del grafo


int main(){
    FILE *fp = fopen("grafo.txt", "r");
    if (fp == NULL){ printf("Non sono riuscito a aprire grafo.txt"); }
    fscanf(fp, "%d %d\n", &N, &E);

    Arco archi[E];
    for (int i=0; i<E; i++){ fscanf(fp, "%d %d\n", &archi[i].u, &archi[i].v); }
    fclose(fp);

    trovaVertexCover(N, archi);
}

// wrapper 😎
void trovaVertexCover(int N, Arco *archi){
    int mark[N]; // a vector that represents if the node is already counted (1) or not (0)
    for (int i=0; i<N; i++){ mark[i] = 0; }
    
    trovaVertexCoverR(N, archi, 0, mark);
}

void trovaVertexCoverR(int N, Arco *archi, int iE, int *mark){
    if (iE >= N){
        printf("Found Vertex cover: (");
        for (int i=0; i<N; i++){
            if (mark[i] > 0)
                printf("%d, ", i);
        }
        printf(")\n");
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