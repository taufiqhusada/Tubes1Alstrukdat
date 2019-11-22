#include <stdio.h>
#include "mesinkarSTDIN.h"
#include "mesinkataSTDIN.h"

/* State Mesin Kata */
boolean EndKataSTDIN;
KataSTDIN CKataSTDIN;

void IgnoreBlankSTDIN(){
  while((CCSTDIN==BLANKSTDIN) && (CCSTDIN!=MARKSTDIN)) ADVSTDIN();
}
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTKATASTDIN(){
  STARTSTDIN();
  IgnoreBlankSTDIN();
  if (CCSTDIN == MARKSTDIN) 
    EndKataSTDIN = true;
  else 
   {/* CC != MARK */
    EndKataSTDIN = false;
    SalinKataSTDIN();
   }
}
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATASTDIN(){
  IgnoreBlankSTDIN();
  if (CCSTDIN == MARKSTDIN) 
    EndKataSTDIN = true;
  else 
   {/* CC != MARK */
    EndKataSTDIN = false;
    SalinKataSTDIN();
    IgnoreBlankSTDIN();
   }
}
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinKataSTDIN(){
  boolean isRun =  true;
  int i = 1;
  while(isRun){
    CKataSTDIN.TabKata[i] = CCSTDIN;
    ADVSTDIN();
    if ((CCSTDIN == MARKSTDIN) || (CCSTDIN == BLANKSTDIN) || i>=NMaxSTDIN) isRun = false;
    else i++;
  }
  CKataSTDIN.Length = i;
}
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

void PrintKata(KataSTDIN kata){
  int i;
  for (i = 1; i<=kata.Length; ++i){
    printf("%c",kata.TabKata[i]);
  }
  printf("\n");
}


boolean CompareKata(KataSTDIN kata, char* pembanding){
  KataSTDIN Kpembanding;
  int i = 0;
  boolean isOk = true;
  while(isOk){
    if (!((pembanding[i]>='a' && pembanding[i]<='z')||(pembanding[i]>='0' && pembanding[i]<='9')||(pembanding[i]>='A' && pembanding[i]<='Z')))  isOk = false;
    else{
      Kpembanding.TabKata[i+1] = pembanding[i];
      i++;
    }
  }
  Kpembanding.Length = i;
  //PrintKata(Kpembanding);
  
  if (kata.Length != Kpembanding.Length){
    return false;
  }
  for (i = 1; i<=kata.Length; ++i){
    if (Kpembanding.TabKata[i]!=kata.TabKata[i]) {
      return false;
    }
  }
  return true;
}

