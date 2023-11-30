#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void leggiFile(char *path, att* *v, int* n);

int main(int argc, char *argv[]){
    if (argc != 2){ printf("Usage: %s filename\n", argv[0]); return 1; }

    int n;
    att* v;
    leggiFile(argv[1], &v, &n);

    // debug
    for (int i=0; i<n; i++){ printf("%d %d\n", v[i].inizio, v[i].fine); }

    
}

void leggiFile(char *path, att* *v, int* n){
    FILE* fp = fopen(path, "r");
    if (fp==NULL){ printf("File %s not found", path); }
    fscanf(fp, "%d\n", n);

    *v = malloc(sizeof(att)*(*n));

    for (int i=0; i<(*n); i++){
        fscanf(fp, "%d %d\n", &((*v)[i].inizio), &((*v)[i].fine));
    }
    fclose(fp);
}