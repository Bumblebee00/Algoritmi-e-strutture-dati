#include "tempo.h"

int tempoCompare(tempo t1, tempo t2){
    if (t1->anno > t2->anno){
        return 1;
    } else if (t1->anno < t2->anno){
        return -1;
    } else {
        if (t1->mese > t2->mese){
            return 1;
        } else if (t1->mese < t2->mese){
            return -1;
        } else {
            if (t1->giorno > t2->giorno){
                return 1;
            } else if (t1->giorno < t2->giorno){
                return -1;
            } else {
                if (t1->ore > t2->ore){
                    return 1;
                } else if (t1->ore < t2->ore){
                    return -1;
                } else {
                    if (t1->minuti > t2->minuti){
                        return 1;
                    } else if (t1->minuti < t2->minuti){
                        return -1;
                    } else {
                        return 0;
                    }
                }
            }
        }
    }
}