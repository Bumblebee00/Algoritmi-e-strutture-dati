#include "main.h"

typedef struct node *link;
struct node {
    Item val;
    link next;
};

// insert a new node at the head of the list, and returns the new head. to create a new list, use NULL as head
link insertHead(link head, Item val);
// this function will insert the new node in a way to keep the list ordered by birthday
// it makes sense to use it only if the list is ordered by birthday
link insertOrderedBirthday(link head, Item val);
// linear search by code. Return the first node with the given code
link searchByCode(link head, char *code);
// delete the first node with the given code (and return it)
// the main has to dealocate the returned node
link deleteByCode(link head, char *code);
// the first node in the date interval is removed from the list, and returned
// date1 is after date2
link deleteByDateInterval(link head, char *date1, char *date2);

void freeList(link head);
int isBefore(char *a, char *b);