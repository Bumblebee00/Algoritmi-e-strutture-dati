[24/11/2023] In questa lezione continuiamo a parlare di applicazioni/esmpi di algoritmi di ricerca e ordinamento. Indice completo del file markdown:

- [Longest Increasing Sequence](#longest-increasing-sequence)
  - [Algoritmo](#algoritmo)
  - [Strutture dati](#strutture-dati)
  - [Codice](#codice)
- [Le 8 regine](#le-8-regine)
  - [Soluzione 0](#soluzione-0)
  - [Soluzione 1](#soluzione-1)
  - [Soluzione 2](#soluzione-2)
  - [Soluzione 3](#soluzione-3)
  - [Soluzione 4](#soluzione-4)
- [Aritmetica verbale](#aritmetica-verbale)
  - [Sturttura dati](#sturttura-dati)
  - [Algoritmo](#algoritmo-1)

# Longest Increasing Sequence
Data una sequenza di N interi\
$X = \{x_1, x_2, ..., x_n\}$\
trovare la più lunga sottosequenza crescente.

Esempio:\
$X = \{0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15\}$\
esistono 4 LIS con k=6:
$\{0,2,6,9,11,15\}$ $\{0,4,6,9,11,15\}$ $\{0,2,6,9,13,15\}$ $\{0,4,6,9,13,15\}$

## Algoritmo
- generare tutti i sottoinsiemi di elementi di X (non necessario l’insieme vuoto)
- per ogni sottoinsieme applicare una funzione di verifica di validità (controllo di monotonia stretta)
- problema di ottimizzazione: tenere traccia della soluzione ottima corrente e confrontarla con ciascuna soluzione generata
- tra le soluzioni valide, scegliere una tra quelle a massima cardinalità.

Genereremo l'insieme delle parti con disposizioni ripetute di n elementi. Si potrebbe anche introdurre un criterio di pruning durante la generazione dei sottoinsiemi, controllando a ogni step che la sequenza sia increasing.

## Strutture dati
Useremo:
- vettore v di n interi per i valori
- vettore s e best_s di n interi per soluzione corrente e soluzione migliore
- interi l e best_l per lunghezza corrente e lunghezza migliore.

## Codice
( vedi file `04 Codice C per esempi di problemi di ricerca e ottimizzazione/02LIS.c` )

# Le 8 regine
Proposto da Max Bezzel nel 1848. Data una scacchiera 8x8, posizionare 8 regine in modo che nessuna possa mangiare un’altra. Questo problema si può facilmente generalizzare a n regine su una scacchiera n x n. Ecco le soluzioni per n 0-14:

| n | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
| soluzioni | 1 | 0 | 0 | 2 | 10 | 4 | 40 | 92 | 352 | 724 | 2680 | 14200 | 73712 | 365596 |

## Soluzione 0
Ogni cella puù contenere o meno una regina. Generiamo tutti i sottoinsiemi possibili ($2^{64} \approx 1.84 \cdot 10^{19}$) e controlliamo se sono soluzioni valide. È un modello di merda. Il codice si può trovare nel file `03otto-regine-powerset.c`.

L'unica parte interessante di questo codice è la funzione `controlla`. che controlla per ogni riga, colonna, diagonale e altra diagonale se c'è più di una regina.

## Soluzione 1
Si piazzano 8 regine sulle 64 caselle, usando il modello di disposizioni semplici (quindi considerando le varie regine come distinte. si avranno ripetizioni). I casi da controllare sono $64 \cdot 63 \cdot 62 \cdot 61 \cdot 60 \cdot 59 \cdot 58 \cdot 57 \approx 1.78 \cdot 10^{14}$. Il codice si può trovare nel file `04otto-regine-disp-sempl.c`.

## Soluzione 2
Adessu usiamo invece il modello di combinazioni semplici, qundi lo spazio di ricerca è ${ 64 \choose 8 } = 4426165368$. Il codice si può trovare nel file `05otto-regine-comb-sempl.c`.

## Soluzione 3
Anzichè avere una struttura dati bidimensionale, posso avere un vettore di 8 interi, dove ogni intero rappresenta la colonna in cui si trova la regina nella riga corrispondente. Quindi ho 8 caselle, e ogniuna può contenere un intero da 0 a 7. È chiaramente un disposizione con ripetizioni, e lo spazio di ricerca è $8^8 = 16777216$. La funzione `controlla` cambia, e bisogna controllare solo colonne e diagonali.
Il codice si può trovare nel file `06otto-regine-disp-ripet.c`.

## Soluzione 4
Come la 3 ma non mettiamo la regina in una colonna già occupata. Abbiamo da controllare $8! = 40320$ casi. Il codice si può trovare nel file `08otto-regine-perm-sempl-ott.c`.

# Aritmetica verbale
S E N D + M O R E = M O N E Y\
ogni lettera rappresenta una cifra diversa. La prima cifra significativa non può essere 0. sono numeri in base 10. quindi ci sono 10! = 3628800 possibili soluzioni.

## Sturttura dati
avremo un vetttore di char che contiene le lettere distinte `lett_dist`, poi avremo una tabella di simboli che ha un campo char e un int

## Algoritmo
- riempire lettere con lett_dist caratteri distinti (funzione setup che usa la funzione di servizio trova_indice)
- calcolare le permutazioni di 10 elementi (funzione permuta)

# Sudoku
Prima diciamo un pò di probelmi simili
### 36 ufficiali di Eulero
In un reggimento ci sono 6 ufficiali di ranghi diversi (i 6 pezzi degli scacchi, quindi: Re, Regina, Alfiere, Cavallo, Torre, Pedone). Ci sono 6 reggimenti (associati a 6 colori). Quindi un totale di 36 ufficiali. È possibile disporli in un quadrato 6x6 in modo che ogni riga e ogni colonna contengano un ufficiale di ogni rango e di ogni colore?

questo problema è un caso particolare del:
### Quadrato latino (aka sudoku generalizzato)
C'è un quadrato n x n, e abbiamo n simboli distinti, ripetuuti n volte. È possibile riempire il quadrato in modo che ogni riga e ogni colonna contengano tutti i simboli distinti?

questo problema è un caso particolare del:
### Quadrato greco latino
Come due quadrati latini diversi, quindi con n simboli er il primo e n per il secondo, ma poi sono messi enllo stesso quadrato, e c'è il requirement addizionale che ogni cella contenga una coppia di simboli distinti (quindi non è possibile avere due volte la stessa coppia di simboli).

Eulero ipotizzò che i quadrati greco latini esistono solo per n multipli di 4. questo è falso, esistono per $n \geq 3$ con l'eccezione di $n=6$.