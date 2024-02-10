[9/02/24]

# Albero ricoprente minimo

## Definizione
Sia dato un grafo G=(V,E) con V insieme dei vertici e E insieme degli archi. G è un grafo non orientato, pesato, connesso. Un albero ricoprente minimo (o Minimum Weight Spanning Tree - MST) è un sottografo G' di G tale che:
- G' = (V, A) con A sottoinsieme di E (qundi stessi vertici, alcuni archi)
- G' è un albero, cioè un grafo connesso e aciclico
- la somma dei pesi degli archi di A è minima

L'albero MST è unico se e solo se i pesi degli archi sono tutti distinti.

## Rappresentazione in c
Il grafo originale viene rappresentato con un ADT grafo normale. Nella matrice di adiacenza, per segnalare l'assenza dell'arco, unsiamo un valore `maxWT` idealmente infinito.

il MST può essere rappresentato con un array di archi (usato nell'algoritmo di Kruskal), o con un grafo (quindi lista di adiacenza) o con due vettori, uno per i pesi dei vertici e uno per i padri dei vertici (usato nell'algoritmo di Prim).

## Approccio del calcolo combiantorio
Potremmo usare i modelli del caclolo combiantorio per provare con tutti i possibili sottografi. Possiamo fare un pò di pruning perchè il MST avrà esattametne V-1 archi (se ne avesse di più, avrebbe un ciclo, se ne avesse di meno, non sarebbe connesso). Inoltre non tutti i sottoinsiemi di V-1 archi sono accettabili, alcuni non sono alberi, altri non sono connessi.

## Approccio Greedy
In questo specifico caso si può dimostrare che l'approccio greedy porta alla soluzione globalmente ottima. Usiamo un algorimo incrementale, cioè che a ogni step aggiunge un elemento alla soluzione.

La soluzione A corrente è un sottoinsieme degli archi di un albero ricoprente minimo.
- inizialmente A è l’insieme vuoto
- ad ogni passo si aggiunge ad A un arco “sicuro”
- fino a quando A non diventa un albero ricoprente minimo.

Il problema è determinare un arco “sicuro” da aggiungere ad A. l’arco (u,v) è sicuro se e solo se aggiunto ad un sottoinsieme di un albero ricoprente minimo produce ancora un sottoinsieme di un albero ricoprente minimo. Per trovarlo dobbiamo prima definire alcuni concetti.

> DEF(taglio): Dato un grafo G non orientato pesato e connesso, si definisce taglio (S, V\S) di G una partizione di V in due insiemi disgiunti S e V\S. Si dice che un taglio rispetta un sottoinsieme di archi A di G se nessun arco di A ha un estremo in S e l’altro in V\S, cioè se nessun arco di A attraversa il taglio.

![](<taglio rispetta.png>)

> DEF(arco leggero): Dato un grafo G non orientato pesato e connesso, si definisce arco leggero di un taglio (S, V\S) un arco (u,v) di G che attraversa il taglio tale che il peso di (u,v) è minimo tra tutti gli archi che attraversano il taglio.

![](<arco leggero.png>)
