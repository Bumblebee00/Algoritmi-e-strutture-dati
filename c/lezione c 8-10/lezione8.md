in questa lezione si parla di strutture dati modulari, cioè strutture dati che sono composte da più parti, e i concetti di composizione e aggregazione, cioè come si possono raggruppare dati o riferimenti a dati in un unico dato composto tenendo conto delle relazioni gerarchiche di appartenenza e possesso.

# Strutture dati modulari
Dividere un dato in più pezzi. Hanno senso quando il programma usa solo uno dei vari pezzi del dato.

Esempio:
Bisogna acquisire ripetutamnete dei segmenti, calcolarne la lunghezza e terminare l'acquisizione quando la lunghezza è 0.

Soluzione non modulare:
```c
typedef struct {
    int X, Y;
} punto_t;

int main(void) {
    punto_t A, B;
    int fine=0;
    float l;
    while (!fine) {
        printf("coordinate primo estremo: ");
        scanf("%d%d", &A.X, &A.Y);
        printf("coordinate secondo estremo: ");
        scanf("%d%d", &B.X, &B.Y);
        l=sqrt((B.X-A.X)*(B.X-A.X) + (B.Y-A.Y)*(B.Y-A.Y));
        printf("Segmento (%d,%d)-(%d,%d) l: %f\n", A.X,A.Y,B.X,B.Y,l);
        fine = l==0;
    }
    return 0;
}
```
qua non ha molto senso creare la struttura dati punto, perchè il main ci guarda dentro. avremmo potuto definire due variabili x e y.

Soluzione modulare:
```c
typedef struct { int X, Y; } punto_t;

// qua è come se il punto fosse passato by reference
void puntoScan(FILE *fp, punto_t *pp) {
    fscanf(fp, "%d%d", &pp->X, &pp->Y);
}

void puntoPrint(FILE *fp, punto_t p) {
    fprintf(fp, "(%d,%d)", p.X, p.Y);
}

float puntoDist(punto_t p0, punto_t p1) {
    int d2 = (p1.X-p0.X)*(p1.X-p0.X) + (p1.Y-p0.Y)*(p1.Y-p0.Y);
    return ((float) sqrt((double)d2));
}

int main(void) {
    punto_t A, B; int fine=0; float l;
    while (!fine) {
        printf("primo estremo: "); puntoScan(stdin, &A);
        printf("secondo estremo: "); puntoScan(stdin, &B);
        l = puntoDist(A,B);
        printf("Il segmento ");
        puntoPrint(stdout,A); printf("-"); puntoPrint(stdout,B);
        printf(" ha lunghezza: %f\n", l);
        fine = lunghezza==0;
    }
    return 0;
}
```
qua il lavoro sporco le fanno le funzioni, il main non guarda dentro la struttura dati. In questo modo se cambia la struttura dati, non cambia il main.

## Modularità e allocazione dinamica
```c
typedef struct { int X, Y; } punto_t;

punto_t *puntoCrea(void) {
    punto_t *pp = (punto_t *) malloc(sizeof(punto_t));
    return pp;
}

void puntoLibera(punto_t *pp) {
    free(pp);
}

void puntoScan(FILE *fp, punto_t *pp) {
    fscanf(fp, "%d%d", &pp->X, &pp->Y);
}

void puntoPrint(FILE *fp, punto_t *pp) { fprintf(fp, "(%d,%d)", pp->X, pp->Y); }

float puntoDist(punto_t *pp0, punto_t *pp1) {
    int d2 = (pp1->X-pp0->X)*(pp1->X-pp0->X) + (pp1->Y-pp0->Y)*(pp1->Y-pp0->Y);
    return ((float) sqrt((double)d2));
}

int main(void) {
    punto_t *A, *B; int fine=0; float lunghezza;
    A = puntoCrea();
    B = puntoCrea();
    while (!fine) {
        printf("I estremo: "); puntoScan(stdin, A);
        printf("II estremo: "); puntoScan(stdin, B);
        lunghezza = puntoDist(A,B);
        printf("Segmento ");
        puntoPrint(stdout,A); printf("-"); puntoPrint(stdout,B);
        printf(" ha lunghezza: %f\n", lunghezza);
        file = lunghezza==0;
    }
    puntoLibera(A);
    puntoLibera(B);
    return 0;
}
```
(si potrebbe anche scrivere una variante in cui lo struct è esso stesso un puntatore `typedef struct { int X, Y; } *punto_t;`. in questo modo non ci sono gli asterichi nella definizione delle funzioni).

