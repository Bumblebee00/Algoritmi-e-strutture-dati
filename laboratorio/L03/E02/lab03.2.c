// Mattia Micheletta Merlin, esercizio 2, laboratorio 3, 26/10/2023

#include <stdio.h>
#include <stdlib.h>
#define MAX 255

typedef struct Livello{int num_scelte; char **scelte;} Livello;

int findAllPlaylists(Livello *val, int n);
int princ_molt(int, Livello *val, char **sol, int n, int cnt);

int main(int argc, char *argv[])
{
    if (argc != 2){ printf("Usage: %s <file_path>\n", argv[0]); return 1; }
    
    char *filePath = argv[1];
    FILE *fp = fopen(filePath, "r");
    
    int A;
    fscanf(fp, "%d\n", &A);
    
    // val contains A number of levels
    // each level contains a num_scelte int, and a vector of strings
    Livello *val = malloc(A*sizeof(Livello));

    for (int i=0; i<A; i++){
        int nSongs;
        fscanf(fp,"\t%d\n", &nSongs);
        val[i].num_scelte = nSongs;
        val[i].scelte = malloc(nSongs*sizeof(char*));

        for (int j=0;j<nSongs;j++){
            char *song = malloc(MAX*sizeof(char));
            fscanf(fp,"\t\t%s\n", song);
            val[i].scelte[j] = song;
        }
    }

    printf("Ecco tutte le playlist possiblili:\n");
    int tot = findAllPlaylists(val, A);
    printf("Sono in %d tutto\n", tot);
}

// wrapper 😎
int findAllPlaylists(Livello *val, int n){
    char **sol = malloc(n*sizeof(char *));
    return princ_molt(0, val, sol, n, 0);
}

/*
pos is the starting pos for the recursion
val contains n number of levels, each level contains a num_scelte int, and a vector of strings
sol is a vector of strings, of lenght A, that gets written over and over. (once is full is printed, and then rewritten by other istanze di ricorsione)
*/
int princ_molt(int pos, Livello *val, char **sol, int n, int cnt) {
    int i;
    if (pos >= n){
        for (i = 0; i < n; i++)
            printf("%-25s ", sol[i]);
        printf("\n");
        return cnt + 1;
    }
    for (i = 0; i < val[pos].num_scelte; i++){
        sol[pos] = val[pos].scelte[i];
        cnt = princ_molt(pos + 1, val, sol, n, cnt);
    }
    return cnt;
}
