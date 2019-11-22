#ifndef __PERMAINAN_H__
#define __PERMAINAN_H__

#include"../skill/skill.h"
#include"../bangunan/list_bangunan.h"
#include"../skill/queue.h"
#include"../stackUndo/stackToken.h"

typedef struct 
{
    Queue qSkillPlayer;
    Stack stackPlayer;  // untuk undo
    List listBangunan;
    int turn;
}Player;

#define qSkillPlayer(P) (P).qSkillPlayer
#define stackPlayer(P) (P).stackPlayer
#define listBangunan(P) (P).listBangunan


void Init(Player *P);
// prosedur untuk menginisialisasi queue of skill

void printSkill(Player P);
// print list skill yg available oleh player tertentu

void printBangunan(Player P, TBangunan TB);
// print list bangunan oleh player tertentu

//void printAllState(Player P);
// 

void Undo(Stack *S);
// metode undo memanfaatkan stack



#endif
