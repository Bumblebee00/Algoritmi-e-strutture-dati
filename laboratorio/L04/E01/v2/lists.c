#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

link newNode(int graphNode, link head) {
    if (head==NULL){
        link node = malloc(sizeof(struct node));
        if (node==NULL){ printf("Memory allocation failed"); }
        node->val = graphNode;
        node->next = NULL;
        return node;
    } else {
        head->next = newNode(graphNode, head->next);
        return head;
    }
}

void freeList(link head){
    link temp;
    while (head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}

void printList(link head){
    printf("{");
    while (head != NULL){
        printf("%d", head->val);
        if (head->next != NULL) { printf(", "); }
        head = head->next;
    }
    printf("}\n");
}