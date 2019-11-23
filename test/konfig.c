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
#include <stdlib.h>
#include "../src/pcolor/pcolor.h"
#include "../src/graph/multilist.h"
#include "../src/bangunan/boolean.h"
#include "../src/konfig/mesinkar.h"
#include "../src/konfig/mesintoken.h"
#include "../src/konfig/petaMatriks.h"
#include "../src/bangunan/bangunan.h"

/* VARIABEL GLOBAL */
boolean EndToken;
Token CToken;
int mapheight, mapwidth, B;
TBangunan TB;

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
        printf("HASIL KONFIGURASI: \n");
        printf("width: %d | height: %d | Bangunan: %d\n\n", mapheight, mapwidth, B);

        // insisialisasi matriks untuk menyimpan peta
        MATRIKS M;
        MakeMATRIKS(mapheight,mapwidth,&M);

        // membaca data bangunan sebanyak B
        printf("[ TIPE DAN LETAK BANGUNAN ]\n");
        for (i = 1; i <= B; i++) { 
            Bgn(TB,i).idxArray = i;
            type(Bgn(TB, i)) = CToken.bgn;
            ADVTOKEN();
            absis(Bgn(TB, i)) = CToken.val;
            ADVTOKEN();
            ordinat(Bgn(TB, i)) = CToken.val;
            CreateBangunan(&Bgn(TB,i));
            ADVTOKEN();
            Elmt(M,absis(Bgn(TB, i)),ordinat(Bgn(TB, i))) = i;
            printf("[%d] t:%c x:%d y:%d\n", i,type(Bgn(TB, i)), absis(Bgn(TB, i)), ordinat(Bgn(TB, i)));
        }
        printf("\n");

        printf("[ PETA PERMAINAN ]\n");
        TulisMATRIKS(M,TB);
        printf("\n");

        printf("[ CEK ISI ARRAY ] \n");
        for (i = 1; i <= B; i++) {
            printf("%d. ", i);
            TulisDataBangunan(Bgn(TB, i));
            printf("\n");
        }
        printf("\n");

        // Memasukkan connected components ke multilist
        printf("[ KETERHUBUNGAN ANTARBANGUNAN ]");
        Multilist L;
	    CreateEmptyMultilist(&L);
        for (i = 1; i<=B; ++i){
            int j;
            for (j = 1; j<=B; ++j){
                if (CToken.val==1){
                    InsertPair(&L, i, j);
                    //InsertPair(&L, j, i);
                    //if (IsConnectedDirect(L,i,j)) printf("%d %d \n", i, j);
                }
                ADVTOKEN();
            }
        }
        printf("\n");

        // cek keterkoneksian di graph (untuk debugging aja)
        int *arrResult = (int*) malloc(100*sizeof(int));
        int sizeArr = 0;
        for (i = 1; i<=B; ++i){
            printf("%d -> ", i);
            FindAllAdj(L,i,&arrResult,&sizeArr);
            if (sizeArr==0){
                printf("do not have any adj node\n");
            }
            else{
                int j;
                for (j = 1; j<=sizeArr; ++j){
                    printf("%d ", arrResult[j]);
                }
                printf("\n");
            }
        }


}