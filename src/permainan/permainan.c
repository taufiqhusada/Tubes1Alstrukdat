#include "permainan.h"
#include "../skill/queue.h"
#include "../bangunan/list_bangunan.h"


void Init(Player *P){
    CreateEmptyQueue(&(*P).qSkillPlayer,10);
    //AddQueue(&(*P).qSkillPlayer, "IU");
    CreateEmptyList(&(*P).listBangunan);
}

void printBangunan(Player P){
    PrintInfo(P.listBangunan);
}

void printSkill(Player P){
    printf("%s", InfoHeadQueue(P.qSkillPlayer));
}

void printAllState(Player P){
    printBangunan(P);
    printSkill(P);
}
