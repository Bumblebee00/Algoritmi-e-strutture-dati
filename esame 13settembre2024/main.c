#include<stdio.h>
#include "strutture.h"

int main(){
    ELENCO e;
    DISTMATR m;
    FILE* fp = fopen("input.txt", "r");
    caricaDATI(fp, &e, &m);
}