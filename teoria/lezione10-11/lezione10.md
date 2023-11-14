[13/11/2023] In questa lezione parliamo di applicazioni/esmpi di algoritmi di ricerca e ordinamento.

# Esempi di algoritmi di ricerca e ordinamento

## Lampadine
Un interruttore controlla più lampadine, e ne scambia lo stato da acceso a spento e viceversa. Si parte da tutte le lampadine spente, vogliamo trovare il più piccolo insieme di interruttori che accenda tutte le lampadine.  Dato che cerchiamo un sottoinsieme di cardinalità minima, è un problema di ottimizzazione.\
Quindi una lampadina è accesa se e solo se il numero di interruttori che la controllano, accesi, è dispari.
Altenativamente possiamo fare xor tra lo stato di ogni lampadina e lo stato di ogni interruttore che la controlla. Se il risultato è 1, la lampadina è accesa, altrimenti è spenta.

### Soluzione
Creiamo il powerset degli interruttori e per ogni sottoinsieme verifichiamo se accende tutte le lampadine. Se sì, lo aggiungiamo alla lista delle soluzioni. Alla fine restituiamo la soluzione di cardinalità minima.
Realizziamo l'iniseme delle parti, la tecnica più adatta in questo caso è quella delle combinazioni, perchè crea prima le combinazioni di cardinalità 1, poi 2, 3, ... fino a n. È la più adatta perchè appena trovo un sottoinsieme che funziona, è sicuro che sia di cardinalità minima.

```c
???
```

# Longest increasing sequence
