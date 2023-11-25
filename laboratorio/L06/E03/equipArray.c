#include "equipArray.h"

/* creatore e disruttore */
equipArray_t equipArray_init(){
    equipArray_t equipArray = malloc(sizeof(struct equipArray_s));
    equipArray->inUso = 0;
    return equipArray;
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}

/* quanti equipaggiamenti sono in uso */
int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUso;
}

/* scrittura su file */
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    int i;
    for(i=0; i<equipArray->inUso; i++){
        fprintf(fp, "%s %s %d %d %d %d %d %d\n", equipArray->vettEq[i].nome, equipArray->vettEq[i].tipo, equipArray->vettEq[i].stat.hp, equipArray->vettEq[i].stat.mp, equipArray->vettEq[i].stat.atk, equipArray->vettEq[i].stat.def, equipArray->vettEq[i].stat.mag, equipArray->vettEq[i].stat.spr);
    }
}
/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    int i, scelta;
    char nome[LEN];
    if (equipArray->inUso == EQUIP_SLOT){
        printf("Equipaggiamento pieno\n");
        return;
    }
    printf("Inserisci il nome dell'oggetto da equipaggiare: ");
    scanf("%s", nome);
    int index = invArray_searchByName(invArray, nome);
    if(index == -1){
        printf("Oggetto non trovato\n");
        return;
    }
    inv_t *invp = invArray_getByIndex(invArray, index);
    equipArray->vettEq[equipArray->inUso] = *invp;
    equipArray->inUso++;
}
/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index, invArray_t invArray){
    char *nameEquiuip = equipArray->vettEq[index].nome;
    return invArray_searchByName(invArray, nameEquiuip);
}
