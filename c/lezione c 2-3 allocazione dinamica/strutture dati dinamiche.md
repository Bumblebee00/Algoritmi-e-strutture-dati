# Strutture dati dinamiche
dinamiche vuol dire che la dimensione della struttura dati è decisa a esecuzione.
strutture anocra più dinamiche sono quelle la cui dimensione cambia durante l'esecuzione (con realloc)
strutture ancora più dinamiche sono le collezioni (le guarderemo in seguitto) (liste concarenatre).

## Vettori dinamici
uso di puntatore, sfruttando la dualità puntatore-vettore, con entrambi le notazioni
- allocazione mediante malloc/calloc
- rilascio mediante free
- Il resto è identico al vettore sovradimensionato in modo statico.

Esempio:
Acquisire da tastiera una sequenza di numeri reali e memorizzarli in un vettore. Stamparli successivamente in ordine inverso a quello di acquisizione. La quantità di dati non è nota al programmatore, né sovradimensionabile, ma è acquisita come primo dato da tastiera.

    #include <stdio.h>
    #include <stdlib.h>
    int main() {
        float *v; int N, i;
        printf("N? ");
        scanf("%d",&N);
        
        v = (float *) malloc (N*(sizeof (float)));
        if (v==NULL) exit(1);
        
        printf("Inserisci %d elementi\n", N);
        for (i=0; i<N; i++) {
            printf("El. %d: ", i);
            scanf("%f",&v[i]);
        }
        
        printf("Dati in ordine inverso\n");
        for (i=N-1; i>=0; i--)
            printf("El. %d: %f\n", i, v[i]);
        free(v);
    };

### Di dimensione ignota ignota
in questo caso il numero di dati non è noto al programmatore, ma è noto all'inizio del programma. supponiamo invece che non sappiamo quanti dati volgiamo mettere, e che vogliamo mettere dati fino a quando mettiamo uno 0.
#### Soluzione stupida
potremmo usare realloc(). cioè a ogni input riallochiamo un nuovo elemento nel vettore. questo approccio fa schifo perchè è O(n^2) (nel peggiore dei casi). Però vabbe eccola lo stesso in codice:

    #include <stdio.h>
    #include <stdlib.h>
    
    int main() {
        float *v; int N=1, i;
        v = malloc(N*(sizeof (float)));
        printf("Inserisci elementi\n");
        printf("Elemento 0: ");
        while (scanf("%f", &d)>0) {
            if (i==N) {
                // attivato sempre eccetto con i==0
                N = N+1;
                v = realloc(v,N*sizeof(float));
                // controllo di errore omesso
            }
            v[i++] = d;
            printf("Elemento %d: ", i) ;
        }
        printf("Dati in ordine inverso\n");
        for (i=N-1; i>=0; i--)
            printf("El. %d: %f\n", i, v[i]);
        free(v);
    };

#### Soluione intelligente
ogni volta che dobbiamo riallargare, raddopppiamo la dimensione ( avolte si può anche fare *1,5 o simili). in questo caso, sprechiamo potenzialmente fino a mezzo vettore (-1), ma la complessita è O(n logn) (poi in toeria si potrebbe anche riallocare diminuendo, ma nessuno lo fa).

    #include <stdio.h>
    #include <stdlib.h>
    
    int main() {
        float *v; int N, MAXN=1, i=0;
        v = malloc(MAXN*(sizeof (float)));
        printf("Inserisci elementi\n");
        printf("Elemento 0: ");
        while (scanf("%f", &d)>0) {
            if (i==MAXN) {
                MAXN = MAXN * 2;
                v = realloc(v,MAXN*sizeof(float));
                // controllo di errore omesso
            }
            v[i++] = d;
            printf("Elemento %d: ", i) ;
        }
        N = i;
        printf("Dati in ordine inverso\n");
        for (i=N-1; i>=0; i--)
            printf("El. %d: %f\n", i, v[i]);
        free(v);
    };

## Matrici dinamiche
per allocare una matrice nr x nc ho due possibilità.
- Vettore monodimensionale di nc * nr elementi, e l'entrata (i,j) sarà i*nc + j. è meno flessibile
- vettore bidimensionale di nr puntatori a righe, seguito da un iterazione sulle n righe, per allocare un vettore di nc elementi

Esempio: Acquisire da tastiera una sequenza di numeri reali e memorizzarli in una matrice. Stampare successivamente la matrice trasposta. Le dimensioni della matrice (righe e colonne) non sono note al programmatore, né sovradimensionabili, ma sono acquisite come primo dato da tastiera.

#### prima soluzione
    float *v;
    int nr,nc,i,j;

    printf("nr nc: ");
    scanf("%d%d", &nr, &nc);
    v = (float *) malloc(nr*nc*(sizeof (float)));
    if (v==NULL) exit(1);

    for (i=0; i<nr; i++) {
        printf("Inserisci riga %d\n", i);
        for (j=0; j<nc; j++)
            scanf("%f", &v[nc*i+j]);
    }
    printf("Matrice trasposta\n"); for (j=0; j<nc; j++) {
    for (i=0; i<nr; i++)
        printf("%6.2f", v[nc*i+j]);
        printf("\n");
    }
    free(v);

