#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "aeroporti.h"

aeroporti_t *allocaAeroporti (int max) {
  aeroporti_t *ap = malloc(sizeof(aeroporti_t));
  ap->nmax = max;
  ap->na = 0;
  ap->elenco = malloc(max*sizeof(aeroporto_t));
  return ap;
}

void liberaAeroporti (aeroporti_t *ap) {
  int i;
  for (i=0; i<ap->na; i++) {
    free (ap->elenco[i].nomeCitta);
    free (ap->elenco[i].nomeAeroporto);
  }
  free (ap->elenco);
  free (ap);
}

// solo usata internamente
void leggiStringhe(FILE *fp, char *s1, char *s2, char *s3, char sep1, char sep2) {
  int i;
  char c;
  fscanf(fp," "); // salta gli spazi
  for (i=0; (fscanf(fp,"%c", &c) != EOF) && c!=sep1; i++) {
    s1[i] = c;
  }
  s1[i] = '\0'; // mette il terminatore di stringa... manovalanza di basso livello
  fscanf(fp," ");
  for (i=0; (fscanf(fp,"%c", &c) != EOF) && c!=sep2; i++) {
    s2[i] = c;
  }
  s2[i] = '\0';
  fscanf(fp," ");
  for (i=0; (fscanf(fp,"%c", &c) != EOF) && c!='\n'; i++) {
    s3[i] = c;
  }
  s3[i] = '\0';
}

/*
(*)
come faccio a mettere le stringhe allcoate dinamicamente, lette da file, negli struct? perchè a priori non so la lunghezza delle stringhe, non posso fare malloc(sizeof(char) * (lunghezza stringa)). potrei fare una malloc sovrallocata e poi realloc, ma il metodo migliore è caricare la stringa su una variabile temporanea e poi fare strdup, che alloca dinamicamente la stringa e la copia nella nuova locazione di memoria. strdup è una funzione di string.h
*/

aeroporti_t *leggiAeroporti (char *nomeFile) {
  aeroporti_t *tutti;
  int i, na;
  char citta[M1], aerop[M1]; // (*)
  FILE *f = fopen(nomeFile,"r");
  if (f==NULL) return NULL;
  fscanf(f,"%d",&na);
  tutti = allocaAeroporti(na);
  for (i=0; i<na; i++) {
    leggiStringhe(f,tutti->elenco[i].codice,citta,aerop,' ',',');
    tutti->elenco[i].nomeCitta  = strdup(citta); // (*)
    tutti->elenco[i].nomeAeroporto  = strdup(aerop);
  }
  tutti->na = na;
  fclose(f);
  return tutti;
}

aeroporto_t *cercaAeroportoC(aeroporti_t *aeroporti, char *codice) {
  int i;
  // non è ordinato, non possiamo fare ricerca dicotomica
  for (i=0; i<aeroporti->na; i++) 
    if (strcmp(aeroporti->elenco[i].codice,codice)==0)
      return &(aeroporti->elenco[i]);
  
  return NULL;
}


void scriviAeroporti (char *nomeFile, aeroporti_t *aeroporti) {
  int i;
  FILE *f;
  if (strcmp(nomeFile,"stdout")==0) {
    f = stdout;
  }
  else {
    f = fopen(nomeFile,"w");
  }
  if (f==NULL) return;
  fprintf(f, "%d\n",aeroporti->na);
  for (i=0; i<aeroporti->na; i++) {
    fprintf(f, "%s %s, %s\n", 
	    aeroporti->elenco[i].codice,
	    aeroporti->elenco[i].nomeCitta,
	    aeroporti->elenco[i].nomeAeroporto
	    );
  }
  if (strcmp(nomeFile,"stdout")!=0)
    fclose(f);
}
