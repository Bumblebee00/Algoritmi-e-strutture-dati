#include<stdlib.h>
#include<stdio.h>
#include "grafo.h"

typedef struct node* link;
struct node{
    int v;
    int wt;
    link next;
};

struct graph{
    int N; // n. di vertici
    int E; // n. di archi
    int **M; // matrice di adiacenza
    link *ladj; // lista di adiacenza
    char** tab; // tablella di simboli, che per adesso sarà un semplice vettore di stringhe
};


Graph GraphInit(int N, char** tab){
    struct graph *g = malloc(sizeof(struct graph));
    g->N = N;
    g->E = 0;
    g->M = malloc(sizeof(int*) * N);
    for (int i=0; i<N; i++){
        (g->M)[i] = calloc(N, sizeof(int));
    }
    g->tab = tab;
    return g;
}

void GraphFree(Graph g){
    for (int i=0; i<g->N; i++){
        free((g->M)[i]);
    }
    free(g->M);
    free(g->tab);
}

void InsertEdge(Graph g, Edge e){
    (g->M)[e.v][e.w] = e.wt;
    (g->M)[e.w][e.v] = e.wt;
    g->E++;
}

void printMat(Graph g, FILE* out){
    fprintf(out, "                 "); for (int i=0; i<g->N; i++){ fprintf(out, "%-2d ", i); } fprintf(out, "\n");
    fprintf(out, "               ╭-------------------------------------------\n");
    for (int i=0; i<g->N; i++){
        fprintf(out, "%-2d) %-10s | ",i, (g->tab)[i]);
        for (int j=0; j<g->N; j++){
            fprintf(out, "%-2d ",(g->M)[i][j]);
        }
        fprintf(out, "\n");
    }
}

link ListAddNode(link head, int weight, int i_node){
    if (head == NULL){
        head = malloc(sizeof(struct node));
        head->wt = weight;
        head->v = i_node;
        head->next=NULL;
        return head;
    }
    if (head->next==NULL){
        head->next = malloc(sizeof(struct node));
        head->next->wt = weight;
        head->next->v = i_node;
        return head;
    }
    link x;
    for (x = head; x->next!=NULL; x = x->next);
    x->next = malloc(sizeof(struct node));
    x->next->wt = weight;
    x->next->v = i_node;

    return head;
}

void printList(Graph g, FILE* out){
    if (g->ladj == NULL){ printf("Lista di adiacenza non presente\n"); return; }
    for (int i=0; i<g->N; i++){
        fprintf(out, "%-2d) %-10s | ", i, (g->tab)[i]);
        link head = (g->ladj)[i];
        if (head == NULL){
            printf("Lista vuota\n");
        } else{
            printf("[");
            link x = head;
            do{
                printf("(el:%d, wt:%d), ", x->v, x->wt);
                x = x->next;
            } while(x != NULL);
            printf("]\n");
        }
    }
}

void CreaListaAdiacenza(Graph g){
    g->ladj = malloc(sizeof(link)*g->N);
    for (int i=0; i<g->N; i++){
        for (int j=0; j<g->N; j++){
            if ((g->M)[i][j]!=0){ (g->ladj)[i] = ListAddNode((g->ladj)[i], (g->M)[i][j], j); }
        }
    }
}

// controlla se a è collegato a b, b è collegato a c, e c è collegato a a
int controllaSottografoM(Graph g, int a, int b, int c){
    return (g->M)[a][b] && (g->M)[b][c] && (g->M)[c][a];
}

int controllaSottografoL(Graph g, int a, int b, int c){
    if (g->ladj == NULL){ CreaListaAdiacenza(g); }
    int founda = 0, foundb = 0, foundc = 0;
    link head = (g->ladj)[a];
    if (head==NULL){ return 0; }
    link x = head;
    do{
        if (x->v == b){ foundc = 1; }
        if (x->v == c){ foundb = 1; }
        x = x->next;
    } while (x!=NULL);
    head = (g->ladj)[b];
    if (head==NULL){ return 0; }
    x = head;
    do{
        if (x->v == c){ founda = 1; }
        x = x->next;
    } while (x!=NULL);
    return founda && foundb && foundc;
}