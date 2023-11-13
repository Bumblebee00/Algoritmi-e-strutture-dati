// Mattia Micheletta Merlin, esercizio 3, laboratorio 1

#include<stdio.h>
#include <stdlib.h>
#include "../include/main.h"
#include "../include/merge-sort.h"
#include "../include/print-help.h"
#include "../include/search.h"

int main(){
    int n, input;
    comando_e comando;
    BusRide rides[MAX];

    n = leggiFile(rides, "corse.txt");

    while(1){
        print_commands();
        printf("\n\nInserisci il comando (tramite indice): ");
        scanf("%d", &input);
        selezionaDati(input, rides, n);
    }
}

int leggiFile(BusRide *rides, char nome_file[]){
    FILE *fp;
    int n;

    fp = fopen(nome_file, "r");
    if (fp == NULL){ printf("Errore nell'apertura del file %s\n", nome_file); exit(EXIT_FAILURE); }
    fscanf(fp, "%d", &n);
    for (int i=0; i<n; i++){
        fscanf(fp, "%s %s %s %s %s %s %d", rides[i].code, rides[i].from, rides[i].to, rides[i].date, rides[i].departure, rides[i].arrival, &rides[i].ritardo);
    }
    fclose(fp);
    return n;
}

void selezionaDati(comando_e comando, BusRide rides[], int n){
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
        MergeSort(rides, n, input);
        
        print_rides(rides, n);
        break;

    case r_ricerca:
        printf("Inserisci il nome della tratta di partenza (o anche solo l'inizio): ");
        char from[MAX];
        scanf("%s", from);
        int *search_results;
        int option;
        printf("Utilizzare la funzione di ricerca (0) lineare o (1) dicotomica? ");
        scanf("%d", &option);

        if (option==0){ search_results = LinearSearch(rides, n, from); }
        else if (option==1){
            MergeSort(rides, n, 2); // ordina per stazione di partenza
            search_results = BinSearch(rides, 0, n-1, from);
        }
        else {printf("Immetti 0 (funzione Lineare) o 1 (funzione Dicotomica)"); break;}

        printf("Ecco i risulati della tua ricerca: \n");
        printf("Codice %-30s %-30s Data       Partenza Arrivo   | Ritardo\n", "Partenza", "Arrivo");
        for (int i=0; search_results[i] != -1; i++){ print_ride(rides[search_results[i]]); }
        free(search_results);

        break;

    case r_fine:
        exit(EXIT_SUCCESS);

    default:
        break;
    }
}
