typedef struct edge { int v; int w; int wt; } Edge;
typedef struct graph *Graph;

Graph GraphInit(int N, char** tab);
void GraphFree(Graph g);

void printMat(Graph g, FILE* out);
void printList(Graph g, FILE* out);

void InsertEdge(Graph g, Edge e);
void CreaListaAdiacenza(Graph g);

int controllaSottografoM(Graph g, int a, int b, int c);
int controllaSottografoL(Graph g, int a, int b, int c);