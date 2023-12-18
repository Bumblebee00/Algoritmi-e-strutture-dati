#include "titolo.h"
#include <stdio.h>

// titolo_s è un ADT di 1 classe, ma è anche usato come nodo della lista
struct titolo_s{
    char *code;
    Quotazioni quotazioni; // lista di quotazioni in giorni diversi
    Titolo next;
};

struct collezioneDiTitoli_s{
    Titolo head;
    int numTitoli;
};

int codeCompare(char *code1, char *code2);

Titoli initList(){
    Titoli list = malloc(sizeof(struct collezioneDiTitoli_s));
    list->head = NULL;
    list->numTitoli = 0;
    return list;
}

void printList(Titoli lista){
    printf("Numero di titoli: %d\n", lista->numTitoli);
    printf("Lista di titoli:\n");
    Titolo x;
    for (x = lista->head; x != NULL; x = x->next){
        printf("ciao\n");
        printf("%s\n", x->code);
    }
}

Titoli addNode(Titoli lista, char *code, Quotazione q){
    Titolo nuovoNodo = malloc(sizeof(struct titolo_s));

    nuovoNodo->code = code;
    nuovoNodo->quotazioni = BSTinit();
    BSTaddInLeaf(nuovoNodo->quotazioni, q);
    
    // if the list is empty
    if (lista->head == NULL){
        nuovoNodo->next = NULL;
        lista->head = nuovoNodo;
    }
    // if i have to insert in head
    else if (codeCompare(lista->head->code, code)>0){
        nuovoNodo->next = lista->head;
        lista->head = nuovoNodo;
    }
    else {
        Titolo x;
        for (x = lista->head; x->next != NULL && codeCompare(x->next->code, code)<0; x = x->next);

        nuovoNodo->next = x->next;
        x->next = nuovoNodo;
        
        free(x);
    }

    lista->numTitoli++;
    return lista;
}

// 0 if strings are equal
// >0 if code 1 is greater than code2
// <0 if code 1 is lower than code2
// alphanumeric codes of MAX charahcters (or less) like: ABC001, ABC002, ABC011
int codeCompare(char *code1, char *code2){
    int i;
    for (i=0; code1[i] != '\0' && code2[i] != '\0'; i++){
        if (code1[i] > code2[i]) return 1;
        if (code1[i] < code2[i]) return -1;
    }
    if (code1[i] == '\0' && code2[i] == '\0') return 0;
    if (code1[i] == '\0') return -1;
    return 1;
}