typedef struct node *link;
struct node {
    int val;
    link next;
};

link newNode(int graphNode, link listNode);
void freeList(link listNode);
void printList(link listNode);