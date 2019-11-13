/* File : listlinier.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* infotype adalah integer */

#ifndef multilistlinier_H
#define multilistlinier_H

#include "boolean.h"


typedef struct tElmtNode *addressNode;
typedef struct tElmtAdj *addressAdj;
typedef struct tElmtNode {
	int info;
	addressNode next;
	addressAdj firstAdj;
} ElmtNode;

typedef struct tElmtAdj {
	int info;
	addressAdj nextAdj;
} ElmtAdj;

typedef struct {
	addressNode First;
} Multilist;


/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyMultilist(Multilist L);
/* Mengirim true jika list kosong */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyMultilist (Multilist *L);


/****************** Manajemen Memori ******************/
addressNode AlokasiNode(int X);

addressAdj AlokasiAdj(int X );

void DealokasiNode(addressNode* P);

void DealokasiAdj(addressAdj* P);

void InsertPair(Multilist *L, int X, int Y);

boolean IsConnectedDirect(Multilist L, int X, int Y);

#endif