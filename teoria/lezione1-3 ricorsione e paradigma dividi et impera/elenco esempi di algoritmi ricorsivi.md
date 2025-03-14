Mostriamo adesso alcuni esempi di algoritmi ricorsivi semplici
# Calcolo del Fattoriale
n! = n * (n-1)!
1! = 1
0! = 1

esempio di decrease and conquer, con a (numero di sottoproblemi in cui il problema è divso) = 1, k' (fattore che diminuisce la dimensione del problema) = 1
```c
unsigned long fact(int n) {
if ((n == 0) || (n == 1))
    return 1;
return n*fact(n-1);
}
```

## Analisi complessità:
D(n) = C(n) = O(1)
T(n)= O(1) + T(n-1) + O(1)
    = O(1) + O(1) + T(n-2) + O(1) + O(1)
    = 2n * O(1) = O(n)


# Numeri di fibonacci
fib(n) = finb(n-1) + fib(n-2)
fib(1) = 1
fib(0) = 0

esempio di decrease and conquer, con a=2, k'_1 = 1 k'_2 = 2
```c
unsigned long fib(int n) {
if ((n == 0) || (n == 1))
    return n;
return fib(n-1) + fib(n-2);
}
```

## Analisi complessità:
D(n) = C(n) = O(1)
T(n)= O(1) + T(n-1) + T(n-2) + O(1)
T(n) = O(phi^n)


# Massimo comune divisore
Algoritmo inefficiente basato sulla socmposizione inf attori primi
x = p1^e1 * p2^e2 * ... * pn^en
y = p1^f1 * p2^f2 * ... * pn^fn
gcd(x,y) = p1^min(e1,f1) * p2^min(e2,f2) * ... * pn^min(en,fn)

## Algoritmo di Euclide(IV sec. aC):
```c
int gcd(int x, int y) {
if(x == y)
    return x;
if (x > y)
    return gcd(x-y, y);
return gcd(x, y-x);
}
```

## Algoritmo di Euclide-Lamé (1844)-Dijkstra (1976):
```c
int gcd(int x, int y) {
if(y == 0)
    return x;
return gcd(y, x % y);
}
```

### Analisi complessità:
D(n) = C(n) = O(1)
...
T(x,y) = O(log y)


# Massimo di un vettore
(esempio di spora)
O(n)

# Prodotto di due Numeri
Ecco un algoritmo ricorsivo per il prodotto di due numeri x, y di n cifre (n=2^k per semplicità).
1234 può essere scritto come 12 * 100 + 34
5678 = 56 * 100 + 78

e in generale divido x in x_d e x_s, y in y_d e y_s
x * y = (x_s * 100 + x_d)(y_s * 100 + y_d) = x_s * y_s * 10000 + (x_s * y_d + x_d * y_s) * 100 + x_d * y_d

ancora più in generale se il numero ha n cifre
x = x_d * 10^(n/2) + x_s
y = y_d * 10^(n/2) + y_s
x * y = (x_s * 10^(n/2) + x_d)(y_s * 10^(n/2) + y_d) = x_s * y_s * 10^n + (x_s * y_d + x_d * y_s) * 10^(n/2) + x_d * y_d

quindi se a sua volta x_d non è banale (tabellina pitagorica) spezzo di nuovo.

In questo algoritmo ogni step dividiamo per 4 sottoproblemi, di dimensione la metà, quindi a=4, b=2
```c
long product(int *x, int lx, int rx, int *y, int ly, int ry, int n) {
long term1,term2, term3;
if(n == 1)
    return (x[lx]*y[ly]);
term1 = product(x, lx, (lx+rx)/2, y, ly, (ly+ry)/2, n/2);
term2 = product(x, lx, (lx+rx)/2, y, ly+n/2, ry, n/2) + product(x, lx+n/2, rx, y, ly, (ly+ry)/2, n/2);
term3 = product(x, lx+n/2, rx, y, ly + n/2, ry, n/2);
return term1 * pow(10,n) + term2 * pow (10, n/2) + term3;
}
```

## Analisi di complessità

(ricorda: Somma(x^i, 0, k) = (x^(k+1) - 1)/(x-1) )
(ricorda: a ^ logbn = n ^ logba)

