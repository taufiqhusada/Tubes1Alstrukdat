/* ADT list_bangunan */
/* Menyimpan daftar indeks bangunan yang dimiliki pemain */

#include "boolean.h"
#include "list_bangunan.h"
#include "bangunan.h"
#include "../konfig/petaMatriks.h"
#include <stdlib.h>
#include <stdio.h>

/* PROTOTYPE */

/* MUNGKIN DIPAKAI DALAM PERMAINAN */
/********************************************************/
// SELF BUILDINGS
boolean IsEmptyList (List L) {
/* Mengirim true jika list kosong */
    return (First(L) == Nil);
}
void CreateEmpty (List *L) {
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
	First(*L) = Nil;
}
void PrintInfo (List L) {
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak ke bawah */
/* Format pencetakan: <nomor> <nama bangunan> <koordinat> <jumlah pasukan> <level>
/* Contoh : 1. Castle (1,15) 20 lv. 3 */
/* List tidak akan kosong karena jika list kosong, permainan berhenti */
    /* KAMUS */
    int i;
    address P;
    /* ALGORITMA */
    i = 1;
    P = First(L);
    while (P != Nil) {
        printf("%d. ", i);
        TulisDataBangunan(Elmt(Mtr(P), I(P), J(P)));
        printf("\n");
        i++;
        P = Next(P);
    }
}
int NbBangunan (List L) {
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
	/* KAMUS */ 
	address P;
	int sum;
	/* ALGORITMA */
	P = First(L);
	sum = 0;
	while (P != Nil) {
		sum += 1;
		P = Next(P);
	}
	return sum;
}

void ChangeOwner (List L1, List L2, int X) {
/* I.S. Bangunan B elemen L1 (milik pemain 1) */
/* F.S. Bangunan B menjadi milik pemain 2. Maka: */
/* 	Bangunan dihapus dari L1 dan ditambahkan ke L2 terakhir */
    /* KAMUS */
    address changed;
    /* ALGORITMA */
    changed = GoTo(L1, X);
    ChangeOwnerB(&Elmt(Mtr(changed), I(changed), J(changed)));
	DelP(&L1, X);
	InsertLast(&L2, changed);
}


/* FUNGSI PENUNJANG */
/********************************************************/

/****************** Manajemen Memori ******************/
address Alokasi (MATRIKS M, int i, int j) {
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Mtr(P) = M, I(P) = i, J(P) = j, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
	/* KAMUS */
	address P;
	/* ALGORITMA */
	P = (address) malloc (1 * sizeof(address));
	if (P != Nil) {
		Mtr(P) = M;
		I(P) = i;
		J(P) = j;
		Next(P) = Nil;
	}
	else {
		P = Nil;
	}
	return P;
}
void Dealokasi (address *P) {
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
	free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address GoTo (List L, int X) {
/* Iterasi menuju elemen list ke-X */
/* Prekondisi: 1 <= X <= NbBangunan */
    /* KAMUS */
    address P;
    /* ALGORITMA */
    if (1 <= X && X <= NbBangunan(L)) {
        P = First(L);
        while (X > 1) {
            P = Next(P);
            X--;
        }
        return P;
    }
    else {
        printf("Out of bound\n");
        return Nil;
    }
}

// address SearchList (List L, int i, int j) {
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
	/* KAMUS */
	/* address P;
	boolean found;
	/* ALGORITMA */
	/* P = First(L);
	found = false;
	while (!found && P != Nil) {
		if (I(P) == i && J(P) == j) {
			found = true;
		}
		else {
			P = Next(P);
		}
	}
	return P;
} */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, MATRIKS M, int i, int j) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
	/* KAMUS */
	address P;
	/* ALGORITMA */
	P = Alokasi(M, i, j);
	if (P != Nil) {
		InsertFirst(&*L, P);
	}
}
void InsVLast (List *L, MATRIKS M, int i, int j) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
	/* KAMUS */
	address P;
	/* ALGORITMA */
	P = Alokasi(M, i, j);
	if (P != Nil) {
		InsertLast(&*L, P);
	}
}

/*** PENGHAPUSAN ELEMEN ***/
//void DelVFirst (List *L, infotype *X) {
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
	/* KAMUS */
	//address P;
	/* ALGORITMA */
	//DelFirst(&*L, &P);
	//*X = Info(P);	
//}
//void DelVLast (List *L, infotype *X) {
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
	/* KAMUS */
	// address Last;
	/* ALGORITMA */
	// DelLast(&*L, &Last);
	// *X = Info(Last);
//}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P) {
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
	Next(P) = First(*L);
	First(*L) = P;
}
void InsertAfter (List *L, address P, address Prec) {
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
	Next(P) = Next(Prec);
	Next(Prec) = P;
}
void InsertLast (List *L, address P) {
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
	/* KAMUS */
	address Last;
	/* ALGORITMA */
	if (IsEmptyList(*L)) {
		InsertFirst(&*L, P);
	}
	else {
		Last = First(*L);
		while (Next(Last) != Nil) {
			Last = Next(Last);
		}
		InsertAfter(&*L, P, Last);
	}
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P) {
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
	/* KAMUS */
	/* ALGORITMA */
	*P = First(*L);
	First(*L) = Next(First(*L));
}
void DelP (List *L, int X) {
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, elemen ke-X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* List mungkin menjadi kosong karena penghapusan */
	/* KAMUS */
	address P, Prec;
	/* ALGORITMA */
	P = GoTo(*L, X);
	if (P == First(*L)) {
		DelFirst(&*L, &P);
	}
	else if (P != Nil) {
		Prec = First(*L);
		while (Next(Prec) != P) {
			Prec = Next(Prec);
		}
		DelAfter(&*L, &P, Prec);
	}
}
void DelLast (List *L, address *P) {
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
	/* KAMUS */
	address Last, PrecLast;
	/* ALGORITMA */
	Last = First(*L);
	PrecLast = Nil;
	while (Next(Last) != Nil) {
		PrecLast = Last;
		Last = Next(Last);
	}
	*P = Last;
	if (PrecLast == Nil) {
		First(*L) = Nil;
	}
	else {
		Next(PrecLast) = Nil;
	}
}
void DelAfter (List *L, address *Pdel, address Prec) {
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
	/* KAMUS */
	/* ALGORITMA */
	*Pdel = Next(Prec);
	Next(Prec) = Next(Next(Prec));
}