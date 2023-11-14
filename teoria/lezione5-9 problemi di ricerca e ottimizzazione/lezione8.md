In questa lezione parliamo di applicazioni/esmpi di algoritmi di ricerca e ordinamento. abbiamo trattato di
- [Permutazioni ripeute](#permutazioni-ripetute)
- [Combinazioni semplici](#combinazioni-semplici)
- [Algoritmo di Er (1987)](#algoritmo-di-er-1987)


# Permutazioni ripetute
n è la cardianlità del multiiinsieme (conta le ripetizioni)
memorizziamo in un vettore **dist_val** gli elementi distinti del multinsieme, presi solo una volta, e in un intero **n_dist** il numero di elementi distinti (di solito si fa ordinando il multinsieme e poi scartando gli elementi uguali ad altri vicini)
abbiamo anche un vettore **mark** che contiene (almeno inizialmente), il numero di occorrenze degli elementi disitinti. se prendiamo un elemento `dist_val[i]` e lo togliamo dal multinsieme, dobbiamo decrementare `mark[i]`. al ritorno della ricorsione, `mark[i]` è di nuovo incrementato.

Esempio: Generare tutti gli anagrammi distinti di una parola (che ha lettere ripetute).
val = 'ORO', dist_val = {'O', 'R'}, mark = {2, 1}, n = 3, n_dist = 2

```c
int main() {
  int i, j, n, n_dist, total, *mark;
  char *val, *dist_val, *sol;

  printf("Inserisci n: "); scanf("%d", &n);
  val = malloc((n+1) * sizeof(char));
  dist_val = malloc((n+1) * sizeof(char)); // stiamo allocando per eccesso
  sol = malloc((n+1) * sizeof(char));

  printf("Inserisci stringa: "); scanf("%s", val);

  // crea il vettore dist_val ordinato
  MergeSort(val, 0, n-1);
  n_dist = 1;
  for (i=1; i<n; i++)
    if(val[i-1] != val[i])
      n_dist++;
  mark = calloc(n_dist, sizeof(int));
  j = 0;
  dist_val[j++] = val[0];
  for (i=1; i<n; i++)
    if(val[i-1] != val[i]) { dist_val[j++]= val[i]; }
  dist_val[j] = '\0';
  // crea il vettore mark
  i = 1;
  j = 0;
  mark[j] = 1;
  while(i < n) {
    while (val[i-1] == val[i]) {
      i++;
      mark[j]++;
    }
    j++;
    mark[j]++;
    i++;
  }

  for (i=0; i < n; i++)
    sol[i]= -1;

  printf("Le permutazioni distinte della stringa %s con ripetizioni sono: \n", val);
  total = coeff_multin(0, dist_val, sol, mark, n, n_dist, 0);
  printf("\ne in totale sono %d \n", total);
}

int coeff_multin(int pos, char dist_val[], char sol[], int mark[], int n, int n_dist, int count) {
  int i;
  if (pos >= n) {
    sol[pos]='\0';
    printf("\nSoluzione: ");
    printf("%s \n \n", sol);
    return count+1;
  }

  for (i=0; i<n_dist; i++)
    if (mark[i] > 0) {
      mark[i]--;
      sol[pos] = dist_val[i];
      count = coeff_multin(pos+1, dist_val, sol, mark, n, n_dist, count);
      mark[i]++;
    }
  return count;
}
```

# Combinazioni semplici
Esempio: combinazione di k tra n valori. Dato un insieme di n interi, generare tutte le combinazioni semplici di k di questi valori.
val = {1, 9, 5, 4}

# Algoritmo di Er (1987)
Prende n oggetti, e calcola tutte le partizioni in osttoinsiemi di lunghezza da 1 a n. la osluzione è memorizzata in un vettore sol di n elemeti. funziona con due ricorsioni
- si attribuisce l'oggetto corrente alla partizione corrente (tra 0 e m-1) e poi si ricorre all'oggetto successivo
- si attribuisce l'oggetto corrente al blocco m, e si ricorre sul prossimo oggetto.

```c
int main(){
  int i, n, *val, *sol;

  printf("\nCalcolo delle partizioni di un insiemi di n elementi in 1 .. n blocchi\n");
  printf("Inserisci il numero n di elementi: "); scanf("%d", &n);

  val = malloc(n * sizeof(int));
  sol = calloc(n, sizeof(int));

  for (i=0; i<n; i++) {
    printf("Inserisci elementi: ");
    scanf("%d", &val[i]);
  }

  printf("Le partizioni di %d elementi in 1 .. %d blocchi sono \n", n, n);
  SetPartitions(n, sol, val);
}

void SetPartitions(int n, int *sol, int *val) {
  SP_rec(n, 0, 0, sol, val);
  return;
}

void SP_rec(int n,int m,int pos,int *sol,int *val) {
  int i, j;
  if (pos >= n) {
    printf("partizione in %d blocchi: ", m);
    for (i=0; i<m; i++) {
      printf("{ ");
      for (j=0; j<n; j++)
        if (sol[j]==i)
          printf("%d ", val[j]);
      printf("}  ");
     }
    printf("\n");
    return;
  }
  for (i=0; i<m; i++) {
    sol[pos] = i;
    SP_rec(n, m, pos+1, sol, val);
  }
  sol[pos] = m;
  SP_rec(n, m+1, pos+1, sol, val);
}
```