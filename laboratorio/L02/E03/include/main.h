#define MAX 30

typedef struct {
    char code[MAX];
    char from[MAX];
    char to[MAX];
    char date[MAX];
    char departure[MAX];
    char arrival[MAX];
    int ritardo;
} BusRide;

typedef enum {
    r_stampa_video,
    r_stampa_file,
    r_ord,
    r_ricerca,
    r_acquisisci,
    r_fine
} comando_e;

void selezionaDati(comando_e);
void readFile(char *, BusRide **, int *);