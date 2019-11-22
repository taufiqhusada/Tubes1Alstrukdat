/* File: mesinkar.h */
/* Definisi Mesin Karakter */

#ifndef __MESIN_KARSTDIN_H_
#define __MESIN_KARSTDIN_H_

#include "../konfig/boolean.h"

#define MARKSTDIN '\n'
/* State Mesin */
extern char CCSTDIN;
extern boolean EOPSTDIN;

void STARTSTDIN();
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita
          Jika CC != MARK maka EOP akan padam (false)
          Jika CC = MARK maka EOP akan menyala (true) */

void ADVSTDIN();
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = MARK
          Jika  CC = MARK maka EOP akan menyala (true) */

void FINISH();

#endif