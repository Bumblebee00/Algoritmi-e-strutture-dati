#include "pg.h"

int pg_read(FILE *fp, pg_t *pgp){
    if (fscanf(fp, "%s %s %s ", pgp->cod, pgp->nome, pgp->classe) != 3){
        return 0;
    }
    stat_read(fp, &pgp->b_stat);
    pgp->eq_stat = pgp->b_stat;
    pgp->equip = equipArray_init();
    return 1;
}

void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    fprintf(fp, "╭─%s %s %s\n", pgp->cod, pgp->nome, pgp->classe);
    fprintf(fp, "| stat_base: "); stat_print(fp, &(pgp->b_stat), 1); fprintf(fp, "\n");
    fprintf(fp, "| stat_eq: ");   stat_print(fp, &(pgp->eq_stat), 1); fprintf(fp, "\n");
    fprintf(fp, "| equipaggiamento:\n"); equipArray_print(fp, pgp->equip, invArray);
    fprintf(fp, "╰──────────────\n");
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip, invArray);
    // update stats
    pgp->eq_stat = pgp->b_stat;
    for (int i=0; i<equipArray_inUse(pgp->equip); i++){
        stat_t stat = inv_getStat(invArray_getByIndex(invArray, equipArray_getEquipByIndex(pgp->equip, i)));
        pgp->eq_stat.hp += stat.hp;
        pgp->eq_stat.mp += stat.mp;
        pgp->eq_stat.atk += stat.atk;
        pgp->eq_stat.def += stat.def;
        pgp->eq_stat.mag += stat.mag;
        pgp->eq_stat.spr += stat.spr;
    }
}