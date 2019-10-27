/* File: bangunan.h */
/* Definisi untuk bangunan */

#ifndef _BANGUNAN_
#define _BANGUNAN_

#include "boolean.h"

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
    int U;          // pasukan awal untuk menjadikan bangunan ini milik pemain
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
// array
#define Bgn(T, i) (T).TB[(i)]

/* ***** SET UP ***** */
void CreateBangunan(BANGUNAN *B);
/* Membentuk bangunan yang ada di dalam game */
/* I.S. Sembarang */
/* F.S. Terbentuk sebuah bangunan dengan properti level 1 */

/* ***** OPERATIONS ***** */
void LevelUp(BANGUNAN *B);
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
void Move(BANGUNAN *B1, BANGUNAN *B2); 
// apa ini masuk commands aja

/* **** TESTS ***** */
boolean MaxPas(BANGUNAN B);
/* True jika jumlah pasukan >= M */
boolean Upgradeable(BANGUNAN B);
/* True jika jumlah pasukan >= M/2 */
boolean CanConquer(BANGUNAN B1, BANGUNAN B2);
/* True jika jumlah pasukan B1 >= (B2).U */
/* Berarti pasukan B1 dapat mengambil alih bangunan B2 */
boolean Connected(BANGUNAN B1, BANGUNAN B2);
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