## Funzioni di creazione e distribuzione
Per evitare memory leak, gestendo in modo modulare strutture dati allocate dinamicamente, è necessario/opportuno che:
- la creazione di un dato sia evidente e gestita con uniformità. Può essere interna al modulo o visibile anche al client
- ci sia un modulo responsabile di ogni struttura dinamica.
- In generale deve distruggere chi ha creato.
- A volte c'è un "trasferimento" (meglio se esplicito/chiaro) di responsabilità

Esempio: estensione dell’esempio sui punti con
- funzione puntoDupl che duplica un punto allocandolo al suo interno
- funzione puntoM che, dati 2 punti, ne ritorna un terzo (allocato internamente) che coincide con quello tra i 2 più lontano dall’origine

```c
punto_t *puntoDupl(punto_t *pp) {
    punto_t *pp2 = puntoCrea();
    *pp2 = *pp;
    return pp2;
}

punto_t *puntoM(punto_t *pp0, punto_t *pp1) {
    punto_t origine = {0,0};
    float d0 = puntoDist(&origine,pp0);
    float d1 = puntoDist(&origine,pp1);
    if (d0>d1)
        return puntoDupl(pp0);
    else
        return puntoDupl(pp1);
}

int main(void) {
    punto_t *A, *B, *max;
    A = puntoCrea(); B = puntoCrea();
    /* input dei 2 punti A e B */
    max = puntoM(A,B);

    printf("Punto piu' lontano: ");
    puntoPrint(stdout,max);
    
    puntoLibera(A);
    puntoLibera(B);
    puntoLibera(max);
    return 0;
}
```
dentro a puntoM c'è una malloc, quindi il main deve ricordarsi di chiamare la free al fondo. quindi il main deve consocere bene la documentazione e studiare.
Esempio di memory leak:
```c
int main(void) {
    punto_t *A, *B, *max;
    A = puntoCrea(); B = puntoCrea();
    /* input dei 2 punti A e B */
    A = puntoM(A,B);

    printf("Punto piu' lontano: ");
    puntoPrint(stdout,max);
    
    puntoLibera(A);
    puntoLibera(B);
    puntoLibera(max);
    return 0;
}
```
in questo main il vecchio valore di A è andato perso. memory leak.

# Composizione e aggregazione
strategie per raggruppare dati o riferimenti a dati in un unico dato composto tenendo conto delle relazioni gerarchiche di appartenenza e possesso. (per arrivare a dire chi è responsabile di cosa (ownership))

Composizione stretta con posseso: A composto B: vuol dire che A possiede B
- per valore: A include B
- per riferimento: A include un puntatore a B
Aggregazione senza possesso: A aggregato a B: A non possiede B
- A include un puntatore a B

## Composizione per valore
Esempio di composizione per valore: simulazione di una creatura che percorre una spezzata (punti su piano cartesiano con coordinate intere non negative):
dato ad alto livello: creatura, che contiene
- nome
- punti
- percorso

```c
typedef struct { int X, Y; } punto_t;

typedef struct {
    char nome[MAXS];
    punto_t posizione;
    float percorsoTotale;
} creatura_t;

void creaturaNew(creatura_t *cp, char *nome, punto_t punto) {
    strcpy(cp->nome,nome);
    cp->posizione = punto;
    cp->percorsoTotale = 0.0;
}

void creaturaSposta(creatura_t *cp, punto_t p) {
    cp->percorsoTotale += puntoDist(cp->posizione,p);
    cp->posizione = p;
}

int main(void) {
    char nome[MAXS];
    punto_t punto;
    creatura_t cr;
    int fine=0;
    printf("Creatura : "); scanf("%s", nome);
    printf("Inizio: "); puntoScan(stdin,&punto);
    
    creaturaNew(&cr,nome,punto);
    while (!fine) {
        printf("Nuovo: "); puntoScan(stdin,&punto);
        if (puntoFuori(punto))
            fine = 1;
        else {
            creaturaSposta(&cr,punto);
            printf("Ora %s: ",cr.nome); puntoPrint(stdout,punto); printf("\n");
        }
    }
    printf("%s ha percorso: %f\n", cr.nome, cr.percorsoTotale);
    return 0;
}
```

