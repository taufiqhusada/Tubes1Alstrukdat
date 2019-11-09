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
#include "konfig/boolean.h"
#include "konfig/mesinkar.h"
#include "konfig/mesintoken.h"
#include "konfig/petaMatriks.h"
#include "bangunan/bangunan.h"
#include "permainan/permainan.h"

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
        printf("w:%d h:%d B:%d\n", mapheight, mapwidth, B);

        // insisialisasi matriks untuk menyimpan peta
        MATRIKS M;
        MakeMATRIKS(mapheight,mapwidth,&M);

        // membaca data bangunan sebanyak B
        for (i = 1; i <= B; i++) { 
            type(Bgn(TB, i)) = CToken.bgn;
            ADVTOKEN();
            absis(Bgn(TB, i)) = CToken.val;
            ADVTOKEN();
            ordinat(Bgn(TB, i)) = CToken.val;
            ADVTOKEN();
            Elmt(M,absis(Bgn(TB, i)),ordinat(Bgn(TB, i))) = Bgn(TB,i);
            printf("[%d] t:%c x:%d y:%d\n", i,type(Bgn(TB, i)), absis(Bgn(TB, i)), ordinat(Bgn(TB, i)));
        }
        TulisMATRIKS(M);


        // membaca graf keterhubungan bangunan
        boolean isRunProgram = true;
        int playerTurn = 1;
        Player player1;
        Player player2;
        init(&player1);
        init(&player2);
        while(isRunProgram){
            char inputCommand[20];
            scanf("%s", inputCommand);
            if (inputCommand=="ATTACK"){
                printBangunan(player1);
                printBangunan(player2);
                if (playerTurn==1){
                    
                }
            }
            else if (inputCommand=="LEVEL_UP"){
                if (playerTurn==1){
                    printBangunan(player1);      
                }
                else{
                    printBangunan(player2);
                }
                int inputPilihan;
                scanf("%d", &inputPilihan);
                LevelUp(&Bgn(TB,inputPilihan));
            }
            else if (inputCommand=="SKILL"){
                if (playerTurn==1) {
                    printSkill(player1);
                    if (!IsEmptyQueue(player1.qSkillPlayer)){

                    }
                }
                else {
                    printSkill(player2);
                    if (!IsEmptyQueue(player2.qSkillPlayer)){

                    }
                }
            
            }
            else if (inputCommand=="UNDO"){

            }
            else if (inputCommand=="END_TURN"){
                playerTurn ^= 3;
            }
            else if (inputCommand=="MOVE"){

            }
            else if (inputCommand=="EXIT"){
                isRunProgram = false;
            }
            else{
                printf("input salah, ulangi \n");
            }

        }
        
        
}
