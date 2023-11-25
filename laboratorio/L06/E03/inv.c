#include "inv.h"

void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp, "%d %d %d %d %d %d",
         &statp->hp, &statp->mp, &statp->atk,
         &statp->def, &statp->mag, &statp->spr);
}

void stat_print(FILE *fp, stat_t *statp){
    // se la stat è positiva, stampala, altrimenti stampa 0
    fprintf(fp, "%d %d %d %d %d %d",
         statp->hp > 0 ? statp->hp : 0,
         statp->mp > 0 ? statp->mp : 0,
         statp->atk > 0 ? statp->atk : 0,
         statp->def > 0 ? statp->def : 0,
         statp->mag > 0 ? statp->mag : 0,
         statp->spr > 0 ? statp->spr : 0);
}

/* funzioni di input/output di un oggetto dell'inventario */
void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp, "%s %s", invp->nome, invp->tipo);
    stat_read(fp, &invp->stat);

}
void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp, "%s %s ", invp->nome, invp->tipo);
    stat_print(fp, &invp->stat);
}

/* ritorna il campo stat di un oggetto dell'inventario */
stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}