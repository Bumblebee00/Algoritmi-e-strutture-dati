#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "liste.h"

link newList(Item val){
    link head = malloc(sizeof(struct node));
    if (head==NULL){ printf("Memory allocation failed"); return NULL; }
    head->val = val;
    head->next = NULL;
    return head;
}

link insertHead(link head, Item val){
    link tmp = malloc(sizeof(struct node));
    if (tmp==NULL){ printf("Memory allocation failed"); return NULL; }
    tmp->val = val;
    tmp->next = head;
    return tmp;
}

link insertOrderedBirthday(link head, Item val){
    if (head==NULL || isBefore(head->val, val)){ return insertHead(head, val); }
    link x=head;
    while (x->next!= NULL && isBefore(val, x->next->val)){ x=x->next; }
    link tmp = malloc(sizeof(struct node));
    if (tmp==NULL){ printf("Memory allocation failed"); return NULL; }
    tmp->val = val;
    tmp->next = x->next;
    x->next = tmp;
    return head;
}

link searchByCode(link head, char *code){
    if (head == NULL) { return NULL; }
    link x;
    for (x=head; x!=NULL; x=x->next) { if (strcmp(x->val.codice, code)==0) { return x; } }
    return NULL;
}

// cancellazione (con estrazione del dato) di un elemento dalla lista, previa ricerca per codice
link deleteByCode(link head, char *code){
    if (head == NULL) { return NULL; }
    link x, prev;
    for (x=head, prev=NULL; x!=NULL; prev=x, x=x->next) { if (strcmp(x->val.codice, code)==0) { break; } }
    if (x==NULL) { return NULL; }
    if (prev==NULL) { head = x->next; }
    else { prev->next = x->next; }
    return x;
}

void freeList(link head){
    link temp;
    while (head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}

/*
if a is before b, return 1
if not before, return 0
*/
int isBefore(Item a, Item b){
    int y1, m1, d1, y2, m2, d2;
    sscanf(a.dataNascita, "%d/%d/%d", &d1, &m1, &y1);
    sscanf(b.dataNascita, "%d/%d/%d", &d2, &m2, &y2);
    if (y1 < y2){ return 1;}
    else if (y1 == y2){
        if (m1 < m2){ return 1; }
        else if (m1 == m2){
            if (d1 < d2){ return 1; }
            else if (d1 == d2){
                return 0;
            } else { return 0; }
        } else { return 0; }
    } else { return 0; }
}