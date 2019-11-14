/* File : listlinier.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* infotype adalah integer */


#include "multilist.h"
#include <stdio.h>
#include <stdlib.h>


/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyMultilist(Multilist L){
	return (L.First==NULL);
}
/* Mengirim true jika list kosong */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyMultilist (Multilist *L){
	(*L).First = NULL;
}
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */

/****************** Manajemen Memori ******************/
addressNode AlokasiNode(int X){
	addressNode P;
	P = (addressNode) malloc (sizeof (ElmtNode));
    if (P != NULL) {
      (P)->info = X;
      (P)->next = NULL;
      (P)->firstAdj = NULL;
      return P;
    } else {
      return NULL;
    }
}

addressAdj AlokasiAdj(int X){
	addressAdj P;
	P = (addressAdj) malloc (sizeof (ElmtAdj));
    if (P != NULL) {
      (P)->info = X;
      (P)->nextAdj = NULL;
      return P;
    } else {
      return NULL;
    }
}

void DealokasiNode(addressNode* P){
	free(*P);
}

void DealokasiAdj(addressAdj* P){
	free(*P);
}

addressNode searchNode(Multilist L, int X){
	if (IsEmptyMultilist(L)) return NULL;
	addressNode P = L.First;
	boolean isFound = false;
	while((P != NULL)){
		if (P->info == X) return P;
		else P = (P)->next;
	}
	return NULL;
}

void InsertPair(Multilist *L, int X, int Y){
	if (IsEmptyMultilist(*L)){
		addressNode aNode = AlokasiNode(X);
		aNode->firstAdj = AlokasiAdj(Y);
		(*L).First = aNode;
	}
	else{
		addressNode aNode = searchNode(*L,X);

		if (aNode==NULL){
			aNode = AlokasiNode(X);
			aNode->firstAdj = AlokasiAdj(Y);
			aNode->info = X;
			addressNode P = (*L).First;
			while(((P)->next!=NULL)){
				P = P->next;
			}
			P->next = aNode;
		}
		else{
			addressAdj aAdj = aNode->firstAdj;
			while((aAdj->nextAdj != NULL)){
				aAdj = aAdj -> nextAdj;
			}
			aAdj -> nextAdj = AlokasiAdj(Y);
		}
	}
}

boolean IsConnectedDirect(Multilist L, int X, int Y){
	addressNode aNode = searchNode(L,X);
	if (aNode==NULL){
		return false;
	}
	else{
		addressAdj aAdj = aNode -> firstAdj;
		while(aAdj!=NULL){
			if (aAdj->info == Y) return true;
			aAdj = aAdj -> nextAdj;
		}
	}
	return false;
}


void FindAllAdj(Multilist L, int node, int **arrResult, int *sizeArr){
	addressNode aNode = searchNode(L,node);
	if (aNode==NULL){
		*sizeArr = 0;
	}
	else{
		addressAdj aAdj = aNode->firstAdj;
		//printf("%d ", aAdj);
		int i = 1;
		while(aAdj!=NULL){
			(*arrResult)[i] = aAdj -> info;
			aAdj = aAdj -> nextAdj;
			
			i+=1;
			
		}
		*sizeArr = i-1;
		
	}
}


