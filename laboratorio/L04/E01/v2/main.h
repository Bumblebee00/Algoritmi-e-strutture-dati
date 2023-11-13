#include "lists.h"

typedef struct {int u; int v; } Arco;

void powerset(int N, Arco *archi, int E);
int isVertexCover(Arco *archi, int E, link head);