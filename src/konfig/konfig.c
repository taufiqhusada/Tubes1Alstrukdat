/* Tgl: 26 Oktober 2019 */
/* Program untuk membaca konfigurasi permainan */

/* * * * PROSES * * * * /
/* input: konfigurasi.txt */

/* adv  type     desc                            */
/* 01   int      tinggi peta                     */
/* 02   int      lebar peta                      */
/* 03   int      jumlah bangunan, 4 < B < 30     */
/* //   i traversal [1 .. B]                   */
/* 01   char     tipe bangunan, C/T/F/V          */
/* 02   int      absis bangunan                  */
/* 03   int      ordinat bangunan                */ 
/* //   i traversal [1 .. B]                   */
/* 01   int      graf keterhubungan              */

#include <stdio.h>
#include "boolean.h"
#include "mesinkar.h"
#include "mesintoken.h"
// #include "bangunan.h"

/* VARIABEL GLOBAL */
boolean EndToken;
Token CToken;
int mapheight, mapwidth, B;
// TBangunan TB;

int main() {
    /* KAMUS */
    int i;
    char type;
    int absis;
    int ordinat;

    /* ALGORITMA */
        // membaca tinggi, lebar, dan jumlah bangunan
        STARTTOKEN();
        mapheight = CToken.val;
        ADVTOKEN();
        mapwidth = CToken.val;
        ADVTOKEN();
        B = CToken.val;
        ADVTOKEN();
        printf("w:%d h:%d B:%d\n", mapheight, mapwidth, B);
        
        // membaca data bangunan sebanyak B
        for (i = 1; i <= B; i++) {
            type = CToken.bgn;
            ADVTOKEN();
            absis = CToken.val;
            ADVTOKEN();
            ordinat = CToken.val;
            ADVTOKEN();
            printf("[%d] t:%c x:%d y:%d\n", i, type, absis, ordinat);
            
            /*
            Type(Bgn(TB, i)) = CToken.bgn;
            ADVTOKEN();
            Absis(Bgn(TB, i)) = CToken.val;
            ADVTOKEN();
            Ordinat(Bgn(TB, i)) = CToken.val;
            ADVTOKEN();
            */
        }

        // membaca graf keterhubungan bangunan
        
        
}