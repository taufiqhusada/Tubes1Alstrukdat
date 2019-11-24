/* ADT list_bangunan */
/* Menyimpan daftar indeks bangunan yang dimiliki pemain */

#ifndef _list_bangunan_
#define _list_bangunan_

#include "boolean.h"
#include "bangunan.h"
#include "../konfig/petaMatriks.h"

#include "boolean.h"

#define NilLBangunan NULL

typedef struct tElmtlist *adrBgn;
typedef struct tElmtlist {
	int i; 
	adrBgn next;
} ElmtList;
typedef struct {
	adrBgn First;
} List;

/* Definisi list : */
/* List kosong : First(L) = Nil */
/* Setiap elemen dengan adrBgn P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list : jika adrBgnnya Last, maka Next(Last)=Nil */

#define I(P) (P)->i
#define Next(P) (P)->next
#define First(L) ((L).First)

/* PROTOTYPE */

/* MUNGKIN DIPAKAI DALAM PERMAINAN */
/********************************************************/
int jumlahtower(List L, TBangunan T);

void AddPasukanAll (List L, TBangunan *TB);
// level up all bangunan (saat awal turn)

// SELF BUILDINGS
boolean IsEmptyList (List L);
/* Mengirim true jika list kosong */
void CreateEmptyList (List *L);
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
void PrintInfo (List L, TBangunan TB);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak ke bawah */
/* Format pencetakan: <nomor> <nama bangunan> <koordinat> <jumlah pasukan> <level> */
/* Contoh : 1. Castle (1,15) 20 lv. 3 */
/* List tidak akan kosong karena jika list kosong, permainan berhenti */

void PrintInfoAttack (List L, TBangunan TB, int isAlreadyAttacking[]);


int NbBangunan (List L);
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */

// RELATIONALS
void ChangeOwner (TBangunan TB, List L1, List L2, int X);
/* I.S. Bangunan B elemen L1 (milik pemain 1) */
/* F.S. Bangunan B menjadi milik pemain 2. Maka: */
/* 	Bangunan dihapus dari L1 dan ditambahkan ke L2 terakhir */


/* FUNGSI PENUNJANG */
/********************************************************/

/****************** Manajemen Memori ******************/
adrBgn AlokasiBgn (TBangunan TB, int i);
/* Mengirimkan adrBgn hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka adrBgn tidak nil, dan misalnya */
/* menghasilkan P, maka Mtr(P) = M, I(P) = i, J(P) = j, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokasiBgn (adrBgn *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian adrBgn P */

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
adrBgn GoTo (List L, int X);
/* Iterasi menuju elemen list ke-X */
/* Prekondisi: 1 <= X <= NbBangunan */

int SearchList (List L, int i);
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan adrBgn elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, TBangunan TB, int i);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLast (List *L, TBangunan TB, int i);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
// void DelVFirst (List *L, infotype *X);
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
// void DelVLast (List *L, infotype *X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, adrBgn P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-adrBgn P sebagai elemen pertama */
void InsertAfter (List *L, adrBgn P, adrBgn Prec);
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void InsertLast (List *L, adrBgn P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, adrBgn *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelP (List *L, int X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beradrBgn P, elemen ke-X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* List mungkin menjadi kosong karena penghapusan */
void DelLast (List *L, adrBgn *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
void DelAfter (List *L, adrBgn *Pdel, adrBgn Prec);
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */


#endif