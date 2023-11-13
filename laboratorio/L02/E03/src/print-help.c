#include <stdio.h>
#include <stdlib.h>
#include "../include/main.h"
#include "../include/print-help.h"

void print_ride(BusRide ride){
    printf("%s %-30s %-30s %s %s %s | %d min\n", ride.code, ride.from, ride.to, ride.date, ride.departure, ride.arrival, ride.ritardo);
}

char *print_rideR(BusRide ride){
    char *str = malloc(sizeof(char)*MAX*4);
    sprintf(str, "%s %-30s %-30s %s %s %s | %d min\n", ride.code, ride.from, ride.to, ride.date, ride.departure, ride.arrival, ride.ritardo);
    return str;
}

void print_rides(BusRide rides[], int n){
    printf("Codice %-30s %-30s Data       Partenza Arrivo   | Ritardo\n", "Partenza", "Arrivo");
    for (int i=0; i<n; i++){ print_ride(rides[i]); }
}

void print_commands(){
    int nc=6;
    char commands[6][MAX] = {
        "stampa a video",
        "stampa su file",
        "ordinamento",
        "ricerca",
        "leggi file",
        "fine" };
    char descriptions[6][MAX*4] = {
        "stampa a video i contenuti del log",
        "scrive su un file i contenuti del log",
        "ordinamento del vettore per chiave a scelta",
        "ricerca di una tratta per stazione di partenza",
        "leggere tratte da un file",
        "terminare il programma" };

    printf("\nComandi disponibili:\n");
    for (int i=0; i<nc; i++){ printf(" (%d) %-14s: %s\n", i, commands[i], descriptions[i]); }
}

void print_ord_keys(){
    printf(" (0) %-12s: %s\n", "data", "ordinamento per data");
    printf(" (1) %-12s: %s\n", "codice", "ordinamento per codice");
    printf(" (2) %-12s: %s\n", "partenza", "ordinamento per stazione di partenza");
    printf(" (3) %-12s: %s\n", "arrivo", "ordinamento per stazione di arrivo");
    printf("Inserisci il parametro di ordinamento: ");
}