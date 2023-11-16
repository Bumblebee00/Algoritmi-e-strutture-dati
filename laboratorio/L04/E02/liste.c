#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "liste.h"

link insertHead(link head, Item val){
    link tmp = malloc(sizeof(struct node));
    if (tmp==NULL){ printf("Memory allocation failed"); return NULL; }
    tmp->val = val;
    tmp->next = head;
    return tmp;
}

link insertOrderedBirthday(link head, Item val){
    // if the list is empty or the new node should be inserted at the head, call insertHead
    if (head==NULL || isBefore(head->val.dataNascita, val.dataNascita)){ return insertHead(head, val); }
    // otherwise loop up to the node (x) that should go before the new node (or the end of the list)
    link x=head;
    while (x->next!= NULL && isBefore(val.dataNascita, x->next->val.dataNascita)){ x=x->next; }
    // insert the new node after x
    link tmp = malloc(sizeof(struct node));
    if (tmp==NULL){ printf("Memory allocation failed"); return NULL; }
    tmp->val = val;
    tmp->next = x->next;
    x->next = tmp;
    return head;
}

// TODO: fare il for figo
link searchByCode(link head, char *code){
    if (head == NULL) { return NULL; }
    link x;
    for (x=head; x!=NULL; x=x->next) { if (strcmp(x->val.codice, code)==0) { return x; } }
    return NULL;
}

link deleteByCode(link head, char *code){
    // version 1
    // if (head == NULL) { return NULL; }
    // link x, prev;
    // for (x=head, prev=NULL; x!=NULL; prev=x, x=x->next) { if (strcmp(x->val.codice, code)==0) { break; } }
    // if (x==NULL) { return NULL; }
    // if (prev==NULL) { head = x->next; }
    // else { prev->next = x->next; }
    // return x;
    // version 2
    if (head == NULL) { return NULL; }
    if (strcmp(head->val.codice, code)==0) {
        // we have to use these two temporaney variables, because the main keeps the pointer to the same head
        link headCopy = insertHead(NULL, head->val);
        link second = head->next;
        head->val = second->val;
        head->next = second->next;
        free(second);
        return headCopy;
    }
    // head, ..., previous, toDelete, ..., NULL
    link previous = head;
    for (;previous->next != NULL; previous=previous->next) {
        if (strcmp(previous->next->val.codice, code)==0){
            link toDelete = previous->next;
            previous->next = toDelete->next;
            return toDelete;
        }
    }
    return NULL;
}

// TODO: find the error
link deleteByDateInterval(link head, char *date1, char *date2){
    link previous=head;
    // loop up until previous->next should be deleted
    while(isBefore(date1, previous->next->val.dataNascita)){ previous = previous->next;}
    link toDelete = previous->next;
    // head, ..., previous, toDelete, ...
    while(previous->next != NULL && isBefore(date2, previous->next->val.dataNascita)){
        link tmp = previous->next;
        previous->next=tmp->next;
        // print element
        free(tmp);
        previous = previous->next;
    }
    return NULL;
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
a and b are date in strings in format "gg/mm/aaaa"
if a is before b, return 1
if not before, return 0
*/
int isBefore(char *a, char *b){
    int y1, m1, d1, y2, m2, d2;
    sscanf(a, "%d/%d/%d", &d1, &m1, &y1);
    sscanf(b, "%d/%d/%d", &d2, &m2, &y2);
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