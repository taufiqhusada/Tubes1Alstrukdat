/* File : queue.h */
/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */

#ifndef queue_H
#define queue_H

#include "boolean.h"


#define NilQueue 0
#define MaxQueue 10 // MaxQueue Skill yang ada di Queue adalah 10
/* Konstanta untuk mendefinisikan addressQueue tak terdefinisi */
#define MaxCodeLen 5
/* Definisi elemen dan addressQueue */
typedef struct  {
    int skillID;
} SKILL;

typedef SKILL infotypeQueue;
typedef int addressQueue;   /* indeks tabel */
/* Contoh deklarasi variabel bertype Queue : */
/* Versi I : tabel dinamik, HeadQueue dan TailQueue eksplisit, ukuran disimpan */
typedef struct { infotypeQueue * T;   /* tabel penyimpan elemen */
                 addressQueue HeadQueue;  /* alamat penghapusan */
                 addressQueue TailQueue;  /* alamat penambahan */
                 int MaxElQueue;     /* MaxQueue elemen queue */
               } Queue;
/* Definisi Queue kosong: HeadQueue=NilQueue; TailQueue=NilQueue. */
/* Catatan implementasi: T[0] tidak pernah dipakai */

/* ********* AKSES (Selektor) ********* */
/* Jika Q adalah Queue, maka akses elemen : */
#define HeadQueue(Q) (Q).HeadQueue
#define TailQueue(Q) (Q).TailQueue
#define InfoHeadQueue(Q) (Q).T[(Q).HeadQueue]
#define InfoTailQueue(Q) (Q).T[(Q).TailQueue]
#define MaxElQueue(Q) (Q).MaxElQueue

/* ********* Prototype ********* */
boolean IsEmptyQueue(Queue Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsFullQueue(Queue Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxQueueElQueue */
int NBElmtQueue(Queue Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void CreateEmptyQueue(Queue * Q, int MaxElQueue);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran MaxQueue+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxQueueElQueue=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DeAlokasiQueue(Queue * Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxQueueElQueue(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void AddQueue(Queue * Q, infotypeQueue X);
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TailQueue yang baru, TailQueue "maju" dengan mekanisme circular buffer */
void DelQueue(Queue * Q, infotypeQueue * X);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = NilQueueai elemen HeadQueue pd I.S., HeadQueue "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */

#endif