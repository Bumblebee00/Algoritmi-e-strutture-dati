#include "equipArray.h"

struct equipArray_s{
    int *vettEquip;
    int nEquip;
};

equipArray_t equipArray_init(){
    equipArray_t equipArray = malloc(sizeof(struct equipArray_s));
    equipArray->vettEquip = NULL;
    equipArray->nEquip = 0;
    return equipArray;
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray->vettEquip);
    free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray){
    return equipArray->nEquip;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    for (int i=0; i<equipArray->nEquip; i++){
        fprintf(fp, "%d) ", i);
        invArray_printByIndex(fp, invArray, equipArray->vettEquip[i]);
        fprintf(fp, "\n");
    }
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    if (equipArray->vettEquip == NULL){
        equipArray->vettEquip = malloc(8 * sizeof(int));
        for (int i=0; i<8; i++){
            equipArray->vettEquip[i] = -1;
        }
        equipArray->nEquip = 8;
    }
    invArray_print(stdout, invArray);
    int index_inv, index_eqip_arr;
    printf("Inserisci indice oggetto da equipaggiare: ");
    scanf("%d", &index_inv);
    
    equipArray_print(stdout, equipArray, invArray);
    printf("Inserisci slot equipaggiamento (0-7): ");
    scanf("%d", &index_eqip_arr);
    (equipArray->vettEquip)[index_eqip_arr] = index_inv;
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    return equipArray->vettEquip[index];
}