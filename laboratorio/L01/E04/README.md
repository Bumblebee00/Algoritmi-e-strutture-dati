# Esercizio numero 4, laboratorio 1

## Descrizione
Questo progetto è parte di un esercizio di laboratorio. Include l'implementazione di algoritmi di ordinamento e ricerca su un dataset di corse in autobus. Permette di:
- stampare a video tutte le corse
- salvare su un file i log di tutte le corse
- stampare a video le corse ordinate per: data, codice tratta, partenza, destinazione
- cercare una corsa per stazione di partenza (utilizzando una funzione di ricerca lineare o dicotomica) (in caso di più corse con la stessa stazione di partenza, verranno stampate tutte le corse trovate)
Per quanto riguarda gli ordinamenti, essi sono salvati in vettori di puntatori a una struttura dati originale.

## Installazione
Seguire questi passaggi per compilare ed eseguire il progetto:
- Navigare nella directory del progetto: `cd E04`
- Compilare il progetto: `gcc -o main src/main.c src/print-help.c src/merge-sort.c src/search.c`
- Eseguire il progetto: `./output`