Una funzione ricorsiva definisce se stessa attraverso se stessa. (oppure la prima chiama un altra che richiama la prima). Ma come si finisce questo ciclo infinito?

ES: Magari devo ordinare un vettore di n dati. non sono capace. ma se ci fossero 2 vettori da n/2 dati magari ci riesco (?)

S(D) = f(S(D'))   dove D' è una forma semplificata di D
S(D_0) = S_0

S soluzione
D dati
f funzione ricursiva

Paradigma dividi et impera:
- partiziona il problema in problemi più piccoli di ugual natura
- risoluzione di sotto-problemi analoghi a quello di partenza (ma più piccoli)
- combinazione di soluzioni parziali nella soluzione del problema originario

bonus: eleganza matematica e poche righe di codice

Ma quindi come si finisce questo ciclo infinito? ci deve essere una condizione termine

## Paradigma dividi et impera più nel dettaglio:
Divide: 1 problema di dimensione n in più sottoproblemi (a in numero) di dimensione n'<n, indipendenti tra loro. cioè io non ho memoria di questi sottoprobelmi e se me ne se presenta uno uguale a un altro lo risolvo ancora
Impera: arrivo a sottoproblemi semplici con soluzioni elementari
Combina: ricostruzione di soluzione complessiva combinando le soluzioni parziali

Pseudo codice:
```
risolvi(problema){
	se (è un problema elementare) {
		return soluzione = risolvi_prob_banale(problema)
	} altrimenti {
		sotto_problemi = dividi(problema)
		per ogni (sotto_problema){
			sottosoluzione = risolvi(sottoproblema)
		}
		return soluzione = Combina(sottosoluzioni)
	}
}
```

Valori di a:
a=1: ricorsione lineare
a>1 ricorsione multi via

Valori di n':
n' = n - qualcosa: decrease and conquer
n' = n / qualcosa: divide and conquer

Esempio stupido:
Devo visuallizzare un vettore di dimensione n=2^k ma io so visualizzare solo i vettori da una cella. come faccio?
Suddividerlo ricorsivamente in sottovettori di dimensione metà, fino alla condizione di terminazione (sottovettore di 1 sola cella).
In questo caso a = 2, n' = n / 2 (b=2)
(vedi 00show_recursion_tree.c)

Esempio:
determinare un massimo di un vettore di n=2^k elementi. non sono capace di farlo, allora provo a vedere se sono capace di trovare il massimo del sottovettore destro e sinistro, e poi li confronto.
(vedi 01max_array.c)

## Analisi di complessità
Utilizzeremo il formalismo delle equazioni alle ricorrenze (la complessita si può scrivere come tempo, spazio o . spazio non ci interessa. vediamo tempo)
In ogni caso gli elementi importanti sono:
- D(n) tempo della divisione
- tempo di esecuzione per input più piccoli
- C(n) tempo della combinazione
- si suppone che al soluzione del problema semplice sia O(1)

Nel caso di divide and conquer T(n) viene espressa come:
T(n) = D(n) + aT(n/b) + C(n)                 se non siamo nel caso elementare
T(n) = O(1)                                  se siamo nel caso elementare
(dove ricordiamo a = numero di sottoproblemi, n/b = dimensione dei sottoproblemi)

Nel caso di decrease and conquer T(n) viene espressa come
T(n) = D(n) + somma[T(n-k_i) per i che va da 0 a a] + C(n)
T(n) = O(1)                                  se siamo nel caso elementare