Possibili scelte alternative:
- la lunghezza del percorso totale è calcolata dal main.
- modifiche a punto_t e creatura_t mediante funzioni che ricevono la struct originale (passata by value e non by reference come nell'esempio sopra) e ne ritornano il nuovo valore.
- puntoScan non lavora più sul puntatore al punto, ma restituisce il nuovo valore come valore di ritorno
```c
punto_t puntoScan(FILE *fp) {
    punto_t p;
    fscanf(fp, "%d %d", &p.X, &p.Y); return p;
}

/* main */
punto = puntoScan(stdin);
```
- creaturaNew ritorna una struct cui sono stati assegnati i valori passati come parametro
- creaturaSposta non modifica una struct esistente, ma riceve la versione precedente e restituisce il valore aggiornato

## Composizione per riferimento
Un dato contiene un puntatore al dato interno di cui mantiene il completo possesso
Esempio:
- creatura_t contiene 2 puntatori o a stringa (per il nome)
- a punto_t per il punto
le facciamo tutte allocate dinamicamente

```c
typedef struct { int X, Y; } punto_t;

typedef struct {
    char *nome;
    punto_t *posizione;
    float percorsoTotale;
} creatura_t;

punto_t *puntoCrea(void) {
    punto_t *pp = (ppunto_t) malloc(punto_t); return pp;
}

punto_t *puntoDuplica(punto_t *pp) {
    punto_t *pp2 = puntoCrea(); *pp2 = *pp;
    return pp2;
}

void puntoLibera(punto_t *pp) { free(pp); }

void puntoScan(FILE *fp, punto_t *pp) {
    scanf("%d %d", &pp->X, &pp->Y);
}

void puntoPrint(FILE *fp, punto_t *pp) { fprintf(fp, "(%d,%d)", pp->X, pp->Y); }

int puntoFuori(punto_t *pp) { return (pp->X<0 || pp->Y<0); }

float puntoDist(punto_t *pp0, punto_t *pp1) {
    int d2 = (pp1->X-pp0->X)*(pp1->X-pp0->X) + (pp1->Y-pp0->Y)*(pp1->Y-pp0->Y);
    return ((float) sqrt((double)d2));
}

creatura_t *creaturaNew(char *nome, punto_t *punto) {
    creatura_t *cp = malloc(sizeof(creatura_t));
    cp->nome = strdup(nome);
    cp->posizione = puntoDuplica(punto);
    cp->percorsoTotale = 0.0;
}

void creaturaLibera(creatura_t *cp) {
    free(cp->nome);
    puntoLibera(cp->posizione);
    free(cp);
}

void creaturaSposta(creatura_t *cp, punto_t *pp) {
    puntoLibera(cp->posizione);
    cp->posizione = puntoDuplica(pp);
}

int main(void) {
    char nome[MAXS];
    punto_t punto; creatura_t *crp;
    int fine=0; float distanzaTotale = 0.0;
    
    printf("Creatura: "); scanf("%s", nome);
    printf("Inizio: "); puntoScan(stdin,&punto);

    crp = creaturaNew(nome,&punto);

    while (!fine) {
        printf("Nuovo: "); puntoScan(stdin,&punto);
        if (puntoFuori(&punto))
            fine = 1;
        else {
            creaturaSposta(crp,&punto);
            printf("Ora %s: ",crp->nome); puntoPrint(stdout,punto); printf("\n");
        }
    }

    printf("%s ha percorso: %f\n", crp->nome, crp->percorsoTotale);
    creaturaLibera(crp);
    return 0;
}
```

## Aggregazinoe senza possesso
Esempi:
- elenco dei dipendenti di un’azienda, I dipendenti esistono al di là dell’azienda
- volo aereo caratterizzato da compagnia, orario, costo, aeroporti di origine e destinazione. Compagnia ed aeroporti esistono al di là del volo.

Composizione vs. Aggregazione
| Composizione | Aggregazione |
|---------|-------------|
| A contiene B | A fa riferimento a B |
| B tipicamente incluso per valore | B tipicamente esterno, A include puntatore a B |
| A crea/distrugge B | A non è responsabile di creazione/distruzione di B |
| B può essere un riferimento, ma A lo possiede (crea/distrugge) | Oltre al puntatore, possibile riferimento a B con indice o nome |

```c
typedef struct { int X, Y; } punto_t;
typedef struct {
    char *nome;
    punto_t *posizione;
    float percorsoTotale;
} creatura_t;

void puntoScan(FILE *fp, punto_t *pp) {
    fscanf(fp, "%d %d", &pp->X, &pp->Y);
}

void puntoPrint(FILE *fp, punto_t *pp) {
    fprintf(fp, "(%d,%d)", pp->X, pp->Y);
}

float puntoDist(punto_t *pp0, punto_t *pp1) {
    int d2 = (pp1->X-pp0->X)*(pp1->X-pp0->X) + (pp1->Y-pp0->Y)*(pp1->Y-pp0->Y);
    return ((float) sqrt((double)d2));
}

void creaturaNew(creatura_t *cp, char *nome, punto_t *puntoP) {
    cp->nome = nome;
    cp->posizione = puntoP;
    cp->percorsoTotale = 0.0;
}

void creaturaSposta(creatura_t *cp, punto_t *pP) {
    cp->percorsoTotale += puntoDist(cp->posizione,pP);
    cp->posizione = pP;
}
```

