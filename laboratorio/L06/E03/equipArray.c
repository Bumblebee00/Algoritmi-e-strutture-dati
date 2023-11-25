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
    // chiediamo all'utente se vuole aggiungere o rimuovere un oggetto
    int scelta;
    printf("Vuoi aggiungere o rimuovere un oggetto? (0/1): ");
    scanf("%d", &scelta);
    if (scelta == 0){
        equipArray_add(equipArray, invArray);
    } else if (scelta == 1){
        equipArray_remove(equipArray, invArray);
    } else {
        printf("Scelta non valida\n");
    }
}

/* aggiunge un oggetto da inventario a equipaggiamento */
void equipArray_add(equipArray_t equipArray, invArray_t invArray){
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
    } else {
        for (int i = 0; i < equipArray->inUso; ++i) {
            if (strcmp(equipArray->vettEq[i].nome, nome) == 0){
                printf("Oggetto gia' equipaggiato\n");
                return;
            }
        }
        printf("Oggetto equipaggiato correttamente\n");
    }
    inv_t *invp = invArray_getByIndex(invArray, index);
    equipArray->vettEq[equipArray->inUso] = *invp;
    equipArray->inUso++;
}

/* rimuove un oggetto da inventario a equipaggiamento */
void equipArray_remove(equipArray_t equipArray, invArray_t invArray){
    char nome[LEN];
    if (equipArray->inUso == 0){
        printf("Equipaggiamento vuoto\n");
        return;
    }
    printf("Inserisci il nome dell'oggetto da rimuovere: ");
    scanf("%s", nome);
    int index = invArray_searchByName(invArray, nome);
    if(index == -1){
        printf("Oggetto non trovato\n");
        return;
    } else {
        for (int i = 0; i < equipArray->inUso; ++i) {
            if (strcmp(equipArray->vettEq[i].nome, nome) == 0){
                for (int j = i; j < equipArray->inUso-1; ++j) {
                    equipArray->vettEq[j] = equipArray->vettEq[j+1];
                }
                equipArray->inUso--;
                printf("Oggetto rimosso correttamente\n");
                return;
            }
        }
        printf("Oggetto non equipaggiato\n");
    }
}

/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index, invArray_t invArray){
    char *nameEquiuip = equipArray->vettEq[index].nome;
    return invArray_searchByName(invArray, nameEquiuip);
}
