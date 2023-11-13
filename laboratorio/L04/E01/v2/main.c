#include<stdio.h>
#include<stdlib.h>
#include "main.h"

int main(){
    int N, E; // numero di nodi e numero di archi
    FILE *fp = fopen("grafo.txt", "r");
    if (fp == NULL){ printf("Non sono riuscito a aprire grafo.txt"); }
    fscanf(fp, "%d %d\n", &N, &E);

    Arco archi[E];
    for (int i=0; i<E; i++){ fscanf(fp, "%d %d\n", &archi[i].u, &archi[i].v); }
    fclose(fp);

    powerset(N, archi, E);
}

void powerset(int N, Arco *archi, int E){
    for (int i=0; i<(1<<N); i++){
        link set = NULL;

        for (int j=0; j<N; j++){
            // (i>>j)&1 is the i-th binary digit of i
            if ((i>>j)&1){
                set = newNode(j, set);
            }
        }
        if (isVertexCover(archi, E, set)){
            printList(set);
        }
        freeList(set);
    }
}

int isVertexCover(Arco *archi, int E, link head){
    link temp;
    for (int i=0; i<E; i++){
        temp = head;
        int edgeIsConnected = 0;
        while (temp != NULL){
            if(archi[i].u == temp->val || archi[i].v == temp->val){
                edgeIsConnected = 1;
                break;
            }
            temp = temp->next;
        }
        if (!edgeIsConnected){ return 0; }
    }
    return 1;
}