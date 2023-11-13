[13/11/2023] In questa lezione si risolve un problema di aereoporti utilizzando i concetti visti nella lezione 9 (strutture dati contenitore e programmi multi-file).

# Esempi con aereoporti:
Dati due file contenenti un elenco di aeroporti e un elenco di voli. costruire una struttura dati contenente le informazioni di aeroporti e voli. I file (nomi ricevuti come argomenti al main) contengono nella prima riga il numero totale di aeroporti/voli. I formati sono (C indica codice):
<C aeroporto> <nome citta>, <nome aeroporto>
<C aeroporto p> <C aeroporto A> <C volo> <oraP> <oraA>

Esempio file:
```txt
28
AOI Ancona, Marche
BRI Bari, Palese
MXP Milano, Malpensa
FCO Roma, Fiumicino
TPS Trapani, Birgi
TRN Torino, S. Pertini
...
```
```txt
42
AOI BGY FR4705 17:45 19:25
AOI BGY FR4887 19:40 21:20
AOI FLR VY1505 19:35 20:50
CAG AOI FR8727 10:25 11:50 
TRN FCO AZ1430 19:05 20:15
...
```

### Strutture dati
Possono essere **composte**:
```c
typedef struct {
    char nomeAeroporto[M1];
    char nomeCitta[M1];
    char codice[M2];
} aeroporto_t;

typedef struct {
    int h, m;
} orario_t;

typedef struct {
    struct {
        aeroporto_t citta;
        orario_t ora;
    } partenza, arrivo; // due elementi di questa struct
    char codiceVolo[M2];
} volo_t;
```
o **aggregate** (composte per riferimento):
```c
typedef struct {
    char *nomeAeroporto; // ci permette di allocare dinamicamente la stringa
    char *nomeCitta; // questa definizione non lo dice ancora, ma str. dati aggregata indica che è allocata e gestita da qualche altra parte (magari in una lista di nomi città)
    char codice[M2];
} aeroporto_t;

typedef struct {
    struct {
        aeroporto_t *citta; // questa definizione non lo dice ancora, ma str. dati aggregata indica che è allocata e gestita da qualche altra parte (magari in una lista di aeroporti)
        orario_t ora;
    } partenza, arrivo;
    char codiceVolo[M2];
} volo_t;
```
### Collezioni di aereoporti e voli:
un wrapper per collezione di aereoporti:
```c
typedef struct {
    aeroporto_t *elenco;
    int nMax, n;
} aeroporti_t;

typedef struct {
    volo_t *elenco;
    int nMax, n;
} voli_t;
```
Nota: non è molto utile il nMax, ma lo mettimao per mostrare che nel wrapper ci piuò stare tanta roba.\
In questo caso con puntatori, se `tabV` è la tabella dei voli, allora
- `tabV->elenco[i]` è il volo i-esimo
- `tabV->elenco[i].partenza->citta` è l’aeroporto di partenza del volo i-esimo
- e così via

# Versione Base (v1): con array
(vadi nella cartella v1 tutti i file, commentati dettagliatamente)
### Modulo aeroporti (`aeroporti.h`):
Tipi definiti:
- aeroporto_t: tipo composto (con riferimenti a nomi)
  ```c
    typedef struct {
        char *nomeAeroporto, *nomeCitta;
        char codice[M2];
    } aeroporto_t;
    ```
- aeroporti_t: wrapper di collezione di aeroporti, realizzata come vettore
    ```c
    typedef struct {
        aeroporto_t *elenco;
        int na, nmax;
    } aeroporti_t;
  ```

Prototype delle funzioni:
```c
// alloca sia l'oggetto aeroporti_t, sia l'array di aeroporto_t, ma non le stringe in aereoporto_t. quelle le deve allocare chi legge dal file (leggiAeroporti)
aeroporti_t *allocaAeroporti (int max);
void liberaAeroporti (aeroporti_t *ap);
// legge da file e crea il vettore di aeroporti_t (chiamando anche allocaAeroporti)
void scriviAeroporti (char *nomeFile, aeroporti_t *aeroporti);
// scrivi su un file di output la lista di aeroporti
aeroporti_t *leggiAeroporti (char *nomeFile);
// ricerca lineare
aeroporto_t *cercaAeroportoC (aeroporti_t *aeroporti, char *codice);
```

### Modulo voli (`voli.h`):
- volo_t: tipo aggregato (i riferimenti ad aeroporti sono esterni) 
    ```c
    typedef struct volo_s {
        struct {
            aeroporto_t *citta;
            orario_t ora;
        } partenza, arrivo;
        char codiceVolo[M2];  
    } volo_t;
    ```
- voli_t: wrapper di collezione di voli, realizzata come vettore
    ```c
    typedef struct {
        volo_t *elenco;
        int nv, nmax;
    } voli_t;
    ```

Prototype delle funzioni:
```c
// libera sia l'array che il wrapper
void liberaVoli (voli_t *vp);
void scriviVolo (FILE *f, volo_t *vp);
// scrive su un file di output la lista di voli (chiama scriviVolo)
void scriviVoli (char *nomeFile, voli_t *voli);
// alloca sia il wrapper voli_t, sia un array di volo_t (max elementi)
voli_t *allocaVoli (int max);
// chiama allocaVoli e legge da file i voli (chiamando anche cercaAeroportoC(); leggiOra(); )
voli_t *leggiVoli (char *nomeFile, aeroporti_t *aeroporti);
orario_t leggiOra (FILE *fp);
```

### Modulo principale (`main.c`):
Il main semplicemente
- legge gli aeroporti
- legge i voli
- fa delle elaborazioni sui dati
- scrive su file di output e libera le strutture dati
(e ovviamente `#include "aeroporti.h"` `#include "voli.h"`)

# Versione 2 (v2): con liste
(vadi nella cartella v2 tutti i file, commentati dettagliatamente)
### Modulo aeroporti (`aeroporti.h`):
come prima ma nel wrapper `aeroporti_t` non c'è un semplice vettore di `aeroporto_t` ma una lista (implementata con puntatori).
```c
typedef struct aeroporto_s *linkAeroporto, aeroporto_t;

struct aeroporto_s {
  char *nomeAeroporto;
  char *nomeCitta;
  char codice[M2];
  linkAeroporto next;
};

typedef struct {
  linkAeroporto head;
  linkAeroporto tail;
} aeroporti_t;
```
i prototipi delle funzioni cambiano di conseguenza.
### Modulo voli (`voli.h`):
come prima ma nel wrapper `voli_t` non c'è un semplice vettore di `volo_t` ma una lista (implementata con puntatori).
```c
struct volo_s {
  struct {
    aeroporto_t *citta;
    orario_t ora;
  } partenza, arrivo;
  char codiceVolo[M2];  
  linkVolo next;
};

typedef struct {
  linkVolo head;
  linkVolo tail;
} voli_t;
```
i prototipi delle funzioni cambiano di conseguenza.

### Modulo principale (`main.c`):
il main è ESATTAMENTE uguale.

# Versione 3 (v3): con indici
...