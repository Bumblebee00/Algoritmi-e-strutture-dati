/*
Dato che il numero di vertici non è noto a priori usiamo una struttura dati ausiliaria per leggere il file, e mentre lo facciamo contiamo il numero di vertici e creiamo la tabella di simboli. Non ho voglia di fare una lista faccio un vettore magari sovrallocato e bom.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "grafo.h"
#define MAX 30

struct infoFile{
    int n_righe_max; // starts at 8 for example
    Edge* righe;
    int n_nodi;
    char** tab;
};

struct infoFile* infoFileInit(){
    struct infoFile* info = malloc(sizeof(struct infoFile));
    info->n_righe_max = 8;
    info->righe = malloc(sizeof(Edge) * 8);
    info->n_nodi = 0;
    info->tab = NULL;
    return info;
};

int addToInfoFile(FILE* fp, struct infoFile* info, int i){
    // reallocate space to store rows
    if (i==info->n_righe_max){
        info->n_righe_max *= 2;
        info->righe = realloc(info->righe, info->n_righe_max * sizeof(Edge));
    }
    char id_elab1[MAX];
    char id_elab2[MAX];
    if (fscanf(fp, "%s %*s %s %*s %d", id_elab1, id_elab2, &((info->righe)[i].wt)) !=3 ){ return 0; }

    // update tab
    int found = 0;
    for (int j=0; j<info->n_nodi; j++){
        if (strcmp(id_elab1, (info->tab)[j]) == 0){
            (info->righe)[i].v = j;
            found = 1;
            break;
        }
    }
    if (!found){
        (info->righe)[i].v = info->n_nodi;
        info->n_nodi++;
        info->tab = realloc(info->tab, sizeof(char*) * info->n_nodi);
        info->tab[info->n_nodi-1] = malloc(sizeof(char) * MAX);
        strcpy(info->tab[info->n_nodi-1], id_elab1);
    }
    found = 0;
    for (int j=0; j<info->n_nodi; j++){
        if (strcmp(id_elab2, (info->tab)[j]) == 0){
            (info->righe)[i].w = j;
            found = 1;
            break;
        }
    }
    if (!found){
        (info->righe)[i].w = info->n_nodi;
        info->n_nodi++;
        info->tab = realloc(info->tab, sizeof(char*) * info->n_nodi);
        info->tab[info->n_nodi-1] = malloc(sizeof(char) * MAX);
        strcpy(info->tab[info->n_nodi-1], id_elab2);
    }
    return 1;
}

int stampaMenu();

int main(int argc, char** argv){
    if (argc!=2){ printf("Usage: %s <path del grafo>", argv[0]); }
    // leggi file
    FILE* fp = fopen(argv[1], "r");
    struct infoFile* info = infoFileInit();
    int n_righe = 0;
    while (addToInfoFile(fp, info, n_righe)){ n_righe++; }
    printf("%d nodi, %d collegamenti\n", info->n_nodi, n_righe);

    // inizializza il grafico
    Graph g = GraphInit(info->n_nodi, info->tab);
    for (int i=0; i<n_righe; i++){InsertEdge(g, (info->righe)[i]); }

    int scelta;
    do{
        scelta = stampaMenu();
        switch (scelta)
        {
        case 1:
            CreaListaAdiacenza(g);
            break;

        case 2:
            printList(g, stdout);
            break;

        case 3:
            printMat(g, stdout);
            break;

        case 4:{
            printf("Inserisci l'indice di tre vertici, per controllare se sono adiacenti a coppie (questo metodo usa la matrice di adiacenza):");
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            if (controllaSottografoM(g, a, b, c)){
                printf("Si è un sottografo\n");
            } else { printf("No non è un sottografo\n"); }
            break;
        }
        
        case 5:{
            printf("Inserisci l'indice di tre vertici, per controllare se sono adiacenti a coppie (questo metodo usa la lista di adiacenza):");
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            if (controllaSottografoL(g, a, b, c)){
                printf("Si è un sottografo\n");
            } else { printf("No non è un sottografo\n"); }
            break;
        }

        default:
            break;
        }
    } while (scelta != 0);
}

int stampaMenu(){
    printf("\n0) Uscire\n");
    printf("1) Generare lista di adiacenza\n");
    printf("2) Stampa lista di adiacenza\n");
    printf("3) Stampa matrice di adiacenza\n");
    printf("4) Tre vertici sottografo completo, con matrice\n");
    printf("5) Tre vertici sottografo completo, con lista\n");
    printf("Inserire scelta: ");
    int x;
    scanf("%d", &x);
    return x;
}