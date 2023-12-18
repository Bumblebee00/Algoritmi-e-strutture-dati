[18/12/2023]

# Interval BST
Sono dei BST nel quale la chiave è un intervallo $[low, high] \subset \R$, e non un solo valore. il confrono degli intervalli viene fatto sul low. inoltre c'è un altra annotazione, oltre a quella del numero di nodi del sottoalbero, che è il massimo high tra tutti i nodi del sottoalbero.

Non serve a niente cercare un intervallo in un BST. Non c'è nessuna applicazione che lo richiede. Quello che serve è trovare un intervallo che interseca un altro intervallo.

Nota: quest'estensione di BST non rende le cose più compelesse in quanto scrivere l'annotazione (cioè trovare il massimo) è un'operazione che si fa in tempo O(1).

