// ipotesi semplificativa: non possono arrivare in un file transazioni di un titolo nello stesso giorno che c'era anche in un altro file. Cioè una volta che la quotazione giornaliera è stata aggiunta al BST non si modifica più.
#include<stdio.h>
#include "tempo.h"
#include "titolo.h"
#include "quotazione.h"

int printMenu();
void selezionaDati(int scelta, Titoli lista);

int main(){
    Titoli listaDiTitoli = initList();
    while (1){
        selezionaDati(printMenu(), listaDiTitoli);
    }
}

void selezionaDati(int scelta, Titoli lista){
    switch (scelta)
    {
    case 0:
        exit(1);
        break;
    
    case 1:{
        char path[MAX];
        int n_titoli, n_transazioni;

        // leggi il nome del file e il numero di titoli
        printf("Inserisci il nome del file: "); scanf("%s", path);
        FILE *fp = fopen(path, "r");
        fscanf(fp, "%d\n", &n_titoli);

        for (int i=0; i<n_titoli; i++){
            printf("i: %d\n", i);
            fscanf(fp, "%s %d\n", path, &n_transazioni); // adesso path contiene il titolo

            // leggi le transazioni dal file
            transazioni t = malloc(sizeof(struct transazione)*n_transazioni);
            for (int j=0; j<n_transazioni; j++){
                printf("    j: %d\n", j);
                t[j].data = malloc(sizeof(struct tempo_s));
                fscanf(fp, "%d/%d/%d %d:%d %d %d", &t[j].data->anno, &t[j].data->mese, &t[j].data->giorno, &t[j].data->ore, &t[j].data->minuti, &t[j].v, &t[j].n);
            }

            // vedi se c'è già il titolo nella lista
            //Titolo searchResult = ListSearch(lista, path);
            Quotazione q = calcolaQuotazione(t, n_transazioni, t[0].data);
            if (1){//searchResult == NULL){
                // se no aggiungi il nodo alla lista
                lista = addNode(lista, path, q);
            } else {
                // se si aggiungi la quotazione del giorno alla lista
                // updateTitolo(searchResult, q);
            }
        }
        printf("File acquisito con successo!\n");

        break;
    }

    case 99:{
        // stampa tutta la lista di titoli (debug)
        printList(lista);
        break;
    }
    
    default:
        break;
    }
}

int printMenu(){
    printf("\n0) Esci\n");
    printf("1) Acquisizione del contenuto di un file contenente un insieme di transazioni\n");
    printf("99) stampa tutta la lista di titoli (debug)\n");
    printf("\nSeleziona una delle seguenti opzioni: ");
    int scelta;
    scanf("%d", &scelta);
    return scelta;
}