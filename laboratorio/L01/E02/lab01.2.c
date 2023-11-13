// Mattia Micheletta Merlin, esercizio 2, laboratorio 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30
#define nComandi 7

typedef struct {
    char code[MAX];
    char from[MAX];
    char to[MAX];
    char date[MAX];
    char departure[MAX];
    char arrival[MAX];
    int ritardo;
} BusRide;

typedef enum { r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_tutto, r_fine } comando_e;

char commands[nComandi][MAX] = {
    "date",
    "partenza",
    "capolinea",
    "ritardo",
    "ritardo_tot",
    "tutto",
    "fine"
};

int leggiFile(BusRide *corse, char nome_file[]);
comando_e leggiComando();
void selezionaDati(comando_e, BusRide[], int);
void stampaMenu();
void print_ride(BusRide);
int isBefore(char[], char[]);

int main(){
    int n; // al più 1000
    comando_e comando;

    BusRide rides[MAX];
    n = leggiFile(rides, "corse.txt");

    while(1){
        stampaMenu();
        comando_e comando = leggiComando();
        selezionaDati(comando, rides, n);
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

comando_e leggiComando(){
    char input[MAX];
    printf("\nInserisci il comando: ");
    scanf("%s", input);
    for (int i=0; i<nComandi; i++){
        if (strcmp(input, commands[i]) == 0){
            return i;
        }
    }
    printf("Comando non valido\n");
    exit(EXIT_FAILURE);
}

void selezionaDati(comando_e comando, BusRide rides[], int n){
    char s1[MAX], s2[MAX];
    switch (comando){
        case r_date:{
            scanf("%s %s", s1, s2);
            for (int i=0; i<n; i++){
                if (isBefore(s1, rides[i].date) && isBefore(rides[i].date, s2)){
                    print_ride(rides[i]);
                }
            }
            break;
        }
        case r_partenza:
            scanf("%s", s1);
            for (int i=0; i<n; i++){
                if (strcmp(rides[i].from, s1) == 0){
                    print_ride(rides[i]);
                }
            }
            break;
        case r_capolinea:
            scanf("%s", s1);
            for (int i=0; i<n; i++){
                if (strcmp(rides[i].to, s1) == 0){
                    print_ride(rides[i]);
                }
            }
            break;
        case r_ritardo:
        {
            scanf("%s %s", s1, s2);
            for (int i=0; i<n; i++){
                if (isBefore(s1, rides[i].date) && isBefore(rides[i].date, s2) && rides[i].ritardo > 0){
                    print_ride(rides[i]);
                }
            }
            break;
        }
        case r_ritardo_tot:
            scanf("%s", s1);
            int ritardo_tot = 0;
            for (int i=0; i<n; i++){
                if (strcmp(rides[i].code, s1) == 0){
                    ritardo_tot += rides[i].ritardo;
                }
            }
            printf("Ritardo totale: %d min\n", ritardo_tot);
            break;
        case r_tutto:
            for (int i=0; i<n; i++){ print_ride(rides[i]); }
            break;
        case r_fine:
            exit(EXIT_SUCCESS);
        default:
            break;
    }
}

void stampaMenu(){
    char arguments[nComandi][MAX*4] = {
        "<data1> <data2>",
        "<partenza>",
        "<capolinea>",
        "<data1> <data2>",
        "<codice_tratta>",
        "",
        ""
    };
    char descriptions[nComandi][MAX*4] = {
        "elencare tutte le corse partite in un certo intervallo di date",
        "elencare tutti le corse partite da una certa fermata",
        "elencare tutti le corse che fanno capolinea in una certa fermata",
        "elencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di date",
        "elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta",
        "elencare tutte le corse",
        "terminare il programma"
    };

    printf("\nComandi disponibili:\n");
    for (int i=0; i<nComandi; i++){
        printf("%-13s %-16s %s\n", commands[i], arguments[i], descriptions[i]);
    }
}

void print_ride(BusRide ride){
    printf("%s %-30s %-30s %s %s %s | %d min\n", ride.code, ride.from, ride.to, ride.date, ride.departure, ride.arrival, ride.ritardo);
}

int isBefore(char date1[], char date2[]){
    int y1, m1, d1, y2, m2, d2;
    sscanf(date1, "%d/%d/%d", &y1, &m1, &d1);
    sscanf(date2, "%d/%d/%d", &y2, &m2, &d2);
    if (y1 < y2){
        return 1;
    } else if (y1 == y2){
        if (m1 < m2){
            return 1;
        } else if (m1 == m2){
            if (d1 < d2){
                return 1;
            } else if (d1 == d2){
                return 1;
            } else { return 0; }
        } else { return 0; }
    } else { return 0; }
}