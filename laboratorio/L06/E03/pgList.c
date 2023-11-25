#include "pgList.h"


/* creatore e distruttore */
pgList_t pgList_init(){
    pgList_t pgList = malloc(sizeof(struct pgList_s));
    pgList->head = NULL;
    pgList->tailPg = NULL;
    pgList->nPg = 0;
    return pgList;
}
void pgList_free(pgList_t pgList){
    nodoPg_t x, p;
    for (x = pgList->head; x != NULL; x = p) {
        p = x->next;
        free(x);
    }
    free(pgList);
}

/* lettura e scrittura su file */
void pgList_read(FILE *fp, pgList_t pgList){
    pg_t pg;
    while (pg_read(fp, &pg) == 1) {
        pgList_insert(pgList, pg);
    }
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    nodoPg_t x;
    for (x = pgList->head; x != NULL; x = x->next) {
        pg_print(fp, &(x->pg), invArray);
    }
}

/* inserimento di un nuovo personaggio */
void pgList_insert(pgList_t pgList, pg_t pg){
    nodoPg_t x, p;
    x = malloc(sizeof(struct nodoPg_s));
    x->pg = pg;
    x->next = NULL;
    if (pgList->head == NULL) {
        pgList->head = x;
        pgList->tailPg = x;
    } else {
        pgList->tailPg->next = x;
        pgList->tailPg = x;
    }
    pgList->nPg++;
}
/* cancellazione con rimozione */
void pgList_remove(pgList_t pgList, char* cod){
    nodoPg_t x, p;
    for (x = pgList->head, p = NULL; x != NULL; p = x, x = x->next) {
        if (strcmp(x->pg.cod, cod) == 0) {
            if (x == pgList->head) {
                pgList->head = x->next;
            } else {
                p->next = x->next;
            }
            free(x);
            pgList->nPg--;
            return;
        }
    }
}
/* ricerca per codice, ritornando il puntatore */
pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    nodoPg_t x;
    for (x = pgList->head; x != NULL; x = x->next) {
        if (strcmp(x->pg.cod, cod) == 0) {
            return &(x->pg);
        }
    }
    return NULL;
}