#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

link newList(Item val){
    link head = malloc(sizeof(struct node));
    if (head==NULL){ printf("Memory allocation failed"); return; }
    head->val = val;
    head->next = NULL;
    return head;
}

link insertHead(link head, Item val){
    link tmp = malloc(sizeof(struct node));
    if (tmp==NULL){ printf("Memory allocation failed"); return; }
    tmp->val = val;
    tmp->next = head;
    return tmp;
}

link insertOrderedBirthday(link head, Item val){
    link x;
    for (x=head; isBefore(x->val, val); x=x->next);
    if (x==head){ return insertHead(head, val); }
    link tmp = malloc(sizeof(struct node));
    if (tmp==NULL){ printf("Memory allocation failed"); return; }
    tmp->val = val;
    tmp->next = x->next;
    x->next = tmp;
    return head;
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
if equal, return 0
if not before, return -1
*/
int isBefore(Item a, Item b){
    int y1, m1, d1, y2, m2, d2;
    sscanf(a.dataNascita, "%d/%d/%d", &y1, &m1, &d1);
    sscanf(b.dataNascita, "%d/%d/%d", &y2, &m2, &d2);
    if (y1 < y2){ return 1;}
    else if (y1 == y2){
        if (m1 < m2){ return 1; }
        else if (m1 == m2){
            if (d1 < d2){ return 1; }
            else if (d1 == d2){
                return 0;
            } else { return -1; }
        } else { return -1; }
    } else { return -1; }
}