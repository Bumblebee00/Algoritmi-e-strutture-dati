#include "main.h"

typedef struct node *link;
struct node {
    Item val;
    link next;
};

link newList(Item val);
link insertHead(link listNode, Item val);
// this function will insert the new node in a way to keep the list ordered by birthday
// it makes sense to use it only if the list is ordered by birthday
link insertOrderedBirthday(link listNode, Item val);
// linear search by code. Return the first node with the given code
link searchByCode(link listNode, char *code);
// delete the first node with the given code (and return it)
link deleteByCode(link listNode, char *code);
// the first node in the date interval is removed from the list, and returned
link deleteByDateInterval(link listNode, char *date1, char *date2);

void freeList(link listNode);
int isBefore(Item a, Item b);