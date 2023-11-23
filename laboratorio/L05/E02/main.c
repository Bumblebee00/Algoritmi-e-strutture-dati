// assunzione 1: RxC = T
#include<stdio.h>
#include<stdlib.h>

struct Tubo{
    char colore;
    int punti;
};

struct Tessera{
    struct Tubo orizzontale;
    struct Tubo verticale;
};

struct Casella{
    // if NULL there is no tessera here
    struct Tessera *tessera;
    int rot;
    int unmodifiable;
};

void findMaxScacchiera(struct Casella *statoIniziale, int *mark);
void findMaxScacchieraR(int pos, struct Casella *sol, int *mark, int* maxPoints, struct Casella *maxSol);
int calculatePoints(struct Casella *sol);

int T, R, C;
// lista di tutte le tessere
struct Tessera *tessere;

int main(){
    FILE *fp;

    // array RxC, che contiene, tutte allineate, le tessere della scacchiera (quindi all'inizio lo riempiamo con la scacchiera iniziale)
    struct Casella *scacchiera;
    // array RxC di zeri e uni, che rappresenta se la tessera all'indice i è già stata messa nella sacchiera
    // 0 non è stata messa. 1 è stata messa
    int *mark;

    fp = fopen("tiles.txt", "r");
    fscanf(fp, "%d\n", &T);
    tessere = malloc(sizeof(struct Tessera) * T);
    for (int i=0; i<T; i++){
        fscanf(fp, "%c %d %c %d\n",
            &tessere[i].orizzontale.colore,
            &tessere[i].orizzontale.punti,
            &tessere[i].verticale.colore,
            &tessere[i].verticale.punti);
    }
    fclose(fp);

    fp = fopen("board.txt", "r");
    fscanf(fp, "%d %d\n", &R, &C);
    if (R*C!=T){ printf("Errore: R*C!=T\n"); return 1; }
    scacchiera = malloc(sizeof(struct Casella)*T);
    mark = calloc(T, sizeof(int));
    for (int i=0; i<R; i++){
        for (int j=0; j<C; j++){
            int indiceTessera;
            int rot;
            fscanf(fp, "%d/%d ", &indiceTessera, &rot);
            int indiceGriglia = R*i + j;
            if (indiceTessera != -1){
                mark[indiceTessera] = 1;
                scacchiera[indiceGriglia].tessera = &tessere[indiceTessera];
                scacchiera[indiceGriglia].rot = rot;
                scacchiera[indiceGriglia].unmodifiable = 1;
            } else {
                scacchiera[indiceGriglia].tessera = NULL;
                scacchiera[indiceGriglia].unmodifiable = 0;
            }
        }
        fscanf(fp, "\n");
    }
    fclose(fp);

    printf("Finding max scacchiera...\n\n");
    findMaxScacchiera(scacchiera, mark);
}

void findMaxScacchiera(struct Casella *statoIniziale, int *mark){
    int maxPoints = 0;
    struct Casella *maxSol = malloc(sizeof(struct Casella) * T);

    findMaxScacchieraR(0, statoIniziale, mark, &maxPoints, maxSol);

    printf("MaxPoints: %d\n", maxPoints);

    for (int i=0; i<R; i++){
        for (int j=0; j<C; j++){
            int indiceGriglia = R*i + j;
            if (maxSol[indiceGriglia].tessera == NULL){
                printf("orizz:   vert:     ");
            } else {
                if (maxSol[indiceGriglia].rot == 0){
                    printf("orizz:%c%d vert:%c%d   ", (*maxSol[indiceGriglia].tessera).orizzontale.colore, (*maxSol[indiceGriglia].tessera).orizzontale.punti, (*maxSol[indiceGriglia].tessera).verticale.colore, (*maxSol[indiceGriglia].tessera).verticale.punti);
                } else {
                    printf("orizz:%c%d vert:%c%d   ", (*maxSol[indiceGriglia].tessera).verticale.colore, (*maxSol[indiceGriglia].tessera).verticale.punti, (*maxSol[indiceGriglia].tessera).orizzontale.colore, (*maxSol[indiceGriglia].tessera).orizzontale.punti);
                }
            }
        }
        printf("\n");
    }
}