#### seconda soluzione
    float **m; // puntaotre a puntatore
    int nr,nc,i,j;

    printf("nr nc: ");
    scanf("%d%d", &nr, &nc);
    m = (float **) malloc(nr*(sizeof (float *)));
    if (m==NULL) exit(1);

    for (i=0; i<nr; i++) {
        printf("Inserisci riga %d\n", i);
        m[i] = (float *) malloc(nc*sizeof (float));
        if (m[i]==NULL) exit(1);
        for (j=0; j<nc; j++)
            scanf("%f", &m[i][j]);
    }

    printf("Matrice trasposta\n");
    for (j=0; j<nc; j++) {
        for (i=0; i<nr; i++)
            printf("%6.2f", m[i][j]);
        printf("\n");
    }
    for (i=0; i<nr; i++)
        free(m[i]);
    free(m);

molto spesso queste alloczioni saranno fatte da funzioni

Esempio:  Si realizzino due funzioni che allocano (malloc2d) o liberano (free2d) una matrice bidimensionale di elementi di tipo Item con nr righe e nc colonne. La funzione di allocazione malloc2d ha 2 versioni:
- Puntatore ritornato come risultato: malloc2dR dove il puntatore alla matrice è restituito come valore di ritorno della funzione
- Passaggio by pointer/reference: malloc2dP dove il puntatore alla matrice è restituito tra i parametri della funzione
#### versione "alla python"
    typedef ... Item;

    // prototipi
    Item **malloc2dR(int nr, int nc);
    void free2d(Item **m, int nr); ...

    void h (/* parametri formali */) {
        Item **matr;
        int nr, nc;
        ...
        matr = malloc2dR(nr, nc);
        ... /* lavoro su matr */
        free2d(matr,nr);
    }

    Item **malloc2dR(int nr, int nc) {
        Item **m; int i;
        m = malloc (nr*sizeof (Item *));
        for (i=0; i<nr; i++) {
            m[i] = malloc (nc*sizeof (Item));
        }
        return m;
    }

    void free2d(Item **m, int nr) { int i;
        for (i=0; i<nr; i++)
            free(m[i]);
        free(m);
    }

#### altra versione
    typedef ... Item;
    void malloc2dP(Item ***mp, int nr, int nc); // al posto di void ci può essere un qualcosaltro di utile
    void free2d(Item **m, int nr);
    ...
    void h (/* parametri formali */) {
        Item **matr;
        int nr, nc;
        ...
        malloc2dP(&matr, nr, nc);
        ... /* lavoro su matr */
        free2d(matr,nr);
    }
    // mp ha *** perchè è puntatore di vettore di vettori
    void malloc2dP(Item ***mp, int nr, int nc) {
        Item **m; // m è una variabile temporanea
        int i;
        m = (Item **)malloc (nr*sizeof(Item *));
        for (i=0; i<nr; i++)
            m[i] = (Item *)malloc (nc*sizeof(Item));
        *mp = m;
    }
    void free2d(Item **m, int nr) {
        int i;
        for (i=0; i<nr; i++)
            free(m[i]);

        free(m);
    }

#### versione alternativa senza l'uso della variabile temporanea m
    void malloc2dP(Item ***mp, int nr, int nc) {
        int i;
        *mp = malloc (nr*sizeof (Item *));
        for (i=0; i<nr; i++)
            (*mp)[i] = malloc (nc*sizeof (Item)); // attenzione a non scrivetre *mp[i]
    }

## Vettori a dimensione variabile
sono semplicemente vettori la cui dimensione non è nota al programmatore, ma è in una variabile (non sono i vettori a lunghezza variabile). presentano alcuni svantaggi, in quanto
- non si può controllare se l’allocazione è andata a buon fine (mentre invece il puntatore ritornato da malloc/calloc/realloc si può confrontare con NULL): l’effetto è un crash, quando lo stack è troppo piccolo
- Il vettore è cancellato all’uscita dalla funzione, ma il programmatore può pensare che esista ancora e continua a farvi riferimento.

    void inverti(int N) {
        int i;
        float V[N];
        printf("Inserisci %d elementi\n", N);
        for (i=0; i<N; i++) {
            printf("Elemento %d: ", i) ;
            scanf("%f", &v[i]) ;
        }
        printf("Dati in ordine inverso\n");
        for (i=N-1; i>=0; i--)
        printf("Elemento %d: %f\n", i, v[i]);
    }
quindi qui sarebbe un errorone fare return v !!! perchè viene deallocato alla fine della funzione. se proprio vogliamo ritornare v dobbiamo usare malloc.

    float *inverti(int N) {
        int i;
        float *v = (float *)malloc(N*sizeof(float));
        printf("Inserisci %d elementi\n", N);
        for (i=0; i<N; i++) {
            printf("Elemento %d: ", i);
            scanf("%f", &v[i]) ;
        }
        printf("Dati in ordine inverso\n");
        for (i=N-1; i>=0; i--)
            printf("Elemento %d: %f\n", i, v[i]);
        return v;
    }