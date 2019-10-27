/* NIM / NAMA: 13518034 / Anindya Prameswari Ekaputri */
/* Hari / Tgl: Selasa, 1 Oktober 2019 */
/* Body untuk ADT mesintoken.h */

#include <stdio.h>
#include "mesintoken.h"	

/* KAMUS GLOBAL */
boolean EndToken;
Token CToken;

void IgnoreBlank() {
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */
	while ((CC == BLANK || CC == ENTER) && CC != MARK) {
		ADV();
	}
}

void STARTTOKEN() {
/* I.S. : CC sembarang
   F.S. : EndToken = true, dan CC = MARK;
          atau EndToken = false, CToken adalah Token yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir Token */
	START();
	IgnoreBlank();
	if (CC == MARK) {
		EndToken = true;
	}
	else {
		EndToken = false;
		SalinToken();
	}
}

void ADVTOKEN(){
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CToken adalah Token terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, maka EndToken = true
   Proses : Akuisisi kata menggunakan procedure SalinKata */
	IgnoreBlank();
	if (CC == MARK) {
		EndToken = true;
	}
	else {
		SalinToken();
		IgnoreBlank();
	}
}

void SalinToken() {
/* Mengakuisisi Token dan menyimpan hasilnya dalam CToken
   I.S. : CC adalah karakter pertama dari Token
   F.S. : CToken berisi Token yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
	/* KAMUS */
	int temp, numb, i;
	/* ALGORITMA */
	i = 1;
	temp = 0;
	while (CC != BLANK && CC != ENTER && CC != MARK && i <= NMax) {
		if (CC == 'T' || CC == 'V' || CC == 'C' || CC == 'F') {
			CToken.bgn = CC;
			CToken.val = -1;
			ADV();
			i++;
		}
		else {
			CToken.bgn = 'b';
				if (CC == '1')
					numb = 1;
				else if (CC == '2')
					numb = 2;
				else if (CC == '3')
					numb = 3;
				else if (CC == '4')
					numb = 4;
				else if (CC == '5')
					numb = 5;
				else if (CC == '6')
					numb = 6;
				else if (CC == '7')
					numb = 7;
				else if (CC == '8')
					numb = 8;
				else if (CC == '9')
					numb = 9;
				else if (CC == '0')
					numb = 0;
			temp = (temp * 10) + (numb);
			CToken.val = temp;
			ADV();
			i++;
		}
	}
}
