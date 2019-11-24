#include <stdio.h>
#include <stdlib.h>
#include "save.h"
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




void printbangunan (TBangunan TB, int x, FILE* fp){
/* I.S. array TB terdefinisi */
/* F.S. print array TB ke file */
    int i;
	for (i = 1; i <= x; i++) {
        fprintf(fp, "%c ", type(Bgn(TB,i)));
        fprintf(fp, "%d ", absis(Bgn(TB,i)));
        fprintf(fp, "%d ", ordinat(Bgn(TB,i)));
        fprintf(fp, "%d ", nbPas(Bgn(TB,i)));
        fprintf(fp, "%d ", level(Bgn(TB,i)));
        fprintf(fp, "%d ", owner(Bgn(TB,i)));
        fprintf(fp, " \n");
	}
}

void printskill(Queue Q, FILE* fp){
/* I.S. Queue skill terdefinisi */
/* F.S. print queue skill ke file */ 
    int i, j, queueLen, skillID;
    queueLen = NBElmtQueue(Q);
    if (queueLen == 0) {
        fprintf(fp, " \n");
    }
    else {
        i = 1;
        j = HeadQueue(Q);
        while (i <= queueLen) {
            skillID = (Q).T[j];
            fprintf(fp, "%d ", skillID);
            i++;
            if (j == TailQueue(Q)) {
                j = 1;
            }
            else {
                j++;
            }
        }
        fprintf(fp, " \n");
    }
}

void printlistbangunan(Player P, TBangunan TB, FILE* fp){
/* I.S. list bangunan yang dimiliki player terdefinisi */
/* F.S. print list bangunan skill ke file */ 
    int i;
    adrBgn L;
    i = 1;
    L = First(P.listBangunan);
    while (L != NilLBangunan) {
        fprintf(fp, "%d ", I(L));
        i++;
        L = Next(L);
    }
    fprintf(fp, " \n");
}


void save (int B, int h, int w, TBangunan TB, Queue a, Queue b, int x, int y, Player m, Player n){
/* I.S. jumlah bangunan, tinggi peta, lebar peta, array bangunan (TB), queue skill pemain 1 dan 2, 
counter shield pemain 1 dan 2, dan list bangunan yang dimiliki player 1 dan 2 terdefinisi */
/* F.S. print jumlah bangunan, tinggi peta, lebar peta, array bangunan (TB), queue skill pemain 1 dan 2, 
counter shield pemain 1 dan 2, dan list bangunan yang dimiliki player 1 dan 2 ke file */ 
    
    char filename[100];
    printf("Nama file yang diinginkan : ");
    scanf("%s", &filename);

    FILE * fp;
    fp = fopen (filename, "w");
    
    fprintf(fp, "%d \n", B); /* Print jumlah bangunan */

    fprintf(fp, "%d \n", h); /* Print mapheigth */
    fprintf(fp, "%d \n", w); /* Print mapwidth */

    printbangunan(TB, B, fp);  /* Print detail bangunan */

    printskill(a, fp); /* Print queue skill player 1 */
    printskill(b, fp); /* Print queue skill player 2 */

    fprintf(fp, "%d \n", x); /* Print counter shield player 1 */
    fprintf(fp, "%d \n", y); /* Print counter shield player 2 */

    printlistbangunan(m, TB, fp); /* Print list bangunan player 1 */
    printlistbangunan(n, TB, fp); /* Print list bangunan player 2 */

    fclose(fp);

    printf("Game berhasil disave! \n");
}
