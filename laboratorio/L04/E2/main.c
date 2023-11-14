#include<stdio.h>
#include<stdlib.h>
#include "liste.h"

// takes the list (pointer to node = link) by reference (rather thab by value) (pointer to link)
void azione(int, link*);
void printMenu();
void printItem(Item);

int main(){
    int d;
    link head = NULL;

    while (1)
    {
        printMenu();
        scanf("%d", &d);
        azione(d, &head);
    }
    
}

void azione(int d, link *head){
    link result;
    Item tmp;
    char str[MAX];
    switch (d)
    {
    case 0:
        printf("Inserisci i dati nel formato:\n<codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>:\n");
        scanf("%s %s %s %s %s %s %d", tmp.codice, tmp.nome, tmp.cognome, tmp.dataNascita, tmp.via, tmp.citta, &tmp.cap);
        *head = insertOrderedBirthday(*head, tmp);
        break;
    case 1:
        printf("Inserisci il path del file: ");
        scanf("%s", str);
        FILE *fp = fopen(str, "r");
        if (fp==NULL){ printf("File not found"); return; }
        while (fscanf(fp, "%s %s %s %s %s %s %d", tmp.codice, tmp.nome, tmp.cognome, tmp.dataNascita, tmp.via, tmp.citta, &tmp.cap) != EOF){
            *head = insertOrderedBirthday(*head, tmp);
        }
        fclose(fp);
        break;
    
    case 2:
        printf("Inserisci il codice: ");
        scanf("%s", str);
        result = searchByCode(*head, str);
        if (result != NULL){ printItem(result->val); }
        else { printf("Element not found\n"); }
        break;
    
    case 3:
        printf("Inserisci il codice: ");
        scanf("%s", str);
        result = deleteByCode(*head, str);
        if (result != NULL){ printItem(result->val); }
        else { printf("Element not found\n"); }
        break;

    case 6:
        for (link i = *head; i != NULL; i=i->next){ printItem(i->val); };
        break;
    
    case 7:
        exit(0);
        break;

    default:
        break;
    }
}

// printer functions
void printItem(Item x){
    printf("%s %s %s %s %s %s %d\n", x.codice, x.nome, x.cognome, x.dataNascita, x.via, x.citta, x.cap);
}

void printMenu(){
    printf("\nComandi disponibili:\n");
    printf(" (0) Acquisizione e inserimento ordinato di un nuovo elemento in lista (da tastiera)\n");
    printf(" (1) Acquisizione ed inserimento ordinato di nuovi elementi in lista (da file)\n");
    printf(" (2) Ricerca un elemento per codice\n");
    printf(" (3) Cancellazione di un elemento dalla lista, dato il codice\n");
    printf(" (6) Stampa a video della lista\n");
    printf(" (7) Esci\n");
    printf("Inserisci comando (tramite indice): ");
}