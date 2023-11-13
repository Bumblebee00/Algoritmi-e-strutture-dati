Ho un insieme di punti Q. Voglio trovare il poligono convesso di area minima che contiene tutti i punti di Q (anche sul perimetro possono stare).

### Soluzione meccanica:
pianto dei chiodi nel piano, mmetto un elastico all'esterno e lo stringo sempre di più.

### Soluzione brute force
prendo tutti i punti e faccio tutte le combinazioni possibili di punti. Per ogni combinazione, controllo se è convessa. Se lo è, calcolo l'area e tengo quella minima. ( complessità esponenziale )

### Graham Scan (1972)
- trovo il punto più in basso p0 (y minore) (perchè di sicuro sarà nel perimetro del poligono convesso)
- ordino tutti gli altri punti per angolo crescente rispetto al punto trovato prima (con quicksort)
- prendo i primi tre punti e li metto nello stack
- prendo il quarto punto e lo metto nello stack. Se la struttura non è convessa, tolgo il penultimo punto inserito (così è convessa).
- ripeto per tutti i punti

##### Strutture dati
