#ifndef __PERMAINAN_H__
#define __PERMAINAN_H__

#include"../skill/skill.h"
#include"../bangunan/listlinier.h"

typedef struct 
{
    Queue qSkillPlayer;
    Stack stackPlayer;  // untuk undo
    LBangunant listBangunan;
}Player;

#define qSkillPlayer(P) (P).qSkillPlayer
#define stackPlayer(P) (P).stackPlayer
#define listBangunan(P) (P).LBangunant


void InitSkill(Queue *Q);
// prosedur untuk menginisialisasi queue of skill

void printSkill(Queue *Q);
// print list skill yg available oleh player tertentu

void printBangunan(Queue *Q);
// print list bangunan oleh player tertentu

void Undo(Queue *Q);
// metode undo memanfaatkan stack



#endif
