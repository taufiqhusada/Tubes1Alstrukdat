/* ADT list_bangunan */
/* Menyimpan daftar indeks bangunan yang dimiliki pemain */

#include "boolean.h"
#include "list_bangunan.h"
#include "bangunan.h"
#include <stdlib.h>
#include <stdio.h>

/* PROTOTYPE */

/* MUNGKIN DIPAKAI DALAM PERMAINAN */
/********************************************************/

void AddPasukanAll (List L, TBangunan TB) {
    /* KAMUS */
    adrBgn P;
    /* ALGORITMA */
    P = First(L);
	boolean status;
    while (P != NilLBangunan) {
        AddPasukan(&Bgn(TB, I(P)));
        P = Next(P);
    }
}

// SELF BUILDINGS

boolean IsEmptyList (List L) {
/* Mengirim true jika list kosong */
    return (First(L) == NilLBangunan);
}
void CreateEmptyList (List *L) {
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
	First(*L) = NilLBangunan;
}
void PrintInfo (List L, TBangunan TB) {
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak ke bawah */
/* Format pencetakan: <nomor> <nama bangunan> <koordinat> <jumlah pasukan> <level>
/* Contoh : 1. Castle (1,15) 20 lv. 3 */
/* List tidak akan kosong karena jika list kosong, permainan berhenti */
    /* KAMUS */
    int i;
    adrBgn P;
    /* ALGORITMA */
    i = 1;
    P = First(L);
    while (P != NilLBangunan) {
        printf("%d. ", i);
        TulisDataBangunan(Bgn(TB, I(P)));
        printf("\n");
        i++;
        P = Next(P);
    }
}
int NbBangunan (List L) {
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
	/* KAMUS */ 
	adrBgn P;
	int sum;
	/* ALGORITMA */
	P = First(L);
	sum = 0;
	while (P != NilLBangunan) {
		sum += 1;
		P = Next(P);
	}
	return sum;
}

void ChangeOwner (TBangunan TB,List L1, List L2, int X) {
/* I.S. Bangunan B elemen L1 (milik pemain 1) */
/* F.S. Bangunan B menjadi milik pemain 2. Maka: */
/* 	Bangunan dihapus dari L1 dan ditambahkan ke L2 terakhir */
    /* KAMUS */
    adrBgn changed;
    /* ALGORITMA */
    changed = GoTo(L1, X);
    ChangeOwnerB(&Bgn(TB, I(changed)));
	DelP(&L1, X);
	InsertLast(&L2, changed);
}


/* FUNGSI PENUNJANG */
/********************************************************/

/****************** Manajemen Memori ******************/
adrBgn AlokasiBgn (TBangunan TB, int i) {
/* Mengirimkan adrBgn hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka adrBgn tidak NilLBangunan, dan misalnya */
/* menghasilkan P, maka TB(P) = TB, I(P) = i, Next(P)=NilLBangunan */
/* Jika alokasi gagal, mengirimkan NilLBangunan */
	/* KAMUS */
	adrBgn P;
	/* ALGORITMA */
	P = (adrBgn) malloc (1 * sizeof(ElmtList));
	if (P != NilLBangunan) {
		I(P) = i;
		Next(P) = NilLBangunan;
	}
	else {
		P = NilLBangunan;
	}
	return P;
}
void DealokasiBgn (adrBgn *P) {
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian adrBgn P */
	free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
adrBgn GoTo (List L, int X) {
/* Iterasi menuju elemen list ke-X */
/* Prekondisi: 1 <= X <= NbBangunan */
    /* KAMUS */
    adrBgn P;
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
        return NilLBangunan;
    }
}

// adrBgn SearchList (List L, int i, int j) {
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan adrBgn elemen tersebut. */
/* Jika tidak ada, mengirimkan NilLBangunan */
	/* KAMUS */
	/* adrBgn P;
	boolean found;
	/* ALGORITMA */
	/* P = First(L);
	found = false;
	while (!found && P != NilLBangunan) {
		if (I(P) == i && J(P) == j) {
			found = true;
		}
		else {
			P = Next(P);
		}
	}
	return P;
} */

/****************** PRIMITIF BERDASARKAN NilLBangunanAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, TBangunan TB, int i) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan NilLBangunanai X jika alokasi berhasil */
	/* KAMUS */
	adrBgn P;
	/* ALGORITMA */
	P = AlokasiBgn(TB, i);
	if (P != NilLBangunan) {
		InsertFirst(L, P);
	}
}
void InsVLast (List *L, TBangunan TB, int i) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* berNilLBangunanai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
	/* KAMUS */
	adrBgn P;
	/* ALGORITMA */
	P = AlokasiBgn(TB, i);
	if (P != NilLBangunan) {
		InsertLast(&*L, P);
	}
}

/*** PENGHAPUSAN ELEMEN ***/
//void DelVFirst (List *L, infotype *X) {
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: NilLBangunanai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
	/* KAMUS */
	//adrBgn P;
	/* ALGORITMA */
	//DelFirst(&*L, &P);
	//*X = Info(P);	
//}
//void DelVLast (List *L, infotype *X) {
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: NilLBangunanai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
	/* KAMUS */
	// adrBgn Last;
	/* ALGORITMA */
	// DelLast(&*L, &Last);
	// *X = Info(Last);
//}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, adrBgn P) {
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-adrBgn P sebagai elemen pertama */
	Next(P) = First(*L);
	First(*L) = P;
}
void InsertAfter (List *L, adrBgn P, adrBgn Prec) {
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
	Next(P) = Next(Prec);
	Next(Prec) = P;
}
void InsertLast (List *L, adrBgn P) {
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
	/* KAMUS */
	adrBgn Last;
	/* ALGORITMA */
	if (IsEmptyList(*L)) {
		InsertFirst(&*L, P);
	}
	else {
		Last = First(*L);
		while (Next(Last) != NilLBangunan) {
			Last = Next(Last);
		}
		InsertAfter(&*L, P, Last);
	}
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, adrBgn *P) {
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
/* F.S. Jika ada elemen list beradrBgn P, elemen ke-X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* List mungkin menjadi kosong karena penghapusan */
	/* KAMUS */
	adrBgn P, Prec;
	/* ALGORITMA */
	P = GoTo(*L, X);
	if (P == First(*L)) {
		DelFirst(&*L, &P);
	}
	else if (P != NilLBangunan) {
		Prec = First(*L);
		while (Next(Prec) != P) {
			Prec = Next(Prec);
		}
		DelAfter(&*L, &P, Prec);
	}
}
void DelLast (List *L, adrBgn *P) {
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
	/* KAMUS */
	adrBgn Last, PrecLast;
	/* ALGORITMA */
	Last = First(*L);
	PrecLast = NilLBangunan;
	while (Next(Last) != NilLBangunan) {
		PrecLast = Last;
		Last = Next(Last);
	}
	*P = Last;
	if (PrecLast == NilLBangunan) {
		First(*L) = NilLBangunan;
	}
	else {
		Next(PrecLast) = NilLBangunan;
	}
}
void DelAfter (List *L, adrBgn *Pdel, adrBgn Prec) {
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
	/* KAMUS */
	/* ALGORITMA */
	*Pdel = Next(Prec);
	Next(Prec) = Next(Next(Prec));
}