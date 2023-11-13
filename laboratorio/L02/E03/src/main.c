// Mattia Micheletta Merlin, esercizio 3, laboratorio 2

#include<stdio.h>
#include <stdlib.h>
#include "../include/main.h"
#include "../include/merge-sort.h"
#include "../include/print-help.h"
#include "../include/search.h"

int n = 0;
BusRide *rides = NULL;
BusRide ***sorted; // è un array di array di puntatori a BusRide

int main(){
    readFile("corse.txt", &rides, &n);

    sorted = Sort(rides, n);

    int input;
    while(1){
        print_commands();
        printf("\n\nInserisci il comando (tramite indice): ");
        scanf("%d", &input);
        selezionaDati(input);
    }
}


void selezionaDati(comando_e comando){
    switch (comando) {
    case r_stampa_video:
        print_rides(rides, n);
        break;

    case r_stampa_file:
        printf("Inserisci il nome del file: ");
        char filename[MAX];
        scanf("%s", filename);
        FILE *fp = fopen(filename, "w");
        if (fp == NULL){ printf("Unable to open file");}

        fprintf(fp, "Codice %-30s %-30s Data       Partenza Arrivo   | Ritardo\n", "Partenza", "Arrivo");
        for (int i=0; i<n; i++){ fprintf(fp, "%s", print_rideR(rides[i])); }
        
        fclose(fp);
        break;
    
    case r_ord:
        print_ord_keys();
        int input;
        scanf("%d", &input);
        for (int i=0; i<n; i++){
            print_ride(*(sorted[input][i]));
        }
        break;

    case r_ricerca:
        printf("Inserisci il nome della tratta di partenza (o anche solo l'inizio): ");
        char from[MAX];
        scanf("%s", from);
        printf("Utilizzare la funzione di ricerca (0) lineare o (1) dicotomica? ");
        int *search_results;
        int option;
        scanf("%d", &option);
        if (option==0){ search_results = LinearSearch(sorted[2], n, from); }
        else if (option==1){ search_results = BinSearch(sorted[2], 0, n-1, from); }
        else {printf("Immetti 0 (funzione Lineare) o 1 (funzione Dicotomica)"); break;}

        printf("Ecco i risulati della tua ricerca: \n");
        printf("Codice %-30s %-30s Data       Partenza Arrivo   | Ritardo\n", "Partenza", "Arrivo");
        for (int i=0; search_results[i] != -1; i++){ print_ride(*sorted[2][search_results[i]]); }
        free(search_results);

        break;

    case r_acquisisci:
        printf("Inserisci il nome del file da leggere: ");
        char path[MAX];
        scanf("%s", path);

        readFile(path, &rides, &n);
        sorted = Sort(rides, n);
        break;

    case r_fine:
        exit(EXIT_SUCCESS);

    default:
        break;
    }
}

void readFile(char *path, BusRide **v, int *n){
    int l = 0;

    FILE *fp = fopen(path, "r");
    if (fp==NULL){ printf("Failed to open file"); return; }
    fscanf(fp, "%d\n", &l);

    if (*n==0)
        *v = malloc(sizeof(BusRide)*(*n + l));
    else
        *v = realloc(*v, sizeof(BusRide)*(*n + l));

    // get rides from file
    for (int i=*n; i<(*n + l); i++){
        char date[MAX], arrival[MAX], departure[MAX];
        fscanf(fp, "%s %s %s %s %s %s %d\n", (*v)[i].code, (*v)[i].from, (*v)[i].to, (*v)[i].date, (*v)[i].departure, (*v)[i].arrival, &(*v)[i].ritardo);
    }
    *n += l;
    printf("File read usccesfully. New %d rides added to database (tot %d)\n", l, *n);
}