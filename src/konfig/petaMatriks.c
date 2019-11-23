#include<stdio.h>
#include"../pcolor/pcolor.h"
#include"petaMatriks.h"

/* NBrsEff <= 1 dan NKolEff <= 1 */
/* Indeks matriks yang digunakan: [BrsMin..BrsMax][KolMin..KolMax] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M){
	(*M).NBrsEff = NB;
	(*M).NKolEff = NK;
}
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */

/* *** Selektor *** */
#define NBrsEff(M) (M).NBrsEff
#define NKolEff(M) (M).NKolEff
#define Elmt(M,i,j) (M).Mem[(i)][(j)]

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j){
	return ((i>=BrsMin && i<=BrsMax) && (j>=KolMin && j<=KolMax));
}
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M){
	return BrsMin;
}
/* Mengirimkan indeks baris terkecil M */
indeks GetFirstIdxKol (MATRIKS M){
	return KolMin;
}
/* Mengirimkan indeks kolom terkecil M */
indeks GetLastIdxBrs (MATRIKS M){
	return (M).NBrsEff;	
}
/* Mengirimkan indeks baris terbesar M */
indeks GetLastIdxKol (MATRIKS M){
	return M. NKolEff;
}
/* Mengirimkan indeks kolom terbesar M */
boolean IsIdxEff (MATRIKS M, indeks i, indeks j){
	return ((i>=BrsMin && i<=GetLastIdxBrs(M)) && (j>=KolMin && j<=GetLastIdxKol(M)));
}
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
/* 
ElType GetElmtDiagonal (MATRIKS M, indeks i){
	return type(Elmt(M,i,i));
}
*/
/* Mengirimkan elemen M(i,i) */

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl){
	(*MHsl).NBrsEff = (MIn).NBrsEff;
	(*MHsl).NKolEff = (MIn).NKolEff;
	int i,j;
	for (i=1; i<=GetLastIdxBrs(MIn); ++i){
		for (j = 1; j<=GetLastIdxKol(MIn); ++j){
			Elmt(*MHsl,i,j) = Elmt(MIn,i,j);
		}
	}
}
/* Melakukan assignment MHsl  MIn */

/* ********** KELOMPOK BACA/TULIS ********** */
/* 
void BacaMATRIKS (MATRIKS * M, int NB, int NK){
	ElType x;
	MakeMATRIKS(NB,NK,M);
	if (NB==0 || NK==0) return;
	int i,j;
	for (i=1; i<=NB; ++i){
		for (j = 1; j<=NK; ++j){
			scanf("%c",&x);
			type(Elmt(*M,i,j)) = x;	
		}
	}
}
*/
/* I.S. IsIdxValid(NB,NK) */
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10
*/
void TulisMATRIKS (MATRIKS M, TBangunan TB){
	if (M.NBrsEff==0 || M.NKolEff==0) return;
	int i,j;
	for (i =1; i<=GetLastIdxKol(M)+2; ++i){
		printf("*");
	}
	printf("\n");
	for (i=1; i<=GetLastIdxBrs(M); ++i){
		printf("*");
		for (j = 1; j<=GetLastIdxKol(M); ++j){
			if (Bgn(TB,Elmt(M,i,j)).owner==1){
				print_red(Bgn(TB,Elmt(M,i,j)).type);
			}
			else if(Bgn(TB,Elmt(M,i,j)).owner==2) {
				print_green(Bgn(TB,Elmt(M,i,j)).type);
			}
			else{
				printf("%c",(Bgn(TB,Elmt(M,i,j)).type));
			}
			// if (j<GetLastIdxKol(M)) printf(" ");	
		}
		printf("*\n");
	}
	for (i =1; i<=GetLastIdxKol(M)+2; ++i){
		printf("*");
	}
	printf("\n");
}
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/