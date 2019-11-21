
#include "../konfig/boolean.h"
#include "stackToken.h"

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyStack(Stack *S){
	(*S).TOP = NilStack;
}
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxElStack */
/* jadi indeksnya antara 1.. MaxElStack+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP berNilStackai NilStack */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack(Stack S){
	return TopStack(S)==NilStack;
}
/* Mengirim true jika Stack kosong: lihat definisi di atas */
boolean IsFullStack(Stack S){
	return TopStack(S) == MaxElStack;
}
/* Mengirim true jika tabel penampung NilStackai elemen stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void PushStack(Stack * S, char tipeEl, BANGUNAN bChange){
	TopStack(*S)++;
	InfoTopTipeEl(*S) = tipeEl;
	InfoTopBangunan(*S) = bChange;
}

void PushStackConquered(Stack *S, char tipeEl, BANGUNAN bChange, int listAsal, int idxList ){
	TopStack(*S)++;
	InfoTopTipeEl(*S) = tipeEl;
	InfoTopBangunan(*S) = bChange;
	InfoTop(*S).asalList = listAsal;
	InfoTop(*S).posList = idxList;
}
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void PopStack(Stack * S, BANGUNAN* X){
	*X = InfoTopBangunan(*S);
	TopStack(*S)--;
}
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah NilStackai elemen TOP yang lama, TOP berkurang 1 */

