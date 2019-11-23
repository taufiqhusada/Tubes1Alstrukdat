/* File: bangunan.h */
/* Definisi untuk bangunan */

#ifndef _BANGUNAN_
#define _BANGUNAN_

#include "boolean.h"
#include "../graph/multilist.h"

#define IdxMax 30
#define IdxMin 1  // tapi minimal ada 4 bangunan
#define Undef  -99

/* ***** PROPERTI BANGUNAN ***** */
typedef struct {
    char type;      // tipe bangunan: C, T, F, atau V
    int owner;      // pemilik bangunan: 1, 2, atau Undef
    int nbPasukan;  // jumlah pasukan
    int level;      // level bangunan
    // Nilai AMPU haram diubah kecuali dengan fungsi level up
    int A;          // nilai penambahan pasukan
    int M;          // nilai maks penambahan
    boolean P;      // pertahanan
    int SDur;	    // Shield Duration
    int U;          // pasukan awal untuk menjadikan bangunan ini milik pemain
    int absis;      // letak absis
    int ordinat;    // letak ordinat
    int idxArray;
    boolean isAdaPertahanan; // Shield
	int pertahananDuration; // Durasi pertahanan (max 2 turn lawan) 
} BANGUNAN;

/* ***** ARRAY BANGUNAN ***** */
typedef struct {
    BANGUNAN TB[IdxMax];
} TBangunan;

/* ***** SELEKTOR ***** */
// properti
#define type(B)  (B).type
#define owner(B) (B).owner
#define nbPas(B) (B).nbPasukan
#define level(B) (B).level
// AMPU
#define A(B) (B).A
#define M(B) (B).M 
#define P(B) (B).P
#define U(B) (B).U
#define S(B) (B).isAdaPertahanan
#define SDur(B) (B).pertahananDuration
// array
#define Bgn(T, i) (T).TB[(i)]
// letak
#define absis(B) (B).absis
#define ordinat(B) (B).ordinat
// pertahanan
#define isAdaPertahanan(B) (B).isAdaPertahanan

/* ***** SET UP ***** */
void copyBangunan(BANGUNAN *Bawal, BANGUNAN *BTarget);

void CreateBangunan(BANGUNAN *B);
/* Membentuk bangunan yang ada di dalam game */
/* I.S. Sembarang */
/* F.S. Terbentuk sebuah bangunan dengan properti level 1 */

/* ***** OPERATIONS ***** */
void LevelUp(BANGUNAN *B, boolean *status);
/* Melevel up bangunan yang dimiliki pemain */
/* I.S. Pemain memiliki bangunan */
/* F.S. Bangunan yang dimiliki pemain naik satu level, yang berarti */
/*      properti AMPU bangunan pemain juga bertambah sesuai level */
/*      dan jumlah pasukan berkurang sebanyak M/2 */
/* Syarat: jumlah pasukan yang harus dimiliki bangunan: M/2 */
void Conquered(BANGUNAN *B);
/* Dipakai ketika bangunan berhasil direbut oleh lawan */
/* I.S. Bangunan *B dimiliki oleh salah satu pemain */
/* F.S. Jika bangunan diserang dengan jumlah pasukan lebih dari U */
/*      kepemilikan bangunan diganti menjadi pemain yang lain dan */
/*      level bangunan direset menjadi level 1 */
void AddPasukan(BANGUNAN *B);
/* Menambah jumlah pasukan di setiap awal giliran */
/* I.S. Terdapat bangunan *B */
/* F.S. Jika jumlah pasukan di bangunan *B belum mencapai batas M, */
/*      jumlah pasukan ditambah sebanyak A */
void Move(Multilist L, BANGUNAN *B1, BANGUNAN *B2, int N, boolean *status); 
// apa ini masuk commands aja
void ChangeOwnerB(BANGUNAN *B);
/* I.S. Terdapat bangunan *B dengan owner salah seorang pemain */
/* F.S. Bangunan *B menjadi milik lawan pemain */
void TulisDataBangunan(BANGUNAN B);
/* I.S. Terdapat bangunan B */
/* F.S. Tercetak data bangunan B di layar */
/* Format pencetakan: <nomor> <nama bangunan> <koordinat> <jumlah pasukan> <level> */
/* Contoh : 1. Castle (1,15) 20 lv. 3 */

/* **** TESTS ***** */
boolean MaxPas(BANGUNAN B);
/* True jika jumlah pasukan >= M */
boolean Upgradeable(BANGUNAN B);
/* True jika jumlah pasukan >= M/2 */
boolean CanConquer(BANGUNAN B1, BANGUNAN B2);
/* True jika jumlah pasukan B1 >= (B2).U */
/* Berarti pasukan B1 dapat mengambil alih bangunan B2 */
boolean Connected(Multilist L, BANGUNAN B1, BANGUNAN B2);
/* True jika B1 dan B2 saling terhubung */
boolean SameOwner(BANGUNAN B1, BANGUNAN B2);
/* True jika B1 dan B2 dimiliki pemain sama */

#endif

/* ***** FREE NOTES **** */
/* kita butuh adt player gak sih */
/* isinya list linier bangunan dia */
/* terus apakah itu turn dia atau bukan (end_turn) */
/* queue skill yang dia punya */
/* sama stack command buat undo */
