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

link deleteByCode(link *head, char *code){
    // this should never appen. just in case
    if (*head == NULL) { return NULL; }
    if (strcmp((*head)->val.codice, code)==0) {
        // head transforms into the element after head (it could be NULL)
        link headcp = *head;
        *head = (*head)->next;
        return headcp;
    }
    // head, ..., previous, toDelete, ..., NULL
    link previous = *head;
    for (;previous->next != NULL; previous=previous->next) {
        if (strcmp(previous->next->val.codice, code)==0){
            link toDelete = previous->next;
            previous->next = toDelete->next;
            return toDelete;
        }
    }
    return NULL;
}

// data1 è dopo data2
link deleteByDateInterval(link *head, char *date1, char *date2){
    link lastToKeep, firstToDelete, lastToDelete;
    int deleteHead = 0;
    lastToKeep = *head;
    // if also head should be deleted
    if (isBefore((*head)->val.dataNascita, date1)){
        // if list has lenght one, return the firs element (it will be freed)
        if ((*head)->next == NULL){
            link headcp = *head;
            *head = NULL;
            return headcp;
        }
        deleteHead = 1;
        firstToDelete = *head;
    } else {
        // head, ..., lastToKeep, firstToDelete, ... lastToDelete, ..., lastElement, NULL
        // loop up until you find the true lastToKeep (is not head)
        while(lastToKeep->next!=NULL && isBefore(date1, lastToKeep->next->val.dataNascita)){ lastToKeep = lastToKeep->next;}
        // no element to delete
        if (lastToKeep->next == NULL){ return NULL; }
        firstToDelete = lastToKeep->next;
    }
    // loop until you find the true lastToDelete
    lastToDelete = firstToDelete;
    while(lastToDelete->next!=NULL && isBefore(date2, lastToDelete->next->val.dataNascita)){ lastToDelete = lastToDelete->next;}

    if (deleteHead) {
        // if to delete all the list, 
        if (lastToDelete->next == NULL){
            link headcp = *head;
            *head = NULL;
            return headcp;
        }
        // head transforms into the element after lastToDelete
        *head = lastToDelete->next;
        lastToDelete->next = NULL;
    } else {
        // head, ..., previous, ..., lastElement, NULL
        lastToKeep->next = lastToDelete->next;
        // firstToDelete, ... lastToDelete, NULL
        lastToDelete->next = NULL;
    }
    return firstToDelete;
}

link freeList(link head){
    link temp;
    while (head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
    return head;
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