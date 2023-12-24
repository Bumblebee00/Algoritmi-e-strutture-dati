#include "titolo.h"

struct titolo_s{
    char code[MAX];
    Quotazioni quotazioni; // lista di quotazioni in giorni diversi
};

struct collezioneDiTitoli_s{
    link head;
    int numTitoli;
};

void updateTitolo(Titolo t, Quotazione q){
    BSTaddInLeaf(t->quotazioni, q);
}

void printTitolo(Titolo t){
    printf("%s, ", t->code);
    printBST(t->quotazioni);
}

void Strcpy(char destination[MAX], char source[MAX]){
    for (int i=0; i<MAX && source[i]!='\0'; i++){
        destination[i] = source[i];
    }
}

Titolo creaTitolo(char code[MAX], Quotazione q){
    Titolo x = malloc(sizeof(struct titolo_s));
    Strcpy(x->code, code);
    Quotazioni bst = BSTinit();
    BSTaddInLeaf(bst, q);
    x->quotazioni = bst;
    return x;
}

int codeCompare(char code1[MAX], char code2[MAX]);

TitoliList initList(){
    TitoliList list = malloc(sizeof(struct collezioneDiTitoli_s));
    list->head = NULL;
    list->numTitoli = 0;
    return list;
}

void printList(TitoliList lista){
    printf("[");
    link x;
    for (x = lista->head; x != NULL; x = x->next){printf("%s, ", x->titolo->code);}
    printf("] (%d titoli)\n", lista->numTitoli);
}

void addNode(TitoliList lista, char code[MAX], Quotazione q){
    link nuovoNodo = malloc(sizeof(struct listNode_s));

    nuovoNodo->titolo = creaTitolo(code, q);

    // if the list is empty
    if (lista->head == NULL){
        nuovoNodo->next = NULL;
        lista->head = nuovoNodo;
    }
    // if i have to insert in head
    else if (codeCompare(lista->head->titolo->code, code)>0){
        nuovoNodo->next = lista->head;
        lista->head = nuovoNodo;
    }
    else {
        link x;
        for (x = lista->head; x->next != NULL && codeCompare(x->next->titolo->code, code)<0; x = x->next);

        nuovoNodo->next = x->next;
        x->next = nuovoNodo;
    }

    lista->numTitoli++;
}

Titolo ListSearch(TitoliList lista, char code[MAX]){
    if (lista->head == NULL){ return NULL; }
    link x;
    for (x = lista->head; x != NULL; x = x->next){
        if (codeCompare(x->titolo->code, code)==0)
            return x->titolo;
    }
    return NULL;
}

Quotazione SearchQuotazione(Titolo t, tempo data){
    return BSTsearch(t->quotazioni, data);
}

Quotazione SearchMax(Titolo t, tempo data1, tempo data2, int mode){
    return searchMaxValoreBST(t->quotazioni, data1, data2, mode);
}

void bilanciaQuotazioni(Titolo t, int S){
    int d = 999;//deltaMaxCammino(t->quotazioni);
    if (d>S){
        bilanciaBST(t->quotazioni);
    }
}

// 0 if strings are equal
// >0 if code 1 is greater than code2
// <0 if code 1 is lower than code2
// alphanumeric codes of MAX charahcters (or less) like: ABC001, ABC002, ABC011
int codeCompare(char code1[MAX], char code2[MAX]){
    int i;
    for (i=0; code1[i] != '\0' && code2[i] != '\0'; i++){
        if (code1[i] > code2[i]) return 1;
        if (code1[i] < code2[i]) return -1;
    }
    if (code1[i] == '\0' && code2[i] == '\0') return 0;
    if (code1[i] == '\0') return -1;
    return 1;
}