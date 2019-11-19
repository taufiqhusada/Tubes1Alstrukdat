/* Body untuk ADT bangunan.h */
/* 27 Oktober 2019 */

#include <stdio.h>
#include "../graph/multilist.h"
#include "bangunan.h"

/* ***** SET UP ***** */
void copyBangunan(BANGUNAN *Bawal, BANGUNAN *BTarget){
    (*BTarget).A = (*Bawal).A;
    (*BTarget).M = (*Bawal).M;
    (*BTarget).P = (*Bawal).P;
    (*BTarget).U = (*Bawal).U;
    (*BTarget).absis = (*Bawal).absis;
    (*BTarget).ordinat = (*Bawal).ordinat;
    (*BTarget).type = (*Bawal).type;
    (*BTarget).owner = (*Bawal).owner;
    (*BTarget).nbPasukan = (*Bawal).nbPasukan;
    (*BTarget).level = (*Bawal).level;
    (*BTarget).idxArray = (*Bawal).idxArray;
    (*BTarget).isAdaPertahanan = (*Bawal).isAdaPertahanan;
}


void CreateBangunan(BANGUNAN *B) {
/* Membentuk bangunan yang ada di dalam game */
/* I.S. Terdapat bangunan tipe C/T/V/F di titik tertentu */
/* F.S. Bangunan dilengkapi dengan properti level 1 */
    if (type(*B) == 'C') {
        A(*B) = 10;
        M(*B) = 40;
        P(*B) = false;
        U(*B) = 40;
    }
    else if (type(*B) == 'T') {
        A(*B) = 5;
        M(*B) = 20;
        P(*B) = true;
        U(*B) = 30;
    }
    else if (type(*B) == 'F') {
        A(*B) = 10;
        M(*B) = 20;
        P(*B) = false;
        U(*B) = 80;
    }
    else if (type(*B) == 'V') {
        A(*B) = 5;
        M(*B) = 20;
        P(*B) = false;
        U(*B) = 20;
    }
    nbPas(*B) = U(*B);
    level(*B) = 1;
    isAdaPertahanan(*B) = false;
    if (type(*B)=='T'){
        isAdaPertahanan(*B) = true;
    }
    //TulisDataBangunan(*B);
}

