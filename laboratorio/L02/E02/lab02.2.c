// Mattia Micheletta Merlin, esercizio 2, laboratorio 2

#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(int nc, int nr, FILE *fp){
    int **mat;

    mat = malloc(sizeof(int*) * nr);
    if (mat == NULL) { printf("Errore nell'allocazione della matrice\n"); exit(1); }

    for (int i=0; i<nr; i++){
        mat[i] = malloc(sizeof(int) * nc);
            if (mat[i] == NULL) { printf("Errore nell'allocazione della matrice\n"); exit(1); }
        for (int j=0; j<nc; j++){
            fscanf(fp, "%d", &mat[i][j]);
        }
    }

    return mat;
}

void separa(int **mat, int nr, int nc, int **bianchi, int **neri){
    int tot = nr*nc/2;
    *bianchi = malloc(sizeof(int) * (tot+1));
    *neri = malloc(sizeof(int) * tot);

    int b=0, n=0;

    for (int i=0; i<nr; i++){
        for (int j=0; j<nc; j++){
            if ((i%2 + j)%2 == 0){
                (*bianchi)[b] = mat[i][j];
                b++;
            } else {
                (*neri)[n] = mat[i][j];
                n++;
            }
        }
    }
}

int main(){
    int nc, nr;
    char path[] = "./mat.txt";
    int **mat;
    int *bianchi, *neri;

    FILE *fp = fopen(path, "r");
    fscanf(fp, "%d %d", &nc, &nr);

    mat = malloc2dR(nc, nr, fp);
    
    fclose(fp);

    printf("Matrix (dynamically allocated):\n");
    for (int i=0; i<nr; i++){
        for (int j=0; j<nc; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    separa(mat, nr, nc, &bianchi, &neri);

    printf("Vettori scacchiera (dynamically allocated):\n");
    for (int i=0; i<nr*nc/2+1; i++){
        printf("%d", bianchi[i]);
    }
    printf("\n");

    for (int i=0; i<nr*nc/2; i++){
        printf("%d", neri[i]);
    }
    printf("\n");

    free(mat);
    free(bianchi);
    free(neri);
}