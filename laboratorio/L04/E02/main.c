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

    while (1) {
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
        scanf("%s %s %s %s %s %s %d", tmp.codice, tmp.nome, tmp.cognome, tmp.dataNascita, tmp.via, tmp.citta, &tmp.cap);
        *head = insertOrderedBirthday(*head, tmp);
        break;
    case 1:
        scanf("%s", str);
        FILE *fp = fopen(str, "r");
        if (fp==NULL){ printf("File not found"); return; }
        while (fscanf(fp, "%s %s %s %s %s %s %d", tmp.codice, tmp.nome, tmp.cognome, tmp.dataNascita, tmp.via, tmp.citta, &tmp.cap) != EOF){
            *head = insertOrderedBirthday(*head, tmp);
        }
        fclose(fp);
        printf("Read file %s succesfully\n", str);
        break;
    
    case 2:
        scanf("%s", str);
        result = searchByCode(*head, str);
        if (result != NULL){ printItem(result->val); }
        else { printf("Element not found\n"); }
        break;
    
    case 3:
        scanf("%s", str);
        result = deleteByCode(*head, str);
        if (result != NULL){
            printItem(result->val);
            if (result == *head && (*head)->next == NULL){ *head = freeList(*head); }
            else { free(result); }
            printf("Element deleted succesfully\n");
        }
        else { printf("Element not found\n"); }
        break;

    case 4:
        scanf("%s %s", str, tmp.dataNascita);
        link deleted = deleteByDateInterval(*head, str, tmp.dataNascita);
        printf("I deleted:\n");
        for (link i = deleted; i != NULL; i=i->next){ printItem(i->val); };
        *head = freeList(deleted);
        break;

    case 5:
        scanf("%s", str);
        FILE *fp2 = fopen(str, "w");
        for (link i = *head; i != NULL; i=i->next){ fprintf(fp2, "%s %s %s %s %s %s %d\n", i->val.codice, i->val.nome, i->val.cognome, i->val.dataNascita, i->val.via, i->val.citta, i->val.cap); };
        fclose(fp2);
        printf("Saved list to file %s succesfully\n", str);
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
    printf("        0 <codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>: Acquisizione nuova persona da tastiera\n");
    printf("        1 <path>: Acquisizione nuove persone da file\n");
    printf("        2 <codice>: Ricerca persona per codice\n");
    printf("        3 <codice>: Cancellazione persona per codice\n");
    printf("        4 <data1> <data2>: Cancellazione persone con data di nascita compresa tra data1 e data2 (formato gg/mm/yyyy) (data1 è dopo data2)\n");
    printf("        5 <path>: Salvataggio lista su file\n");
    printf("        6 Stampa a video della lista\n");
    printf("        7 Esci\n");
    printf("Inserisci comando: ");
}