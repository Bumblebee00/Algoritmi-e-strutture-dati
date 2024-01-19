#include "greedy.h"

float DD;
float DP;

int main(void){
    struct diagArr listaDiag;

    FILE *fp = fopen("elementi.txt", "r");
    fscanf(fp, "%d", &(listaDiag.nEl));
    listaDiag.vec = calloc(listaDiag.nEl, sizeof(struct elemento_s));
    for (int i = 0; i < listaDiag.nEl; i++){
        fscanf(fp, " %s %d %d %d %d %d %f %f", listaDiag.vec[i].name, &(listaDiag.vec[i].tipo), &(listaDiag.vec[i].dir_ingresso), &(listaDiag.vec[i].dir_uscita), &(listaDiag.vec[i].notFirst), &(listaDiag.vec[i].last), &(listaDiag.vec[i].points), &(listaDiag.vec[i].dif));
    }
    fclose(fp);
    printf("%d elementi letti\n", listaDiag.nEl);

    printf("Inserisci DD e DP separati da uno spazio: ");
    scanf("%f %f", &DD, &DP);

    greedySol(listaDiag);
}