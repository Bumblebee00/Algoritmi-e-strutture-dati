// ipotesi semplificativa: non possono arrivare in un file transazioni di un titolo nello stesso giorno che c'era anche in un altro file. Cioè una volta che la quotazione giornaliera è stata aggiunta al BST non si modifica più.
// ipotesi semplificativa2: supprta gli anni da 0 a 999999
#include<stdio.h>
#include "tempo.h"
#include "titolo.h"
#include "quotazione.h"

int printMenu();
void selezionaDati(int scelta, TitoliList lista);

int main(){
    TitoliList listaDiTitoli = initList();
    while (1){
        selezionaDati(printMenu(), listaDiTitoli);
    }
}

void selezionaDati(int scelta, TitoliList lista){
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
            fscanf(fp, "%s %d\n", path, &n_transazioni); // adesso path contiene il titolo
            // leggi le transazioni dal file
            transazioni t = malloc(sizeof(struct transazione)*n_transazioni);
            for (int j=0; j<n_transazioni; j++){
                t[j].data = malloc(sizeof(struct tempo_s));
                fscanf(fp, "%d/%d/%d %d:%d %d %d", &t[j].data->anno, &t[j].data->mese, &t[j].data->giorno, &t[j].data->ore, &t[j].data->minuti, &t[j].v, &t[j].n);
            }
            Quotazione q = calcolaQuotazione(t, n_transazioni, t[0].data);

            // vedi se c'è già il titolo nella lista
            Titolo searchResult = ListSearch(lista, path);
            if (searchResult == NULL){ addNode(lista, path, q);
            } else { updateTitolo(searchResult, q); }
        }
        fclose(fp);
        printf("File acquisito con successo!\n");
        
        break;
    }

    case 2:{
        printf("Inserisci il codice del titolo azionario: ");
        char code[MAX];
        scanf("%s", code);
        Titolo searchResult = ListSearch(lista, code);
        if (searchResult == NULL){printf("Il titolo azionario non è presente nella lista.\n");}
        else{
            printf("Titolo trovato:\n");
            printTitolo(searchResult);
        }
        break;
    }

    case 3:{
        printf("Inserisci il codice del titolo azionario e la data (aaaa/mm/gg) separati da uno spazio: ");
        char code[MAX];
        tempo data = malloc(sizeof(struct tempo_s));
        scanf("%s %d/%d/%d", code, &data->anno, &data->mese, &data->giorno);

        Titolo searchResult = ListSearch(lista, code);
        if (searchResult == NULL){printf("Il titolo azionario non è presente nella lista.\n"); break;}
        Quotazione searchResult2 = SearchQuotazione(searchResult, data);
        
        if (searchResult2 == NULL){
            printf("La quotazione non è presente nella lista.\n");
        } else {
            printf("Quotazione trovata:\n");
            printQuotazione(searchResult2); printf("\n");
        }
        break;
    }

    case 4:{
        printf("Inserisci il codice del titolo, la data più antica e quella più recente (aaaa/mm/gg), tutti separati da spazi: ");
        tempo data1 = malloc(sizeof(struct tempo_s)), data2 = malloc(sizeof(struct tempo_s));
        char code[MAX];
        scanf("%s %d/%d/%d %d/%d/%d", code, &data1->anno, &data1->mese, &data1->giorno, &data2->anno, &data2->mese, &data2->giorno);
        
        Titolo searchResult = ListSearch(lista, code);
        if (searchResult == NULL){printf("Il titolo azionario non è presente nella lista.\n"); break;}
        Quotazione max = SearchMax(searchResult, data1, data2, 0), min = SearchMax(searchResult, data1, data2, 1);
        
        if (max == NULL){
            printf("Non ci sono quotazioni in questo intervallo di date\n");
        } else if (max == min){
            printf("C'è solo una quotazione in questo intervallo di date: ");
            printQuotazione(max); printf("\n");
        } else {
            printf("Quotazione massima: "); printQuotazione(max); printf("\n");
            printf("Quotazione minima: "); printQuotazione(min); printf("\n");
        }
        break;
    }

    case 5:{
        printf("Inserisci il codice del titolo: ");
        char code[MAX];
        scanf("%s", code);
        tempo data1 = malloc(sizeof(struct tempo_s)), data2 = malloc(sizeof(struct tempo_s));
        data1->anno=0; data1->mese=0; data1->giorno=0;
        data2->anno=999999; data2->mese=13; data2->giorno=31;

        Titolo searchResult = ListSearch(lista, code);
        if (searchResult == NULL){printf("Il titolo azionario non è presente nella lista.\n"); break;}
        Quotazione max = SearchMax(searchResult, data1, data2, 0), min = SearchMax(searchResult, data1, data2, 1);
        
        if (max == min){
            printf("C'è solo una quotazione per questo titolo: ");
            printQuotazione(max); printf("\n");
        } else {
            printf("Quotazione massima: "); printQuotazione(max); printf("\n");
            printf("Quotazione minima: "); printQuotazione(min); printf("\n");
        }
        break;
    }

    case 6:{
        printf("Inseisici il codice del titolo e un intero soglia separati da uno spazio (se la differenza tra cammino più lungo e più corto è minore della soglia, il BST non verrà bilanciato): ");
        char code[MAX]; int S;
        scanf("%s %d", code, &S);
        Titolo searchResult = ListSearch(lista, code);
        if (searchResult == NULL){printf("Il titolo azionario non è presente nella lista.\n"); break;}
        bilanciaQuotazioni(searchResult, S);
        printf("Albero bilanciato\n");
        break;
    }

    case 7:{
        printList(lista);
        break;
    }
    
    default:
        break;
    }
}

int printMenu(){
    printf("\n0) Esci\n");
    printf("1) Acquisizione del contenuto di un file contenente un insieme di transazioni.\n");
    printf("2) Ricerca di un titolo azionario.\n");
    printf("3) Ricerca di quotazione in una specifica data, di un titolo azionario.\n");
    printf("4) Ricerca di quotazione minima e massima di un certo titolo, in un certo intervallo di date.\n");
    printf("5) Ricerca di quotazione minima e massima di un certo titolo.\n");
    printf("6) Bilanciamento del BST di quotazioni per un certo titolo.\n");
    printf("7) stampa tutta la lista di titoli.\n");
    printf("\nSeleziona una delle opzioni: ");
    int scelta;
    scanf("%d", &scelta);
    return scelta;
}