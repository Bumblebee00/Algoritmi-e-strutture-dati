/* GREEDY non c'è all'esame

Funzione GENERA PROGRAMMA GREEDY.
Soluzione Greedy proposta con ordinamento dei dati per punteggio.
   La soluzione puo' esistere o no:
     - a seconda del gruppo di esercizi letti da file;
     - a seconda dei valori di DD (massima difficoltà della diagonale) e DP
       (massima difficoltà del programma).
   L'ottimo NON e' garantito.


Quindi ordini gli elementi per punteggio decrescente

Costruisci il programma una diagonale alla volta
Tu sai che il programma deve avere:
        - DIFFICOLTA <=DP;
        - ALMENO UN ELEMENTO ACROBATICO AVANTI E ALMENO UN ELEMENTO ACROBATICO
          INDIETRO;
        - ALMENO UNA DIAGONALE IN CUI COMPAIONO ALMENO DUE ELEMENTI ACROBATICI
          IN SEQUENZA.
Per rispettare i seguenti vincoli
        - OGNI DIAGONALE DEVE AVERE ALMENO UN ELEMENTO ACROBATICO;
        - IL PROGRAMMA DEVE AVERE ALMENO UN ELEMENTO ACROBATICO AVANTI E ALMENO
          UN ELEMENTO ACROBATICO INDIETRO;
        - IL PROGRAMMA DEVE AVERE ALMENO UNA DIAGONALE IN CUI COMPAIONO ALMENO
          DUE ELEMENTI ACROBATICI IN SEQUENZA.
Faccio in modo che 
        - LA PRIMA DIAGONALE ABBIA DUE ELEMENTI ACROBATICI IN SEQUENZA;
        - LA SECONDA DIAGONALE ABBIA UN ELEMENTO ACROBATICO INDIETRO;
        - LA TERZA DIAGONALE ABBIA UN ELEMENTO ACROBATICO AVANTI; 
Quindi cicli dai i=0 a i<MAX_DIAG ove i rappresenta la i-esima diagonale del programma;
    Per ogni "i" generi la diagonale mediante una funzione che ti sceglie al massimo MAX_EL elemnti tra quelli letti rispettando tutti i vincoli. Ricordando che il programma deve avere esattamente 3 diagonali, se anche solo una diagonale non viene creata si esce dal ciclo " non è stato possibile trovare la soluzione"; in caso contrario si continua con la creazione della diagonale successiva del programma

*/