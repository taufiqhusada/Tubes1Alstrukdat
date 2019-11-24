/* Nama / NIM : Mohammad Rafi Adyatma / 13518121
   Tanggal    : 2 Oktober 2019
*/

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/* ********* Prototype ********* */
boolean     IsEmptyQueue (Queue Q) {
/* Mengirim true jika Q kosong: lihat definisi di atas */
    return ((HeadQueue(Q) == NilQueue) && (TailQueue(Q) == NilQueue));
}
boolean IsFullQueue (Queue Q) {
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */

    return (TailQueue(Q) == MaxElQueue(Q));
}
int NBElmtQueue (Queue Q) {
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
    int n;
    if (IsEmptyQueue(Q)) {
        return 0;
    } 
    else if (HeadQueue(Q) <= TailQueue(Q)) {

        return(TailQueue(Q) - HeadQueue(Q) + 1);
    }
    else {
        n = MaxElQueue(Q) - (HeadQueue(Q) - TailQueue(Q) - 1);
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
    (*Q).T = (infotypeQueue*) malloc ((MaxElmt+1) * sizeof(infotypeQueue));
    MaxElQueue(*Q) = MaxElmt;
}
/* *** Destruktor *** */
void DeAlokasiQueue(Queue * Q) {
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
    free((*Q).T);
    MaxElQueue(*Q) = 0;
}

/* *** Primitif Add/Delete *** */
void AddQueue(Queue * Q, infotypeQueue X) {
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
    if (IsEmptyQueue(*Q)) {
        HeadQueue(*Q) = 1;
        TailQueue(*Q) = 1;
        InfoHeadQueue(*Q) = X;
        InfoTailQueue(*Q) = X;
    }

    else if (TailQueue(*Q) == MaxElQueue(*Q)) {
        TailQueue(*Q) = 1;
        InfoTailQueue(*Q) = X;
    }
    else {
        TailQueue(*Q)++;
        InfoTailQueue(*Q) = X;
    }
}
void DelQueue(Queue * Q, infotypeQueue * X) {
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */

    (*X) = InfoHeadQueue(*Q);
	if (HeadQueue(*Q) == TailQueue(*Q)){
			HeadQueue(*Q) = NilQueue;
			TailQueue(*Q) = NilQueue;
	}
	else{
		HeadQueue(*Q)++;
		if (HeadQueue(*Q) == MaxElQueue(*Q) + 1) HeadQueue(*Q) = 1;
	}

}