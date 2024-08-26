Soluzione: istruzioni per allocare e de-allocare dati (memoria) in modo esplicito:
o in funzione di dati forniti da chi esegue il programma
o allocazioni e de-allocazioni sono (ovviamente) previste e gestite dall’autore del
programma
o la componente del sistema operativo che si occupa di allocazione/deallocazione
è l’allocatore di memoria dinamica
o la memoria dinamica si trova in un’area detta heap
o alla memoria dinamica si accede solo mediante puntatore


La dimensione della struttura dati dinamica può essere
- fissa determinata in fase di esecuzione
- modificabile (aumentabile o diminuibile) mediante riallocazione

Qualunque struttura dinamica ha 3 fasi:
- creazione (allocazione) esplicita
- utilizzo con possibilità di: 
    - riallocazione
    - Inserimenti
    - cancellazioni
- distruzione (de-allocazione) esplicita


===Funzione malloc
    void* malloc(size_t size):
size è quanti byte vogliamo. non è come l'aritmetica del puntatore che conta la dimensione del tipo (size_t è come unsigned int)
la malloc restituisce un puntatore di tipo void* (perchè, ripetiamo, la malloc non interessa il tipo che c'è dentro) che è il puntatore alla struttura dati dinamica. se non c'è abbastanza spazio ritorna l'indirizzo NULL

Regole:
- Per usare malloc occorre includere <stdlib.h>
- La dimensione del dato è responsabilità del programmatore. Solitamente si ricorre all’operatore sizeof per determinare la dimensione (in byte) di un dato: sizeof(<tipo>) o sizeof <espressione riconducibile a tipo>
- Al dato allocato si accede unicamente tramite puntatore. Il puntatore ritornato è opaco, tocca al programmatore passare al tipo desiderato mediante assegnazione a opportuna variabile puntatore

Forma generale di chiamata a malloc:
quattro possibilità:
tipo di sizeof (basato su un tipo o su una variabile/espressione)
presenza di cast esplicito o n o

cast implicito:
    p = malloc(sizeof (<tipo>));
    p = malloc(sizeof <espr>);

cast esplicito:
    p = (<tipo> *) malloc(sizeof (<tipo>));
    p = (<tipo> *) malloc(sizeof <espr>);

Esempio:
    #define MAX 20
    struct stud {char cognome[MAX];int matr; };
    struct stud *s; // oer adesso non contiene nulla

    // sizeof(struc stud) o sizeof(struc *s) restituiscono entrambe la stessa cosa (24 byte) quindi per alocare memoria posso scrivere egualmente

    // cast implicito
    s = malloc(sizeof(struct stud));
    s = malloc(sizeof(*s)); // se hai un vettore v = malloc(sizeof(*v)*n);

    // cast esplicito
    s = (struct stud *)malloc(sizeof(struct stud));
    s = (struct stud *)malloc(sizeof(*s));

Errori comuni:
dimensione richiesta inferiore alla necessaria a causa di uso del tipo errato in sizeof:
    double *pd;
    struct stud *ps, *v;
    int n;
    ...
    pd = malloc(sizeof(int))// <- ERRORE
    // questo errore non viene segnalato dal compilatore, lui semplicemente restituisce un puntatore al primo byte, e ti libera per te 4 byte. quindi se tu provi a scrivere/leggere facendo *pd =, dato che pd è double (8 byte), starai leggendo e scrivendo anche nella parte non liberata. probabilmente farai danni.
Un cast esplicito avrebbe reso più semplice l’identificazione dell’errore (a me mentre controllo il codice):
    pd = (double *)malloc(sizeof(int))

con struct:
    ps=(struct stud *)malloc(sizeof(struct stud *)) // struc stud è 24 bytes, ma struct stud * è 8 bytes perchè è solo un puntatore

con vettori:
    v = malloc (sizeof *v); // ho dimenticato n la dimensione del vettore
    v = (struct stud *)malloc (n) // senza speranza

vettori di puntatori:
    struct stud **ps;
    ...
    ps = malloc(n*sizeof(struct stud)); // dovrebbe essere struct stud * perchè io sto allocando per vett di puntatori. il tipo è puntatore

    o 

    struct stud **ps;
    ...
    ps=(struct stud *)malloc(n*sizeof(struct stud *)); // dovrebbe essere struct stud **, perchè ps è un doppio puntatore

Ora, se la dimensione allocata è maggiore di quella richiesta, vabbès ei inefficiente. Se la dimensione è minoe è molto grave, perchè stai leggendo e scrivendo zone che non dovrebbero essere. (meglio un crash che un errore subdolo)

Memoria dinamica insufficiente:
    p = malloc(sizeof(int));
    if (p == NULL)
        printf("Errore di allocazione\n");
    else

la malloc è O(1) + il tempo per trovare la memoria (indipendente dalla mameoria allocata)

===Funzione Calloc
è O(n) (a causa dell'azzeramento) quando allochi n byte. è equivalente a malloc(n*size); con memoria ritornata azzerata. E stata pensata per i vettori, quindi riceve due parametri:
    void* calloc (size_t n, size_t size);

===Funzione Free
Tutta la memoria allocata dinamicamente com malloc/calloc viene restituita tramite la funzione free (<stdlib.h>)
    void free (void* p);
dove p punta alla memoria (precedentemente allocata) da liberare. dato chè l'allocatore si ricorda già la dimensione della memoria allocata, tu gli dai il puntatore al primo elemento (p) e lui si riprende tutta la memoria. perchè lui vuole riprendersela proprio tutta. Nota: p non scompare, p sta nello stack. la free non elimina p, la free elimina la memoria puntata da free.

(In molti programmi piccoli piccoli non si scrive neanche la free, perchè non finisce la memoria)
Uso di free consigliato, ma non obbligatorio. (è un po come quando non chiudi i file)
Fino a qualche anno fa Windows non metteva le free.

Memory leak: perdi della memoria e non puoi piu usarla
    int *vett = malloc(10 * sizeof(int));
    ... (qua non c'è la free) ...
    vett = malloc(25 * sizeof(int));
i 10 byte di prima, sono persi, perchè ho sovrascritto il loro puntatore ( con i puntatore ai nuovi 25 ) e non posso più liberarli.

===Funzione Relloc
in generale serve per riallocare memoria già allocata
    p = malloc(oldSize);
    ...
    p = realloc(newSize); // dove new size può essere > o < di old size

se vogliamo ridurre la memoria, questo è sempre possibile, ma in generale è sconsigliato.
se vogliamo ingrandire, la riallocazione può
- essere impossiblie
- possibile, perchè alla fine della memoria allocata c'è spazio vuoto per ingrandire (in questo caso il puntatore ritornato è lo stesso di prima, cambia semplicemente la tabellina interna del compilatore) (in qiesto caso il costo è O(1))
- possiblie, ma alla fine della memoria precedente non c'è abbastanza spazio. in questo caso si trova un altro spazio, e si copia tutta la memoria allocata prima nel nuovo posto. in questo caso la realloc ha un costo O(n)

    // non è la vera implementazione – serve solo per capirla
    void* realloc (void* p, size_t size) {
        size_t oldSize = cercaDimensione (p, ...); // cerca in tabella la dimensione precedente
        if (/*si può espandere o ridurre*/) {
            cambiaDimensione (p, ...); // togli o aggiungi un pezzo in fondo
            return p;
        } else {
            void *newp = malloc(size); // nuova allocazione copiaMemoria(newp,p,min(size,oldSize));
            free(p);
            return newp;
        }
    }





















