#include "inv.h"

void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp,"%d %d %d %d %d %d", &statp->hp, &statp->mp, &statp->atk, &statp->def, &statp->mag, &statp->spr);
}

// soglia è 1
void stat_print(FILE *fp, stat_t *statp, int soglia){
    if(statp->hp > soglia){fprintf(fp,"hp:%d ", statp->hp);}else{fprintf(fp,"hp:1 ");}
    if(statp->mp > soglia){fprintf(fp,"mp:%d ", statp->mp);}else{fprintf(fp,"mp:1 ");}
    if(statp->atk > soglia){fprintf(fp,"atk:%d ", statp->atk);}else{fprintf(fp,"atk:1 ");}
    if(statp->def > soglia){fprintf(fp,"def:%d ", statp->def);}else{fprintf(fp,"def:1 ");}
    if(statp->mag > soglia){fprintf(fp,"mag:%d ", statp->mag);}else{fprintf(fp,"mag:1 ");}
    if(statp->spr > soglia){fprintf(fp,"spr:%d ", statp->spr);}else{fprintf(fp,"spr:1 ");}
}

void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp,"%s %s", invp->nome, invp->tipo);
    stat_read(fp, &invp->stat);
}

void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp,"%-20s %-20s ", invp->nome, invp->tipo);
    stat_print(fp, &invp->stat, MIN_STAT);
}

stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}