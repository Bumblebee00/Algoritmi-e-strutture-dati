#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef struct id_s {
    char value;
} id;
typedef struct TS_s* TS;

id creaID(char nome);
int confrontaID(id x, id y);
void stampaID(id x);

TS inizializzaTS(int N);
int TS_aggiungiElemento(TS tabella, id elemento, int indice); // 0 if succesful

id TS_getFromIndex(TS tabella, int index);
int TS_getFromId(TS tabella, id id); // -1 if not found

void stampaTS(TS t);