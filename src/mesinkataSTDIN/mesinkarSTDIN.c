/* File: mesinkar.c */
/* Implementasi Mesin Karakter */

#include "mesinkarSTDIN.h"
#include <stdio.h>

char CCSTDIN;
boolean EOPSTDIN;

static FILE * pitaSTDIN;
static int retvalSTDIN;

void STARTSTDIN() {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita. Jika CC != MARK maka EOP akan padam (false).
          Jika CC = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    pitaSTDIN = stdin;
    ADVSTDIN();
}

void ADVSTDIN() {
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela =
          CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = MARK.
          Jika  CC = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    retvalSTDIN = fscanf(pitaSTDIN,"%c",&CCSTDIN);
    EOPSTDIN = (CCSTDIN == MARKSTDIN);
   
}

void FINISH(){
       fclose(pitaSTDIN);
    
}