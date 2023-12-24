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

// se t1 è più recente di t2 return 1
// se t2 è più recente di t1 return -1
// se sono uguali return 0
int tempoCompare(tempo t1, tempo t2);
#endif