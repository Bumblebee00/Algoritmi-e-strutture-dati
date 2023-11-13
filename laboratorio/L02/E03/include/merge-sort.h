typedef enum {
    r_data,
    r_codice_tratta,
    r_stazione_partenza,
    r_stazione_arrivo
} ord_key;

BusRide ***Sort(BusRide[], int);
void MergeSort(BusRide ***A, int N, ord_key key);
void MergeSortR(BusRide ***A, BusRide **B, int l, int r, ord_key key);
void Merge(BusRide ***A, BusRide **B, int l, int q, int r, ord_key key);
int ITEMeq(BusRide A, BusRide B, ord_key key);
int ITEMlt(BusRide A, BusRide B, ord_key key);
int isBefore(BusRide, BusRide);