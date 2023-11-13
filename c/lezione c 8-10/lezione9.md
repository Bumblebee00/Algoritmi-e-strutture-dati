[12/11/23] In questa lezione si parla brevemente all'inizio di strutture dati contenitore (cioè strutture dati che contengono altri dati), e poi si parla di programmi multi-file, e di come includere i file header in modo da evitare errori di compilazione.

# Strutture dati contenitore
Tipo contenitore (come vettori o liste): involucro che contiene diversi oggetti:
- omogenei
- si possono aggiungere e rimuovere
Le struct NON sono dei contenitori, perchè i dati al loro interno non sono omogenei. per di più sono statiche, non si possono aggiungere o rimuovere elementi.
Altri esempi di contenitori: vettori, liste, pile, code, tabelle di simboli, alberi, grafi
Funzioni tipiche che operano su tipi contenitore:
- creazione di contenitore vuoto
- inserimento di elemento nuovo
- (ricerca forse)
- cancellazione di elemento
- conteggio degli elementi
- accesso agli elementi
- ordinamento degli elementi 
-  distruzione del contenitore

### La struttura involucro (wrapper)
Serve a inglobare tutto ciò (tutte le informazioni) che sereve per gestire il contenitore. Tutto in un solo puntatore.
#### Esempio1:
wrapper per vettore dinamico di interi `int *v` caratterizzato da puntatore al primo dato e dimensione allocata.
```c
typedef struct { int *v;
  int n;
} ivet_t;
```
#### Esempio2:
wrapper per lista con puntatore a head e tail:
```c
typedef struct {
    link head; link tail;
} LIST;
```
Esempio d’uso: inserimento in coda (nota come il codice è molto elegante e semplice):
```c
void listWrapInsTailFast(LISTA *l,Item val) {
    if (l->head==NULL)
        l->head = l->tail = newNode(val, NULL);
    else {
        l->tail->next = newNode(val, NULL);
        l->tail = l->tail->next;
    }
}
```

# Programmi multi-file
Al crescere della complessità dei programmi diventa difficile mantenerli su di un solo file
- la ricompilazione è onerosa
- si impedisce la collaborazione tra più programmatori ciascuno dei quali è indipendente ma coordinato
- non è facile il riuso di funzioni sviluppate separatamente.
Soluzione: modularità e scomposizione su più file

I moduli su più file sono:
- compilati e testati individualmente
- interagiscono in maniera ben definita attraverso interfacce
- implementano l’information hiding, nascondendo i dettagli interni

Soluzione adottata:
Abbiamo un **file di intestazione (header)** .h per dichiarare l’interfaccia, e un **file di implementazione** .c con l’implementazione di quanto esportato e di quanto non esportato
Un modulo è utilizzabile da un programma client: se il client ne include l’interfaccia con una direttiva `#include<headerfile.h>` e se l’eseguibile finale contiene sia client che modulo. La compilazione può essere separata, ma il linker combina i file oggetto di client e modulo in un unico eseguibile. È pportuno che il file .c del modulo includa il suo .h per controllo di coerenza.
Esempio: un client che usa due moduli. i tre file possono essere compilati separatamente, (anche su macchine diverse), basta che il client includa le interfacce dei moduli (file header).
La compilazione dei tre crea tre file oggetto (.o o .obj), che vengono linkati insieme per creare l’eseguibile finale ( o .exe) (vengono anche incluse le librerie lib.).

```(Ricorda: #inlcude è solo come un copia e incolla. Usare #include "..." o #include<...> è lo stesso, semplicemente "" cerca in questa cartella, e <> cerca nelle cartelle di sistema)```

## Architettura SW (a strati)
Caso1: il client.c include un modulo uno.h, e in uno.c è incluso due.h (un altro modulo). non è molto usato\
Caso2: il client.c include sia uno.h che due.h, e in uno.c è incluso due.h. è il più usato.
c'è un vincolo però, uno.h deve essere incluso prima di due.h, perchè due.h usa tipi definiti in uno.h. (uno.h è un file di interfaccia, due.h è un file di implementazione)\
Si può anche includere uno.h in due.h, e non in client.c, ma bisogna stare attenti, perchè se uno.h è incluso in due.h, e due.h è incluso in client.c, allora uno.h è incluso due volte in client.c, e questo può portare a errori. per evitarli, si possono usare le direttive di precompilazione:
```c
#ifndef _UNO_H
#define _UNO_H
// codice di uno.h
#endif
```
che significa: se UNO_H non è definito, allora definiscilo e includi il codice, altrimenti non includere il codice. (UNO_H è una macro, che può essere definita con #define, e può essere undefinita con #undef) (il _ davanti serve a creare un nome particolare che di sicuo non apparira da qualche altra parte).
