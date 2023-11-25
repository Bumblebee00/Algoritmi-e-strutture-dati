#include "pg.h"

/* lettura e scrittura su file */
int pg_read(FILE *fp, pg_t *pgp){
    if (fscanf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe) != 3){
        return 0;
    }
    stat_read(fp, &pgp->b_stat);
    pgp->equip = equipArray_init();
    return 1;
}
/* non essendo struct dinamica, pulisce chiamando il distruttire di equipArray */
void pg_clean(pg_t *pgp){
    pgp->cod[0] = '\0';
    pgp->nome[0] = '\0';
    pgp->classe[0] = '\0';
    equipArray_free(pgp->equip);
    // non puliamo le statistiche ma vabbe
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    fprintf(fp, "%s %s %s ", pgp->cod, pgp->nome, pgp->classe);
    stat_print(fp, &pgp->b_stat);
    fprintf(fp, " ");
    stat_print(fp, &pgp->eq_stat);
    fprintf(fp, "\n");
    equipArray_print(fp, pgp->equip, invArray);
}
/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario:
chiamare l'opportuna funzione dal modulo equipArray
aggiorna eq_stat con quella base piu' gli effetti degli oggetti equipaggiati*/
void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip, invArray);
    pgp->eq_stat = pgp->b_stat;
    for (int i = 0; i < equipArray_inUse(pgp->equip); ++i) {
        pgp->eq_stat.hp += invArray_getByIndex(invArray, equipArray_getEquipByIndex(pgp->equip, i, invArray))->stat.hp;
        pgp->eq_stat.mp += invArray_getByIndex(invArray, equipArray_getEquipByIndex(pgp->equip, i, invArray))->stat.mp;
        pgp->eq_stat.atk += invArray_getByIndex(invArray, equipArray_getEquipByIndex(pgp->equip, i, invArray))->stat.atk;
        pgp->eq_stat.def += invArray_getByIndex(invArray, equipArray_getEquipByIndex(pgp->equip, i, invArray))->stat.def;
        pgp->eq_stat.mag += invArray_getByIndex(invArray, equipArray_getEquipByIndex(pgp->equip, i, invArray))->stat.mag;
        pgp->eq_stat.spr += invArray_getByIndex(invArray, equipArray_getEquipByIndex(pgp->equip, i, invArray))->stat.spr;
    }
}
