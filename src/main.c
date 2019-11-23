/* Tgl: 26 Oktober 2019 */
/* Program untuk membaca konfigurasi permainan */

/* * * * PROSES * * * * */
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
#include "mesinkataSTDIN/mesinkataSTDIN.h"
#include "pcolor/pcolor.h"
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
#include "skill/skill.h"


/* VARIABEL GLOBAL */
boolean EndToken;
boolean IsExtraTurnP1, IsExtraTurnP2 = false;
boolean IsAttackUpP1, IsAttackUpP2 = false;
boolean IsCriticalHitP1, IsCriticalHitP2 = false;
Token CToken;
int mapheight, mapwidth, B;
TBangunan TB;

int main() {
    /* KAMUS */
    int i;
    char type;
    int absis;
    int ordinat;
    int sklOut;

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
            Elmt(M,absis(Bgn(TB, i)),ordinat(Bgn(TB, i))) = i;
            printf("[%d] t:%c x:%d y:%d\n", i,type(Bgn(TB, i)), absis(Bgn(TB, i)), ordinat(Bgn(TB, i)));
        }
        TulisMATRIKS(M,TB);

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
        Queue skill1;
        Queue skill2;

        // inisialisasi player 1
        Init(&player1);
        InsVFirst(&player1.listBangunan,TB, 1);
        Bgn(TB,1).owner = 1;
        printBangunan(player1,TB);
        CreateEmptyQueue(&skill1, MaxQueue);
        addSkill(&skill1, 1);
        
        // inisialisasi player 2
        Init(&player2);
        InsVFirst(&player2.listBangunan,TB, 2);
        Bgn(TB,2).owner = 2;
        printBangunan(player2,TB);
        CreateEmptyQueue(&skill2, MaxQueue);
        addSkill(&skill2, 1);

        TulisMATRIKS(M,TB);

        // inisialisasi stack
        Stack undoStack;        
        boolean status;     // untuk mengecek apakah proses command berhasil atau tidak, jika berhasil maka dimasukkan ke stack
        CreateEmptyStack(&undoStack);
       
        // memulai permainan
        while(isRunProgram){
            printf("\n");
            if (playerTurn==1){
                AddPasukanAll(player1.listBangunan,TB);
                printBangunan(player1,TB);
            }
            else{
                AddPasukanAll(player2.listBangunan,TB);
                printBangunan(player2,TB);
            }
            
            printf("Masukkan command: ");
            scanf("\n");
            STARTKATASTDIN();
           
            //printf(" ");
            
            if (CompareKata(CKataSTDIN,"ATTACK")){
                printBangunan(player1,TB);
                printBangunan(player2,TB);
                if (playerTurn==1){
                    printBangunan(player1, TB);
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
                    while (jumPasukan > Bgn(TB,attacking).nbPasukan) {
                        printf("Jumlah pasukan bangunan tidak sebanyak itu. \n");
                        printf("Silakan masukan kembali jumlah pasukan: ");
                        scanf("%d", &jumPasukan);
                    }

                    //SETELAH ATTACK

                    // dapat skill attack up
                    if (jumlahtower(player2.listBangunan, TB)==3){
                        addSkill(&skill1, 6);
                    }

                    // mendapat skill extra turn
                    // if (/*attack berhasil && (type(Bgn(T(L),I(L)))=="F")*/) {
                    //     addSkill(&skill2, 2);
                    // }

                    // mendapat skill barrage
                    if (NbBangunan(player1.listBangunan) == 10) {
                        addSkill(&skill2, 4);
                    }

                    // mendapat skill shield
                    if (NbBangunan(player2.listBangunan) == 2) {
                        addSkill(&skill2, 5);
                    }

                    // Cek Menang
                    if (NbBangunan(player2.listBangunan)==0){
                        printf("SEMUA BANGUNAN PLAYER 2 SUDAH DIKUASAI PLAYER 1");
                        printf("SELAMAT PLAYER 1 MENANG");
                        isRunProgram = false;


                    }
                }
            }
            else if (CompareKata(CKataSTDIN,"LEVELUP")){
                //printf("ini level up\n");
                if (playerTurn==1){
                    printf("Daftar bangunan: \n");
                    printBangunan(player1,TB);   
                    printf("Pilihan bangunan: ");
                    int inputPilihan;
                    scanf("%d", &inputPilihan);
                    BANGUNAN before;
                    int pos = GoTo(player1.listBangunan,inputPilihan)->i;
                    copyBangunan(&Bgn(TB,pos), &before);
                    LevelUp(&Bgn(TB,pos), &status);   
                    if (status){
                        PushStack(&undoStack, 'L', before);
                    }
                }
                else{
                    printf("Daftar bangunan: \n");
                    printBangunan(player2,TB);
                    printf("Pilihan bangunan: ");
                    int inputPilihan;
                    scanf("%d", &inputPilihan);
                    BANGUNAN before;
                    int pos = GoTo(player2.listBangunan,inputPilihan)->i;
                    copyBangunan(&Bgn(TB,pos), &before);
                    LevelUp(&Bgn(TB,pos), &status);   
                    if (status){
                        PushStack(&undoStack, 'L', before);
                    }
                }
                
            }
            else if (CompareKata(CKataSTDIN,"SKILL")){
                if (playerTurn==1) {
                    printSkill(skill1);
                    if (!IsEmptyQueue(skill1)){
                        // Calling Skill
                        sklOut = InfoHeadQueue(skill1);

                        switch (sklOut) {
                            1: 
                                InstantUpgrade(&skill1, playerTurn, &TB);
                                break;
                            
                            2:
                                ExtraTurn(&skill1,&IsExtraTurnP1);
                                break;
                            
                            3:
                                InstantReinforcement(&skill1, playerTurn, &TB);
                                break;

                            4:
                                Barrage(&skill1, playerTurn, &TB);
                                break;

                            5:
                                Shield(&skill1, playerTurn, &TB);
                                break;
                            
                            6:
                                AttackUp(&skill1, &IsAttackUpP1);
                                break;

                            7:
                                CriticalHit(&skill1, &IsCriticalHitP1);
                                break;


                        } // End of Switch

                    }
                }
                else {
                    printSkill(skill2);
                    if (!IsEmptyQueue(skill2)){
                        // Calling Skill
                        sklOut = InfoHeadQueue(skill2);

                        switch (sklOut) {
                            1: 
                                InstantUpgrade(&skill2, playerTurn, &TB);
                                break;
                            
                            2:
                                ExtraTurn(&skill2,&IsExtraTurnP1);
                                break;
                            
                            3:
                                InstantReinforcement(&skill2, playerTurn, &TB);
                                break;

                            4:
                                Barrage(&skill2, playerTurn, &TB);
                                break;

                            5:
                                Shield(&skill2, playerTurn, &TB);
                                break;
                            
                            6:
                                AttackUp(&skill2, &IsAttackUpP2);
                                break;

                            7:
                                CriticalHit(&skill2, &IsCriticalHitP2);
                                break;


                        } // End of Switch


                    }
                }
		    
		    
            }
            else if (CompareKata(CKataSTDIN,"UNDO")){
                if (IsEmptyStack(undoStack)){
                    printf("Tidak bisa undo, stack kosong\n");
                }   
                else if (InfoTopTipeEl(undoStack)=='L'){
                    BANGUNAN hasilUndo;
                    PopStack(&undoStack, &hasilUndo);
                    int pos = hasilUndo.idxArray;
                    copyBangunan(&hasilUndo,&Bgn(TB,pos));
                }
                else if (InfoTopTipeEl(undoStack)=='M'){
                    BANGUNAN hasilUndo1;
                    PopStack(&undoStack, &hasilUndo1);
                    int pos1 = hasilUndo1.idxArray;
                    copyBangunan(&hasilUndo1,&Bgn(TB,pos1));

                    BANGUNAN hasilUndo2;
                    PopStack(&undoStack, &hasilUndo2);
                    int pos2 = hasilUndo2.idxArray;
                    copyBangunan(&hasilUndo2,&Bgn(TB,pos2));
                }
                else if (InfoTopTipeEl(undoStack)=='C'){ // attack and conquered
                    // bangunan yang ter-conquered
                    BANGUNAN hasilUndo1;
                    int listAsal = InfoTop(undoStack).asalList;
                    int idxList = InfoTop(undoStack).posList; 
                    PopStack(&undoStack, &hasilUndo1);
                    int pos1 = hasilUndo1.idxArray;
                    copyBangunan(&hasilUndo1,&Bgn(TB,pos1));
                    if (listAsal==1){
                        ChangeOwner(TB,player2.listBangunan, player1.listBangunan,idxList);
                    }
                    else{
                        ChangeOwner(TB,player1.listBangunan, player2.listBangunan,idxList);
                    }
                    
                    // bangunan yang sebelumnya menyerang
                    BANGUNAN hasilUndo2;
                    PopStack(&undoStack, &hasilUndo2);
                    int pos2 = hasilUndo2.idxArray;
                    copyBangunan(&hasilUndo2,&Bgn(TB,pos2));
                }
                else{   // attack but not conquered
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
            else if (CompareKata(CKataSTDIN,"ENDTURN")){
                // mendapatkan skill instant reinforcement
                // jika semua bangunannya berlevel 4

                // cek player
                adrBgn P;
                if (playerTurn == 1) {
                    List LB = listBangunan(player1);
                    P = (LB).First;
                }
                else {
                    List LB = listBangunan(player2);
                    P = (LB).First;
                }

                // cek bangunan
                boolean allmax = true;
                while (!allmax && P != NULL) {
                    if (level(Bgn(TB, I(P))) != 4) {
                        allmax = false;
                    }
                    else {
                        P = Next(P);
                    }
                }

                // menambah skill jika semua berlevel 4
                if (allmax && playerTurn == 1) {
                    addSkill(&skill1, 3);
                }
                else if (allmax && playerTurn == 2) {
                    addSkill(&skill2, 3);
                }

                // mengganti turn
                playerTurn ^= 3;
            }
            else if (CompareKata(CKataSTDIN,"MOVE")){
                //printf("%s", inputCommand); 
                if (playerTurn==1){
                    printf("Daftar bangunan:\n");
                    printBangunan(player1, TB);   
                    printf("Pilih bangunan: ");
                    int inputPilihan;
                    scanf("%d", &inputPilihan);
                    int pos = GoTo(player1.listBangunan,inputPilihan)->i;
                    sizeArr = 0;
                    FindAllAdj(L,pos,&arrResult,&sizeArr);
                    int j;
                    printf("%d\n",sizeArr);
                    boolean adaBangunanTerdekat = false;
                    for (j = 1; j<=sizeArr; ++j){
                        if (Bgn(TB,arrResult[j]).owner==1){
                            adaBangunanTerdekat = true;
                        }
                    }

                    if (!adaBangunanTerdekat){
                        printf("Tidak ada bangunan terdekat lain yang dimiliki \n");
                    }
                    else{
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
                            PushStack(&undoStack, 'M', before1);
                            PushStack(&undoStack, 'M', before2);
                        }
                    }
                }
                else{
                    printf("Daftar bangunan:\n");
                    printBangunan(player2,TB);   
                    printf("Pilih bangunan: ");
                    int inputPilihan;
                    scanf("%d", &inputPilihan);
                    int pos = GoTo(player2.listBangunan,inputPilihan)->i;
                    sizeArr = 0;
                    FindAllAdj(L,pos,&arrResult,&sizeArr);
                    int j;
                    boolean adaBangunanTerdekat = false;
                    for (j = 1; j<=sizeArr; ++j){
                        if (Bgn(TB,arrResult[j]).owner==2){
                            adaBangunanTerdekat = true;
                        }
                    }

                    if (!adaBangunanTerdekat){
                        printf("Tidak ada bangunan terdekat lain yang dimiliki \n");
                    }
                    else {
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
                            PushStack(&undoStack, 'M', before1);
                            PushStack(&undoStack, 'M', before2);
                        }
                    }
                }
            }
            else if (CompareKata(CKataSTDIN,"EXIT")){
                isRunProgram = false;
            }
            else{
                printf("input salah, ulangi \n");
            }

        }
        
        
}
