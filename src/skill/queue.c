/* Nama / NIM : Mohammad Rafi Adyatma / 13518121
   Tanggal    : 2 Oktober 2019
*/

#include "queue.h"
#include "skill.h"
#include <stdio.h>
#include <stdlib.h>

/* ********* Prototype ********* */
boolean IsEmptyQueue (Queue Q) {
/* Mengirim true jika Q kosong: lihat definisi di atas */
    return ((Head(Q) == Nil) && (Tail(Q) == Nil));
}
boolean IsFullQueue (Queue Q) {
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */

    return (Tail(Q) == MaxEl(Q));
}
int NbElmtQueue (Queue Q) {
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
    int n;
    if (IsEmptyQueue(Q)) {
        return 0;
    } 
    else if (Head(Q) <= Tail(Q)) {

        return(Tail(Q) - Head(Q) + 1);
    }
    else {
        n = MaxEl(Q) - (Head(Q) - Tail(Q) - 1);
        return n;
    }
}

/* *** Kreator *** */
void CreateEmptyQueue (Queue * Q, int MaxElmt) {
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
    (*Q).T = (int*) malloc ((MaxElmt+1) * sizeof(int));
    MaxEl(*Q) = MaxElmt;
}
/* *** Destruktor *** */
void DeAlokasi(Queue * Q) {
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
    free((*Q).T);
    MaxEl(*Q) = 0;
}

/* *** Primitif Add/Delete *** */
void Add (Queue * Q, infotype X) {
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
    if (IsEmptyQueue(*Q)) {
        Head(*Q) = 1;
        Tail(*Q) = 1;
        InfoHead(*Q) = X;
        InfoTail(*Q) = X;
    }

    else if (Tail(*Q) == MaxEl(*Q)) {
        Tail(*Q) = 1;
        InfoTail(*Q) = X;
    }
    else {
        Tail(*Q)++;
        InfoTail(*Q) = X;
    }
}
void Del (Queue * Q, infotype * X) {
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */

    if (Head(*Q) == MaxEl(*Q)) {
        *X = InfoHead(*Q);
        Head(*Q) = 1;
        InfoHead(*Q) = (*Q).T[1];
    } 
    else {
        *X = InfoHead(*Q);
        InfoHead(*Q) = (*Q).T[Head(*Q) + 1];
        Head(*Q)++;      
    }
}