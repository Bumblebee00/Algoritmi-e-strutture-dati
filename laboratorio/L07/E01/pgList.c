#include "pgList.h"

typedef struct pgNode_s* link;
struct pgNode_s{
    pg_t pg;
    link next;
};

struct pgList_s{
    link headPg;
    int nPg;
};

pgList_t pgList_init(){
    pgList_t pgList = malloc(sizeof(struct pgList_s));
    pgList->headPg = NULL;
    pgList->nPg = 0;
    return pgList;
}

void pgList_free(pgList_t pgList){
    link x, next;
    for (x=pgList->headPg; x!=NULL; x=next){
        next = x->next;
        pg_clean(&x->pg);
        free(x);
    }
    free(pgList);
}

void pgList_read(FILE *fp, pgList_t pgList){
    pg_t pg;
    while (pg_read(fp, &pg) == 1){
        pgList_insert(pgList, pg);
    }
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    link x;
    for (x=pgList->headPg; x!=NULL; x=x->next){
        pg_print(fp, &x->pg, invArray);
    }
}

void pgList_insert(pgList_t pgList, pg_t pg){
    link x, p;
    x = malloc(sizeof(struct pgNode_s));
    x->pg = pg;
    x->next = NULL;
    if (pgList->headPg == NULL){
        pgList->headPg = x;
    } else {
        for (p=pgList->headPg; p->next!=NULL; p=p->next);
        p->next = x;
    }
    pgList->nPg++;
}

void pgList_remove(pgList_t pgList, char* cod){
    link x, p;
    for (x=pgList->headPg, p=NULL; x!=NULL; p=x, x=x->next){
        if (strcmp(x->pg.cod, cod) == 0){
            if (p == NULL){
                pgList->headPg = x->next;
            } else {
                p->next = x->next;
            }
            pgList->nPg--;
            pg_clean(&x->pg);
            free(x);
            printf("Personaggio rimosso\n");
            return;
        }
    }
    printf("Personaggio non trovato\n");
}

pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    link x;
    for (x=pgList->headPg; x!=NULL; x=x->next){
        if (strcmp(x->pg.cod, cod) == 0){
            return &x->pg;
        }
    }
    return NULL;
}