[30/11/23] In questa lezione risolveremo alcuni problemi con il paradigma di programmazione dinamica.

- [Esempi di problemi risolvibili con programmazione dinamica](#esempi-di-problemi-risolvibili-con-programmazione-dinamica)
  - [Longest Increasing Sequence](#longest-increasing-sequence)
      - [Soluzione dinamica](#soluzione-dinamica)
  - [Lo zaino discreto](#lo-zaino-discreto)
- [Paradigma della memorization](#paradigma-della-memorization)
  - [Fibonacci](#fibonacci)
  - [Sequenza di Hofstadter H](#sequenza-di-hofstadter-h)
  - [Altre cose boh](#altre-cose-boh)

# Esempi di problemi risolvibili con programmazione dinamica

## Longest Increasing Sequence
Data una sequenza di N interi\
$X = \{x_1, x_2, ..., x_n\}$\
trovare la più lunga sottosequenza crescente.

Esempio:\
$X = \{0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15\}$\
esistono 4 LIS con k=6:
$\{0,2,6,9,11,15\}$ $\{0,4,6,9,11,15\}$ $\{0,2,6,9,13,15\}$ $\{0,4,6,9,13,15\}$

La soluzione ricorsiva ha complessità $O(2^n)$\
La soluzione con programmazione dinamica ha complessità $O(n^2)$

#### Soluzione dinamica
Strutture dati:
- vettore val con la sequenza di interi
- vettore P con l'indice del predecessore di ogni elemento nella sua LIS
- vettore L con la lunghezza della LIS fino a quell'elemento

il codice si trova in `04LIS.c`

## Lo zaino discreto
Ci sono un tot di oggetti con un certo peso e un certo valore. abbiamo un peso massimo. Trovare la combinazione di oggetti che massimizza il valore senza superare il peso massimo.

# Paradigma della memorization
Approccio simile al divide et impera ricorsivo, quindi top-down, ma che prevede la memorizzazione delle soluzioni ai sottoproblemi. Evita di risolvere problemi già trattati

## Fibonacci
```c
unsigned long fib(int n, unsigned long *knownF) {
  unsigned long t;
  if (knownF[n] != -1)
    return knownF[n];
  if(n == 0 || n == 1) {
    knownF[n] = n;
    return(n);
  }
  t = fib(n-2, knownF) + fib(n-1, knownF);
  knownF[n] = t;
  return t;
}
```

## Sequenza di Hofstadter H
Questa sequenza è definita come:
$$
H(n) = \begin{cases}
  0 & \text{se } n = 0 \\
  n - H(H(H(n-1))) & \text{se } n > 0
\end{cases}
$$
I suoi primi valori sono:
0, 1, 1, 2, 3, 4, 4, 5, 5, 6, 7, 7, 8, 9, 10, 10, 11

```c
int Hmemo(int n, hm *hmemo) {
  if (n == 0) {
    hmemo[n].val  = 0;
    hmemo[n].calc = 1;
    return hmemo[n].val;
  }
  if (hmemo[n].calc == 1)
    return hmemo[n].val;
  hmemo[n].val = n- Hmemo(Hmemo(Hmemo(n-1, hmemo), hmemo), hmemo);
  hmemo[n].calc = 1;
  return hmemo[n].val;
}
```

## Altre cose boh