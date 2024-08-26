# Compilazione condizionale
Si usano le direttive #if e #endif. La compilazione di quanto compare tra le direttive #if e #endif è condizionata alla condizione che compare come argomento. Utile, ad esempio, per istruzioni che servono solo quando si fa debug.
```c
...
#define DBG 1 //0 per disabilitare ...
#if DBG
// istruzioni da compilare
// (ed eseguire) in debug
printf (“serve solo per debug“); #endif
...
```
oppure c'è anche #ifdef e #endif, che è come #if e #endif, ma la condizione è se la macro è definita o meno. (se è definita, allora la condizione è vera)
```c
...
#define DBG
...
#ifdef DBG // così è sempre vera
// istruzioni da compilare
// (ed eseguire) in debug
printf (“serve solo per debug“); #endif
...
```
```c
...
#define DBG
#undef DBG
...
#ifdef DBG // così è sempre falsa
// istruzioni da compilare
// (ed eseguire) in debug
printf (“serve solo per debug“); #endif
...
```
analogamente c'è anche `#ifndef` che è come `#ifdef` ma la condizione è se la macro non è definita.
```c