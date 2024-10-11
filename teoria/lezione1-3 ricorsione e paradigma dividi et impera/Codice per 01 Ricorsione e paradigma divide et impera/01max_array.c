#include <stdio.h>
#define N 10

int max(int a[], int l, int r);

int main() {
  int i, a[N];

  for (i=0; i<N; i++) {
    printf("Input a[%d]:", i);
    scanf("%d", &a[i]);
  }

  printf("The maximum is: %d \n", max(a, 0, N-1));
  return 0;
}


int max(int a[], int l, int r) {
  int u, v ;
  int m = (l + r)/2 ; // calcola l'indice di mezzo

  if (l == r) // se l'array ha un solo elemento
    return a[l] ;

  u = max (a, l, m); // chiamata ricorsiva
  v = max (a, m+1, r);

  if (u > v) // confronto
    return u;
  else // else ridondante solo per chiarezza
    return v;
}
