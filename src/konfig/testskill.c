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
#include "petaMatriks.h"
#include "../bangunan/bangunan.h"
#include "../skill/skill.h"
#include "../permainan/permainan.h"

/* VARIABEL GLOBAL */
boolean EndToken;
Token CToken;
int mapheight, mapwidth, B;
TBangunan TB;
Queue skilldummy, skillenemy;
Player dummy, enemy;

int main() {

    /* KAMUS */
    int i;
    char type;
    int absis;
    int ordinat;
    int playerTurn;
    boolean IsExtraTurn;
    boolean IsAttackUp;
    boolean IsCriticalHit;

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

        MATRIKS M;
        MakeMATRIKS(mapheight,mapwidth,&M);
        // membaca data bangunan sebanyak B
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
        }

    // Doing Skill things

    int owner = 1;
    Init(&dummy);
    InsVFirst(&dummy.listBangunan,TB, 1);
    Bgn(TB,1).owner = 1;

    Init(&enemy);
    InsVFirst(&enemy.listBangunan,TB, 2);
    Bgn(TB,2).owner = 2;

    playerTurn = 1;

    int getSkill;

    printf("Skill ID = ");
    scanf("%d", &getSkill);


    CreateEmptyQueue(&skilldummy, MaxQueue);
    addSkill(&skilldummy, 7);

    switch (getSkill) {

        case 0:
            PrintSkillList(skilldummy);
            break;
        
        case 1:

            for (i = 1; i<=B; i++) {
                if (Bgn(TB,i).owner == 1) {
                    TulisDataBangunan(Bgn(TB,i));
                    printf("\n");
                }
            }

            addSkill(&skilldummy, 1);
            InstantUpgrade(&skilldummy, owner, &TB);

            for (i = 1; i<=B; i++) {
                if (Bgn(TB,i).owner == 1) {
                    TulisDataBangunan(Bgn(TB,i));
                    printf("\n");
                }
            }

            break;
        
        case 2:

            printf("Player Turn : %d", playerTurn);

            addSkill(&skilldummy, 2);
            ExtraTurn(&skilldummy, &IsExtraTurn);


            break;

        case 3:


            for (i = 1; i<=B; i++) {
                if (Bgn(TB,i).owner == 1) {
                    level(Bgn(TB,i)) = 4;
                    (Bgn(TB,i).M) += 1;
                    TulisDataBangunan(Bgn(TB,i));
                    printf("\n");
                }
            }

            addSkill(&skilldummy, 3);
            InstantReinforcement(&skilldummy, owner, &TB);

            for (i = 1; i<=B; i++) {
                if (Bgn(TB,i).owner == 1) {
                    TulisDataBangunan(Bgn(TB,i));
                    printf("\n");
                }
            }

            break;

        case 4:

            printf("Data Bangunan Musuh Sebelum :\n");
            for (i = 1; i<=B; i++) {
                if (Bgn(TB,i).owner == 2) {
                    TulisDataBangunan(Bgn(TB,i));
                    printf("\n");
                }
            }

            addSkill(&skilldummy, 4);
            Barrage(&skilldummy, owner, &TB);

            printf("Data Bangunan Musuh Sesudah :\n");
            for (i = 1; i<=B; i++) {
                if (Bgn(TB,i).owner == 2) {
                    TulisDataBangunan(Bgn(TB,i));
                    printf("\n");
                }
            }

            break;



    }



}