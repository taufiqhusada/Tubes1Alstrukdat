#ifndef _Save_
#define _Save_

#include <stdio.h>
#include <stdlib.h>
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



void printbangunan (TBangunan TB, int x);
/* I.S. array TB terdefinisi */
/* F.S. print array TB ke file */

void printskill(Queue Q);
/* I.S. Queue skill terdefinisi */
/* F.S. print queue skill ke file */ 

void printlistbangunan(Player P, TBangunan TB);
/* I.S. list bangunan yang dimiliki player terdefinisi */
/* F.S. print list bangunan skill ke file */ 

void save (int B, int h, int w, TBangunan TB, Queue a, Queue b, int x, int y, Player m, Player n);
/* I.S. jumlah bangunan, tinggi peta, lebar peta, array bangunan (TB), queue skill pemain 1 dan 2, 
counter shield pemain 1 dan 2, dan list bangunan yang dimiliki player 1 dan 2 terdefinisi */
/* F.S. print jumlah bangunan, tinggi peta, lebar peta, array bangunan (TB), queue skill pemain 1 dan 2, 
counter shield pemain 1 dan 2, dan list bangunan yang dimiliki player 1 dan 2 ke file */ 

#endif