#ifndef TEMPO_H
#define TEMPO_H
// quasi ADT per data e ora
struct tempo_s {
    int anno;
    int mese;
    int giorno;
    int ore;
    int minuti;
};

typedef struct tempo_s* tempo;

int tempoCompare(tempo t1, tempo t2);
#endif