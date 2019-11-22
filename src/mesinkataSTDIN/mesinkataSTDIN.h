/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#ifndef __MESINKATASDIN_H__
#define __MESINKATASDIN_H__

#include "../konfig/boolean.h"
#include "mesinkarSTDIN.h"

#define NMaxSTDIN 50
#define BLANKSTDIN ' '

typedef struct {
  char TabKata[NMaxSTDIN+1]; /* container penyimpan kata, indeks yang dipakai [1..NMax] */
    int Length;
} KataSTDIN;

/* State Mesin Kata */
extern boolean EndKataSTDIN;
extern KataSTDIN CKataSTDIN;

void IgnoreBlankSTDIN();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTKATASTDIN();
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATASTDIN();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinKataSTDIN();
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
void PrintKata(KataSTDIN kata);

boolean CompareKata(KataSTDIN kata, char* pembanding);

#endif