#include <stdio.h>

#define MAX 20

int main() {
    int x = 5;
    int *puntatore = &x;
    int valore = *puntatore;

    printf("Value of x: %d\n", x);

    printf("Value via pointer: %d\n", *puntatore);
    printf("Stored value: %d\n", valore);
    printf("Address of variable: %d\n", puntatore);

    *puntatore = x+1;
    printf("New value of x (modified by pointer): %d\n", x);




    // vettore e puntatore
    int v[] = {1, 2, 3, 4};
    printf("primo el: %d\n", v[0]);
    printf("primo el: %d\n", *v);







    int dati[6], *p, i;
    p = &dati[0]; // p punta al primo elemento dell'array dati
    // potrebbe anche essere p = dati;

    // modo 1
    for (i=0;i<5;i++)
        scanf("%d", p+i);
    /* modo 2
    for (i=0;i<10;i++, p++)
        scanf("%d", p);
    */
    for (i=0; i<5; i++)
        printf("el %d: %d\n",i,dati[i]);












    struct studente{
    char cognome[MAX], nome[MAX];
    int matricola;
    float media;
    };

    struct studente s1 = {"Rossi", "Mario", 12345, 27.5};
    
    // puntatore allo sruct
    struct studente *puntatore_a_studente = &s1;

    // puntatore al campo cognome
    char *puntatore_a_cognome = s1.cognome;
    // char *puntatore_a_cognome = &(*puntatore_a_studente).cognome;

    // stampa la media in vari modi
    printf("%f\n", puntatore_a_studente->media);
    printf("%f\n", (*puntatore_a_studente).media);

    // stampa il cognome in vari modi
    printf("%s\n", puntatore_a_cognome);
    printf("%s\n", (*puntatore_a_cognome));


    return 0;
}