/* ***** OPERATIONS ***** */
void LevelUp(BANGUNAN *B, boolean *status) {
/* Melevel up bangunan yang dimiliki pemain */
/* I.S. Pemain memiliki bangunan */
/* F.S. Bangunan yang dimiliki pemain naik satu level, yang berarti */
/*      properti AMPU bangunan pemain juga bertambah sesuai level */
/*      dan jumlah pasukan berkurang sebanyak M/2 */
/* Syarat: jumlah pasukan yang harus dimiliki bangunan: M/2 */
    if (Upgradeable(*B)) {
        *status = true;
        // mengurangi jumlah pasukan
        nbPas(*B) = nbPas(*B) - M(*B)/2;
        // menaikkan level
        switch (level(*B)) {
            case 1: // to level 2
                level(*B) = 2;
                switch (type(*B)) {
                    case 'C':
                        A(*B) = 15;
                        M(*B) = 60;
                    break;
                    case 'T':
                        A(*B) = 10;
                        M(*B) = 30;
                    break;
                    case 'F':
                        A(*B) = 20;
                        M(*B) = 40;
                    break;
                    case 'V':
                        A(*B) = 10;
                        M(*B) = 30;
                    break;
                }
            break;
            case 2: // to level 3
                level(*B) = 3;
                switch (type(*B)) {
                    case 'C':
                        A(*B) = 20;
                        M(*B) = 80;
                    break;
                    case 'T':
                        A(*B) = 20;
                        M(*B) = 40;
                    break;
                    case 'F':
                        A(*B) = 30;
                        M(*B) = 60;
                        P(*B) = true;
                    break;
                    case 'V':
                        A(*B) = 15;
                        M(*B) = 40;
                    break;
                }
            break;
            case 3: // to level 4
                level(*B) = 4;
                switch (type(*B)) {
                    case 'C':
                        A(*B) = 25;
                        M(*B) = 100;
                    break;
                    case 'T':
                        A(*B) = 30;
                        M(*B) = 50;
                    break;
                    case 'F':
                        A(*B) = 40;
                        M(*B) = 80;
                    break;
                    case 'V':
                        A(*B) = 20;
                        M(*B) = 50;
                    break;
                }
            break;
            default: 
            // dont do anything
            break;
        }
    }
    else{
        *status = false;
    }
}
void Conquered(BANGUNAN *B) { // apa masuk commands aja?
/* Dipakai ketika bangunan berhasil direbut oleh lawan */
/* I.S. Bangunan *B dimiliki oleh salah satu pemain */
/* F.S. Jika bangunan diserang dengan jumlah pasukan lebih dari U */
/*      kepemilikan bangunan diganti menjadi pemain yang lain dan */
/*      level bangunan direset menjadi level 1 */

// butuh variabel current_player ga sih
}
void AddPasukan(BANGUNAN *B) {
/* Menambah jumlah pasukan di setiap awal giliran */
/* I.S. Terdapat bangunan *B */
/* F.S. Jika jumlah pasukan di bangunan *B belum mencapai batas M, */
/*      jumlah pasukan ditambah sebanyak A */
    if (!MaxPas(*B)) {
        nbPas(*B) = nbPas(*B) + A(*B);
    }
}
void Move(Multilist L, BANGUNAN *B1, BANGUNAN *B2, int N, boolean*status){ // apa ini masuk commands aja
/* Memindahkan pasukan sebanyak N dari bangunan B1 ke bangunan B2 */
/* I.S. Terdapat dua buah bangunan, jumlah pasukan bebas */
/* F.S. Pasukan di B1 berkurang sejumlah N, di B2 bertambah sejumlah N */ 
    if (Connected(L, *B1, *B2) && SameOwner(*B1, *B2)) {
        if (nbPas(*B1) < N) {
            printf("Jumlah pasukan tidak mencukupi.");
            *status = false;
        }
        else {
            nbPas(*B1) = nbPas(*B1) - N;
            nbPas(*B2) = nbPas(*B2) + N;
            *status = true;
        }
    }
}
void ChangeOwnerB(BANGUNAN *B) {
/* I.S. Terdapat bangunan *B dengan owner salah seorang pemain */
/* F.S. Bangunan *B menjadi milik lawan pemain */
    if (owner(*B) == 1) {
        owner(*B) = 2;
    }
    else if (owner(*B) == 2) {
        owner(*B) = 1;
    }
}
void TulisDataBangunan(BANGUNAN B){
/* I.S. Terdapat bangunan B */
/* F.S. Tercetak data bangunan B di layar */
/* Prekondisi: bangunan sudah dimiliki salah satu player */
/* Format pencetakan: <nomor> <nama bangunan> <koordinat> <jumlah pasukan> <level>
/* Contoh : 1. Castle (1,15) 20 lv. 3 */
    /* KAMUS */
    /* ALGORITMA */
    // tulis jenis bangunan
    switch(type(B)) {
        case 'C':
            printf("Castle ");
            break;
        case 'T':
            printf("Tower ");
            break;
        case 'F':
            printf("Fort ");
            break;
        case 'V':
            printf("Village ");
            break;
    }

    // tulis posisi, jumlah pasukan, level
    printf("(%d, %d) %d lv. %d", absis(B), ordinat(B), nbPas(B), level(B));
}

/* **** TESTS ***** */
boolean MaxPas(BANGUNAN B) {
/* True jika jumlah pasukan >= M */
    return (nbPas(B) >= M(B));
}
boolean Upgradeable(BANGUNAN B) {
/* True jika jumlah pasukan >= M/2 */
    return (nbPas(B) >= M(B)/2);
}
boolean CanConquer(BANGUNAN B1, BANGUNAN B2) {
/* True jika jumlah pasukan B1 >= (B2).U */
/* Berarti pasukan B1 dapat mengambil alih bangunan B2 */
    return (nbPas(B1) >= U(B2));
}
boolean Connected(Multilist L, BANGUNAN B1, BANGUNAN B2) {
    return IsConnectedDirect(L, B1.idxArray, B2.idxArray);
/* True jika B1 dan B2 saling terhubung */
}
boolean SameOwner(BANGUNAN B1, BANGUNAN B2) {
/* True jika B1 dan B2 dimiliki pemain sama */
    return (owner(B1) == owner(B2));
}