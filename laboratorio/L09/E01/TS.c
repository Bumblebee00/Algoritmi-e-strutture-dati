#include "TS.h"

struct TS_s {
    int N; // numero di elemnti massimo
    id *elementi;
};

id creaID(char nome){ id x; x.value = nome; return x; }
int confrontaID(id x, id y){ return x.value - y.value; }
void stampaID(id x){ printf("%c", x.value); }

TS inizializzaTS(int N){
    TS tabella = malloc(sizeof(struct TS_s));
    tabella->N = N;
    tabella->elementi = malloc(sizeof(id) * N);
    return tabella;
}

int TS_aggiungiElemento(TS tabella, id elemento, int indice){
    (tabella->elementi)[indice] = elemento;
    return 0;
}

id TS_getFromIndex(TS tabella, int index){ return (tabella->elementi)[index]; }

int TS_getFromId(TS tabella, id id){
    for (int i = 0; i < tabella->N; i++){
        if (confrontaID(id, (tabella->elementi)[i]) == 0){
            return i;
        }
    }
    return -1;
}

void stampaTS(TS t){
    printf("Tabella di adiacenza:\n");
    for (int i = 0; i < t->N; i++){
        printf("(%d, ", i); stampaID((t->elementi)[i]); printf(")\n");
    }
}