void findMaxScacchieraR(int pos, struct Casella *sol, int *mark, int* maxPoints, struct Casella *maxSol){
    // cond term
    if (pos == T){
        int thisPoints = calculatePoints(sol);
        if (thisPoints > *maxPoints){
            *maxPoints = thisPoints;
            for (int i=0; i<T; i++){
                maxSol[i] = sol[i];
            }
        } else { return; }
    }
    
    // find the next modifiable casella
    while (sol[pos].unmodifiable){
        pos++;
    }
    
    // itera su tutte le tessere
    for (int i=0; i<T; i++){
        // se non è ancora stata usata
        if (mark[i] == 0){
            mark[i] = 1;
            sol[pos].tessera = &tessere[i];
            sol[pos].rot = 0;
            findMaxScacchieraR(pos+1, sol, mark, maxPoints, maxSol);
            sol[pos].rot = 1;
            findMaxScacchieraR(pos+1, sol, mark, maxPoints, maxSol);
            mark[i] = 0;
        }
    }
}

int calculatePoints(struct Casella *sol){
    int pTot = 0;
    int indiceGriglia;
    // punti delle righe
    for (int i=0; i<R; i++){
        int tempP;
        char colorePrimo;
        int rigaValida = 1;

        if (sol[i*R].rot == 0){
            colorePrimo = (*sol[i*R].tessera).orizzontale.colore;
            tempP = (*sol[i*R].tessera).orizzontale.punti;
        } else {
            colorePrimo = (*sol[i*R].tessera).verticale.colore;
            tempP = (*sol[i*R].tessera).verticale.punti;
        }

        for (int j=1; j<C; j++){
            indiceGriglia = R*i + j;
            if (sol[indiceGriglia].rot == 0){
                // se c'è un colore diverso esci
                if ((*sol[indiceGriglia].tessera).orizzontale.colore != colorePrimo){
                    rigaValida = 0;
                    break;
                } else {
                    tempP += (*sol[indiceGriglia].tessera).orizzontale.punti;
                }
            } else {
                // se c'è un colore diverso esci
                if ((*sol[indiceGriglia].tessera).verticale.colore != colorePrimo){
                    rigaValida = 0;
                    break;
                } else {
                    tempP += (*sol[indiceGriglia].tessera).verticale.punti;
                }
            }
        }

        if (rigaValida){
            pTot += tempP;
        }
    }

    // punti delle colonne
    for (int i=0; i<C; i++){
        int tempP;
        char colorePrimo;
        int colonnaValida = 1;

        int first = i;
        if (sol[first].rot == 0){
            colorePrimo = (*sol[first].tessera).verticale.colore;
            tempP = (*sol[first].tessera).verticale.punti;
        } else {
            colorePrimo = (*sol[first].tessera).orizzontale.colore;
            tempP = (*sol[first].tessera).orizzontale.punti;
        }

        for (int j=1; j<R; j++){
            indiceGriglia = R*j + i;
            if (sol[indiceGriglia].rot == 0){
                // se c'è un colore diverso esci
                if ((*sol[indiceGriglia].tessera).verticale.colore != colorePrimo){
                    colonnaValida = 0;
                    break;
                } else {
                    tempP += (*sol[indiceGriglia].tessera).verticale.punti;
                }
            } else {
                // se c'è un colore diverso esci
                if ((*sol[indiceGriglia].tessera).orizzontale.colore != colorePrimo){
                    colonnaValida = 0;
                    break;
                } else {
                    tempP += (*sol[indiceGriglia].tessera).orizzontale.punti;
                }
            }
        }

        if (colonnaValida){
            pTot += tempP;
        }
    }

    return pTot;
}