Equazione alle ricorrenze:
D(n) = 1 // solo spezzare il vettore
// moltiplicare per 10^qualcosa e sommare i termini. moltiplicare è solo uno shift, e moltiplico 2*n volte, quindi è lineare =(2*n) = O(n)
// la somma è lineare, e devo sommare fino a numeri lunghi 2*n, quindi è lineare, O(2*n) = O(n)
C(n) = n
T(n) = 4T(n/2) + n
T(n/2) = 4T(n/4) + n/2
T(n/4) = 4T(n/8) + n/4

T(n) = n + 4(n/2) + 4^2(n/4) + 4^3(n/8) + ... + 4^k(n/2^k) + ... + 4^(log n)(1)
     = n * Somma(2^i, 0, log2n) = 2*n^2 - n = O(n^2)

Quindi non è vantaggioso rispetto al normale algoritmo di moltiplicazione. Tuttavia lo è l'algoritmo di Karatsuba
x_s * y_d + x_d * y_s = (x_s + x_d)(y_s + y_d) - x_s * y_s - x_d * y_d

adesso a=3 e b=2, quindi l'equazione ale ricorrenze è
T(n) = 3T(n/2) + n
T(n/2) = 3T(n/4) +n/2
T(n/4) = 3T(n/8) +n/4

T(n) = n + 3(n/2) + 3^2(n/4) + 3^3(n/8) + ... + 3^k(n/2^k) + ... + 3^(log n)(1)
     = n * Somma((3/2)^i, 0, log2n) = n * ((3/2)^(log2n+1) - 1)/(3/2-1)
     = ... = O(n^log23) ~ O(n^1.58)

# Ricerca binaria (dicotomica)
una chiave k si trova all'interno di un vettore ordinato v[n]? si/no???'
Approccio:
    - se k è uguale al valore centrale di v[n] allora ho trovato
    - se k è minore del valore centrale di v[n] allora cerco in v[0]...v[n/2]
    - se k è maggiore del valore centrale di v[n] allora cerco in v[n/2]...v[n]

Divide and conquer che crea un sottoproblema di dimensione metà. a=1, b=2
```c
int BinSearch(int v[], int l, int r, int k) {
int m;
if (l > r)
    return -1;
m = (l + r)/2;
if (k == v[m])
    return (m);
if (k < v[m])
    return BinSearch(v, l, m-1, k);
return BinSearch(v, m+1, r, k);
}
```

## Analisi di complessità
D(n) = C(n) = O(1)
T(n) = T(n/2) + O(1)
T(n/2) = T(n/4) + O(1)

T(n) = 1 + 1 + T(n/8) = Somma(1, 0, log2n) = O(log2 n)

# Stampa di stringa in ordine inverso (senza conoscere la lunghezza)
```c
void reverse_print(char *s) {
    if(*s != '\0') {
    reverse_print(s+1);
    putchar(*s); // putchar è una funzione che stampa un carattere
    }
    return;
}
```

T(n) = O(n)

# Torre di Hanoi
Non so come spostare n dischi da 0 a 2, perciò
    sposto n-1 dischi da 0 a 1 ( un piolo parcheggio)
    sposto l'ultimo disco da 0 a 2
    sposto i n-1 dischi da 1 (il piolo parcheggio) a 2
```c
void Hanoi(int n, int src, int dest) {
int aux; // il piolo parcheggio
aux = 3 - (src + dest);

if (n == 1) {
    printf("src %d -> dest %d \n", src, dest);
    return;
}

Hanoi(n-1, src, aux);

printf("src %d -> dest %d \n", src, dest);

Hanoi(n-1, aux, dest);
}
```

## Analisi di complessità:
questo algoritmo è decrease and conquer
D(n) = C(n) = 1
T(n) = 2T(n-1) + 1
T(n-1) = 2T(n-2) + 1
T(n-2) = 2T(n-3) + 1

T(n) = 1 + 2 + 4 + 8T(n-3) = Somma(2^i, 0, n-1) = 2^n - 1 = O(2^n)

# Il righello
```
void mark(int m, int h) {
    int i;
    printf("%d \t", m);
    for (i = 0; i < h; i++)
        printf("*");
    printf("\n");
}

void ruler(int l, int r, int h) {
    int m;

    m = (l + r)/2;

    if (h > 0) {
        ruler(l, m, h-1);
        mark(m, h);
        ruler(m, r, h-1);
    }
}
```

stampa una cosa come:
0 	 
1 	*
2 	**
3 	*
4 	***
5 	*
6 	**
7 	*
8 	****
9 	*
10 	**
11 	*
12 	***
13 	*
14 	**
15 	*
16 