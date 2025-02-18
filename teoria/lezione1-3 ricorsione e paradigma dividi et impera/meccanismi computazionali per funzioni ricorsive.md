[17/10/2023]

Chiamata a funzione: quando si chiama una funzione:
- si crea una nuova istanza della funzione chiamata
- si alloca memoria per i parametri e per le variabili locali
- si passano i parametri
- il controllo passa dal chiamante alla funzione chiamata
- si esegue la funzione chiamata
- al suo termine, il controllo ritorna al programma chiamante, che esegue
l’istruzione immediatamente successiva alla chiamata a funzione.

(un esecuzione di funzione è un cilco fetch - decode - execute
- fetch prende una istruzione dalla memoria
- decode decodifica l'istruzione
- execute esegue l'istruzione)

esiste un pezzo di hardware, il program counter, che tiene traccia dell'indirizzo in memoria della prossima istruzione

una volta arrivati al fondo della funzione, si esegue l'istruzione immediatamente successiva dopo la chiamta della funzione. ma come facciamo a ricordarci dov'è questo indirizzo di ritorno? esiste un altro pezzo di hardware, un pezzo di memoria, organizzato a stack.



# Descrizione di Stack dal punto di vista software
lo stack è un tipo di dato astratto, una struttura dati che permette di inserire e togliere elementi solo da un lato, chiamato top. è come una pila di piatti, dove si può togliere solo il piatto più in alto, e si può mettere un piatto solo sopra gli altri piatti. L'aggiunta di un elemento si chiama push, la rimozione di un elemento si chiama pop. Questa strategia di gestion dati si chiama LIFO (last in first out) (l'ultimo a entrare è il primo che esce) (ci sono anche altre politiche tipo FIFO (first in first out) come la coda alle poste, o non cronologiche ma basate sulla priorità come la coda al pronto soccorso).

Si chiama stack frame (o record di attivazione) la struttura dati che contiene almeno:
- i parametri formali
- le variabili locali
- l’indirizzo a cui si ritornerà una volta terminata l’esecuzione della funzione
- il puntatore al codice della funzione.
Lo stack frame viene creato alla chiamata della funzione, pushato sullo stack, distrutto al suo termine.

Gli stack frame sono memorizzati nello stack di sistema.
Lo stack di sistema ha a disposizione una quantità prefissata di memoria. Quando oltrepassa lo spazio allocatogli, c’è stack overflow.
Lo stack cresce da indirizzi maggiori a indirizzi minori (quindi verso l’alto). Lo stack pointer SP è un registro che contiene l’indirizzo del primo stack frame disponibile. (perchè?)




## Utilizzo dello stack sulle funzioni ricorsive
Cambia qualcosa essendo he la funzione chiamante è la stessa che ciama? no, semplicemente sulo stack viene varicata un nuovo stack frame, solo con variabili diverse

```c
int main() {
    int n;
    printf("Input n (<=12):  "); // input è 3
    scanf("%d", &n);
    printf("%d %lu \n",n, fact(n));
    return 0;
}

unsigned long fact(int n) {
        if(n == 0)
        return 1;
        return n*fact(n-1);
}
```

Stack nei vari momenti del tempo:
[   all'inizio   ] =[ [main] ]
[   dopo fact(3) ] =[ [main] [fact(3)] ]
[   dopo fact(2) ] =[ [main] [fact(3)] [fact(2)] ]
[   dopo fact(1) ] =[ [main] [fact(3)] [fact(2)] [fact(1)] ]
[   dopo fact(0) ] =[ [main] [fact(3)] [fact(2)] [fact(1)] [fact(0)] ]
[   dopo fact(1) ] =[ [main] [fact(3)] [fact(2)] [fact(1)] ]
[   dopo fact(2) ] =[ [main] [fact(3)] [fact(2)] ]
[   dopo fact(3) ] =[ [main] [fact(3)] ]
[   alla fine    ] =[ [main] ]
[   dopo return  ] =[ ]




# Funzioni tail recursive
Una funzione ricorsiva è tail-recursive se la chiamata ricorsiva è l’ultima operazione da eseguire, eccezion fatta per return. Invece in una funzione non tail-recursive, la chiamata ricorsiva NON è l'ultima operazione da fare.

Esempio di tail-recursive:
```c
// nel main bisogna chiamare fact(input, 1);
    unsigned long fact(int n, unsigned long f){
        if (n==0)
            return f;
        return fact(n-1, n*f)
    }
```

qua i calcoli si fanno in fase di discesa. questo è molto importante, perchè prima della chiamata della nuova funzione (cioè push del nuovo stack frame sullo stack) alcuni compilatori (furbi) eliminano già lo stack frame della vecchia funzione, così l'occupazione sullo stack è costante. non ci può essere stack overflow.

Esempio di non tail-recursive:
```c
    unsigned long fact(int n){
        if(n == 0)
            return 1;
        return fact(n-1)*n;
    }
```

qua i calcoli si fanno in fase di risalita (risalita dopo le varie chiamte ricorsive). questo meccanismo funziona perchè abbiamo introdotto lo stack.