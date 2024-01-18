/*
Esercizio n.1: Grafi e DAG
Un grafo pesato, orientato e connesso è memorizzato in un file di testo grafo.txt con il seguente formato:
- sulla prima riga un intero N rappresenta il numero di vertici del grafo
- seguono N righe ciascuna delle quali contiene una stringa alfanumerica, di al massimo 30 caratteri rappresentante l’identificatore univoco del nodo
- seguono un numero indefinito di terne <id_1> <id_2> <peso_arco> a rappresentare gli archi orientati del grafo. Il peso è un valore intero non negativo.

Si scriva un programma C che svolga le seguenti operazioni:
- individuazione di tutti gli insiemi di archi di cardinalità minima la cui rimozione renda il grafo originale un DAG
- costruzione di un DAG rimuovendo, tra tutti gli insiemi di archi generati al passo precedente, quelli dell’insieme a peso massimo. Il peso di un insieme di archi è definito come la somma dei pesi degli archi in esso contenuti
- calcolo delle distanze massime da ogni nodo sorgente verso ogni nodo del DAG costruito al
passo precedente

Strategia:
con la strategia delle combianzioni ripetute controllare tutti i possibili sottoinsiemi di archi, quelli che rendono il grafo un DAG stamparli e salvarli solo se hanno cardinalità minima del minimo trovato finora

Nella struttura dati del grafo c'è la matrice di adiacenza ma anche un vettore di tutti gli archi (A di numero), che viene riempito nella fase di lettura dal file.
La funzione powerset controlla i sottoinsiemi con un vettore di A elementi contenenti zero o uno per arco presente o meno nel sottoinsieme. per ogni chiamata ricorsiva nel caso "arco nel sottoinsime" l'arco viene rimosso dalla matrice di adiacenza, e poi ri agginuto. arrivati alla fine si controlla se è DAG o meno.

*/
#include "grafo.h"

void powerset(int pos, int *set, int* cardinalità_min, int* peso_max, int *set_min, Grafo g);

int main(){
    int N, tmp2;
    char tmp, tmp1;
    Grafo g;

    // lettura da file e creazione grafo
    FILE* fp = fopen("grafo4.txt", "r");
    fscanf(fp, "%d\n", &N);
    g = inizializzaGrafo(N);
    for (int i=0; i<N; i++){
        fscanf(fp, "%c\n", &tmp);
        G_aggiungiInfoNodo(g, creaID(tmp), i);
    }
    while (fscanf(fp, "%c %c %d\n", &tmp, &tmp1, &tmp2) != EOF){
        G_aggiungiArco_ID(g, creaID(tmp), creaID(tmp1), tmp2);
    }
    cristallizzaGrafo(g);
    fclose(fp);
    printf("Grafo iniziale:\n");
    stampaGrafo(g, stdout);
    if (èDAG(g)){ printf("Il grafo è già un DAG\n"); }
    else{
        printf("Sottoinsieme di archi che se rimossi rendono il grafo un DAG:\n");
        int *set = malloc(sizeof(int)*getNumA(g));
        int cardinalità_min = getNumA(g)+1;
        int peso_max = 0; // peso max tra gli insiemi a cardinalità min
        int *set_min = malloc(sizeof(int)*getNumA(g));
        powerset(0, set, &cardinalità_min, &peso_max, set_min, g);

        printf("\n\n\nDi questi sottoinsiemi ho scelto quello con cardinalità minima e peso massimo [ ");
        for (int i=0; i<getNumA(g); i++){
            if (set_min[i] == 1){ printf("( "); stampaID(getArco_int(g, i).from); printf(" -> "); stampaID(getArco_int(g, i).to); printf(" ), "); }
        }
        printf("] con peso = %d, e ho rimosso tutti i suoi archi dal grafo rendendolo un DAG. Ecco il nuovo Grafo:\n", peso_max);
        Arco *to_remove = malloc(sizeof(Arco)*cardinalità_min);
        int j = 0;
        for (int i=0; i<getNumA(g); i++){
            if (set_min[i] == 1){ to_remove[j] = getArco_int(g, i); j++; }
        }
        for (int i=0; i<cardinalità_min; i++){
            G_rimuoviArco_ID(g, to_remove[i].from, to_remove[i].to);
        }
        stampaGrafo(g, stdout);
    }

    printf("\n\n\nCalcolo delle distanze massime da ogni nodo sorgente verso ogni nodo del DAG costruito:\n");
    int n_sorgenti;
    id *sorgenti = G_IndividuaNodiSorgenti(g, &n_sorgenti);
    for (int i=0; i<n_sorgenti; i++){
        for (int j=0; j<N; j++){
            if (confrontaID(sorgenti[i], getIDfromIndex(g, j)) != 0){
                printf("Distanza massima da "); stampaID(sorgenti[i]); printf(" a "); stampaID(getIDfromIndex(g, j)); printf(" = %d\n", G_distanzaMassima(g, sorgenti[i], getIDfromIndex(g, j)));
            }
        }
    }
}

void powerset(int pos, int *set, int* cardinalità_min, int* peso_max, int *set_min, Grafo g){
    if (pos+1 > getNumA(g)){
        if (èDAG(g)){
            int cardinalità = 0;
            for (int i=0; i<getNumA(g); i++){
                if (set[i] == 1){
                    printf("("); stampaID(getArco_int(g, i).from); printf("->"); stampaID(getArco_int(g, i).to); printf("), ");
                    cardinalità++;
                }
            }
            printf("\n");

            int swap = 0;
            if (cardinalità < *cardinalità_min){
                *cardinalità_min = cardinalità;
                swap = 1;
            } else if (cardinalità == *cardinalità_min){
                int peso = 0;
                for (int i=0; i<getNumA(g); i++){ if (set[i] == 1){ peso += getArco_int(g, i).wt; } }
                if (peso > *peso_max){
                    *peso_max = peso;
                    swap = 1;
                }
            }
            if (swap){
                for (int i=0; i<getNumA(g); i++){ set_min[i] = set[i]; }
            }
        }
        return;
    }

    set[pos] = 0; // arco non nel powerset
    powerset(pos+1, set, cardinalità_min, peso_max, set_min, g);
    set[pos] = 1; // arco nel powerset
    Arco tmp = getArco_int(g, pos);
    G_rimuoviArcoDaM(g, tmp);
    powerset(pos+1, set, cardinalità_min, peso_max, set_min, g);
    G_aggiungiArcoAM(g, tmp);
}