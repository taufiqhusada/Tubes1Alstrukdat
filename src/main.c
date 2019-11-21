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
#include <string.h>
#include "konfig/boolean.h"
#include "konfig/mesinkar.h"
#include "konfig/mesintoken.h"
#include "konfig/petaMatriks.h"
#include "bangunan/bangunan.h"
#include "bangunan/list_bangunan.h"
#include "stackUndo/stackToken.h"
#include "graph/multilist.h"
#include "skill/queue.h"
#include "permainan/permainan.h"


/* VARIABEL GLOBAL */
boolean EndToken;
boolean IsExtraTurn = false;
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
            Bgn(TB,i).idxArray = i;
            type(Bgn(TB, i)) = CToken.bgn;
            ADVTOKEN();
            absis(Bgn(TB, i)) = CToken.val;
            ADVTOKEN();
            ordinat(Bgn(TB, i)) = CToken.val;
            CreateBangunan(&Bgn(TB,i));
            ADVTOKEN();
            Elmt(M,absis(Bgn(TB, i)),ordinat(Bgn(TB, i))) = Bgn(TB,i);
            printf("[%d] t:%c x:%d y:%d\n", i,type(Bgn(TB, i)), absis(Bgn(TB, i)), ordinat(Bgn(TB, i)));
        }
        TulisMATRIKS(M);

        // Memasukkan connected components ke multilist
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
            printf("%d -> \n", i);
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

        // inisialisai permainan 
        boolean isRunProgram = true;
        int playerTurn = 1;
        Player player1;
        Player player2;

        // inisialisasi player 1
        Init(&player1);
        InsVFirst(&player1.listBangunan,TB, 1);
        Bgn(TB,1).owner = 1;
        printBangunan(player1);
        
        // inisialisasi player 2
        Init(&player2);
        InsVFirst(&player2.listBangunan,TB, 2);
        Bgn(TB,2).owner = 2;
        printBangunan(player2);

        // inisialisasi stack
        Stack undoStack;        
        boolean status;     // untuk mengecek apakah proses command berhasil atau tidak, jika berhasil maka dimasukkan ke stack
        CreateEmptyStack(&undoStack);

        // memulai permainan
        while(isRunProgram){
            
            char inputCommand[20]; 
            scanf("%s", inputCommand);
            
            if (strcmp(inputCommand,"ATTACK")==0){
                printBangunan(player1);
                printBangunan(player2);
                if (playerTurn==1){
                    printBangunan(player1);
                    int inputPenyerang;
                    printf("Pilih bangunan yang akan menyerang: ");
                    scanf("%d", &inputPenyerang);
                    int attacking = GoTo(player1.listBangunan, inputPenyerang) -> i;
                    sizeArr = 0;
                    FindAllAdj(L, attacking, &arrResult, &sizeArr);
                    int j;
                    for (j = 1; j <= sizeArr; j++) {
                        if (Bgn(TB, arrResult[j]).owner==2) {
                            printf("%d. ", Bgn(TB, arrResult[j]).idxArray);
                            TulisDataBangunan(Bgn(TB, arrResult[j]));
                            printf("\n");
                        }
                    }
                    printf("Pilih bangunan yang akan diserang: ");
                    int inputDiserang;
                    scanf("%d", &inputDiserang);
                    int jumPasukan;
                    printf("Jumlah pasukan yang akan menyerang: ");
                    scanf("%d", &jumPasukan);
                    // validasi jumlah pasukan yang menyerang
                    while (jumPasukan > attacking.nbPas) {
                        printf("Jumlah pasukan bangunan tidak sebanyak itu. \n");
                        printf("Silakan masukan kembali jumlah pasukan: ");
                        scanf("%d", &jumPasukan);
                    }

                    // mendapat skill extra turn
                    // jika yang direbut adalah fort
                    if (type(*B) == 'F') {
                        AddQueue(player2).qSkillPlayer, "ET");
                    }

                    // mendapat skill barrage
                    if (NbBangunan(listBangunan(player1) == 10) {
                        AddQueue(player2.qSkillPlayer, "B");
                    }
                }
            }
            else if (strcmp(inputCommand,"LEVEL_UP")==0){
                if (playerTurn==1){
                    printf("Daftar bangunan: \n");
                    printBangunan(player1);   
                    printf("Pilihan bangunan: ");
                    int inputPilihan;
                    scanf("%d", &inputPilihan);
                    BANGUNAN before;
                    int pos = GoTo(player1.listBangunan,inputPilihan)->i;
                    copyBangunan(&Bgn(TB,pos), &before);
                    LevelUp(&Bgn(TB,pos), &status);   
                    if (status){
                        PushStack(&undoStack, 1, before);
                    }
                }
                else{
                    printf("Daftar bangunan: \n");
                    printBangunan(player2);
                    printf("Pilihan bangunan: ");
                    int inputPilihan;
                    scanf("%d", &inputPilihan);
                    BANGUNAN before;
                    int pos = GoTo(player2.listBangunan,inputPilihan)->i;
                    copyBangunan(&Bgn(TB,pos), &before);
                    LevelUp(&Bgn(TB,pos), &status);   
                    if (status){
                        PushStack(&undoStack, 1, before);
                    }
                }
                
            }
            else if (strcmp(inputCommand,"SKILL")==0){
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
            else if (strcmp(inputCommand,"UNDO")==0){
                if (IsEmptyStack(undoStack)){
                    printf("Tidak bisa undo, stack kosong\n");
                }   
                else if (InfoTopJumlahPush(undoStack)==1){
                    BANGUNAN hasilUndo;
                    PopStack(&undoStack, &hasilUndo);
                    int pos = hasilUndo.idxArray;
                    copyBangunan(&hasilUndo,&Bgn(TB,pos));
                }
                else{// pop 2 kali
                    BANGUNAN hasilUndo1;
                    PopStack(&undoStack, &hasilUndo1);
                    int pos1 = hasilUndo1.idxArray;
                    copyBangunan(&hasilUndo1,&Bgn(TB,pos1));

                    BANGUNAN hasilUndo2;
                    PopStack(&undoStack, &hasilUndo2);
                    int pos2 = hasilUndo2.idxArray;
                    copyBangunan(&hasilUndo2,&Bgn(TB,pos2));
                }
            }
            else if (strcmp(inputCommand,"END_TURN")==0){
            // mendapatkan skill instant reinforcement
            // jika semua bangunannya berlevel 4

            // cek player
            if (playerTurn == 1) {}
                adrBgn P = listBangunan(player1);
            }
            else {
                adrBgn P = listBangunan(player2);
            }

            // cek bangunan
            boolean allmax = true;
            while (!allmax && P != Nil) {
                if (level(Bgn(TB(P), I(P)) != 4) {
                    allmax = false;
                }
                else {
                    P = Next(P);
                }

            // menambah skill jika semua berlevel 4
            if (allmax && playerTurn == 1) {
                AddQueue(player1.qSkillPlayer, "IR");
            }
            else if (allmax && playerTurn == 2) {
                AddQueue(player2.qSkillPlayer, "IR");
            }

            // mengganti turn
                playerTurn ^= 3;
            }
            else if (strcmp(inputCommand,"MOVE")==0){
                //printf("%s", inputCommand); 
                if (playerTurn==1){
                    printf("Daftar bangunan:\n");
                    printBangunan(player1);   
                    printf("Pilih bangunan: ");
                    int inputPilihan;
                    scanf("%d", &inputPilihan);
                    int pos = GoTo(player1.listBangunan,inputPilihan)->i;
                    sizeArr = 0;
                    FindAllAdj(L,pos,&arrResult,&sizeArr);
                    int j;
                    printf("Daftar bangunan terdekat yang dimiliki:\n");
                    for (j = 1; j<=sizeArr; ++j){
                        if (Bgn(TB,arrResult[j]).owner==1){
                            printf("%d. ", Bgn(TB,arrResult[j]).idxArray);
                            TulisDataBangunan(Bgn(TB,arrResult[j]));
                            printf("\n");   
                        }
                    }
                    printf("Bangunan yang akan menerima: ");
                    int BMenerima;
                    scanf("%d",&BMenerima);
                    int jumPasukan;
                    printf("Jumlah pasukan: ");
                    scanf("%d", &jumPasukan);
                    BANGUNAN before1;
                    BANGUNAN before2;
                    copyBangunan(&Bgn(TB,pos), &before1);
                    copyBangunan(&Bgn(TB,BMenerima), &before2);
                    Move(L,&Bgn(TB,pos), &Bgn(TB,BMenerima), jumPasukan, &status);
                    if (status){
                        PushStack(&undoStack, 2, before1);
                        PushStack(&undoStack, 2, before2);
                    }
                }
                else{
                    printf("Daftar bangunan:\n");
                    printBangunan(player2);   
                    printf("Pilih bangunan: ");
                    int inputPilihan;
                    scanf("%d", &inputPilihan);
                    int pos = GoTo(player2.listBangunan,inputPilihan)->i;
                    sizeArr = 0;
                    FindAllAdj(L,pos,&arrResult,&sizeArr);
                    int j;
                    printf("Daftar bangunan terdekat yang dimiliki:\n");
                    for (j = 1; j<=sizeArr; ++j){
                        if (Bgn(TB,arrResult[j]).owner==2){
                            printf("%d. ", Bgn(TB,arrResult[j]).idxArray);
                            TulisDataBangunan(Bgn(TB,arrResult[j]));
                            printf("\n");   
                        }
                    }
                    printf("Bangunan yang akan menerima: ");
                    int BMenerima;
                    scanf("%d",&BMenerima);
                    int jumPasukan;
                    printf("Jumlah pasukan: ");
                    scanf("%d", &jumPasukan);
                    BANGUNAN before1;
                    BANGUNAN before2;
                    copyBangunan(&Bgn(TB,pos), &before1);
                    copyBangunan(&Bgn(TB,BMenerima), &before2);
                    Move(L,&Bgn(TB,pos), &Bgn(TB,BMenerima), jumPasukan, &status);
                    if (status){
                        PushStack(&undoStack, 2, before1);
                        PushStack(&undoStack, 2, before2);
                    }
                }
            }
            else if (strcmp(inputCommand,"EXIT")==0){
                isRunProgram = false;
            }
            else{
                printf("input salah, ulangi \n");
            }

        }
        
        
}
