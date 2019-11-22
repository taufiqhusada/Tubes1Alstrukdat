// Update 28 Oktober 2019
// Header untuk Skill (ADT Queue)

#ifndef _SKILL_
#define _SKILL_

#include <stdio.h>
#include <stdlib.h>
#include "../bangunan/bangunan.h"
#include "queue.h"

/*define + struct dipindahin ke queue.h */



#define HeadSklID(Q) (Q).T[(Q).HEAD].skillID
#define SkillID(X) (X).skillID

// List Skill akan bertipe Queue

void addSkill (Queue *Q, infotypeQueue X);
/* I.S. X adalah skill dan Q terdefisini */
/* F.S. X dimasukkan kedalam Queue dan TailQueue(Q) = X */

void InstantUpgrade(Queue *Q, int Owner, TBangunan *T); // Skill ID = 1
/* I.S. Pemain memiliki bangunan */
/* F.S. Seluruh bangunan yang dimiliki pemain akan naik 1 level  */

void ExtraTurn(Queue *Q); // Skill ID = 2
/* I.S. Turn berakhir dengan Pemain X telah menggunakan Skill ExtraTurn */
/* F.S. Turn Selanjutnya dilanjutkan oleh Pemain X */

void InstantReinforcement(Queue *Q); // Skill ID = 3
/* I.S. Semua bangunan milik pemain sudah menjadi level 4 */
/* F.S. Semua bangunan mendapatkan tambahan 5 pasukan */

void Barrage(Queue *Q, int Owner, TBangunan *T); // Skill ID = 4
/* I.S. Bangunan Pemain baru saja menjadi 10 bangunan */
/* F.S. Jumlah pasukan pada seluruh bangunan musuh akan berkurang sebanyak 10 */

void Shield(Queue *Q); // Skill ID = 5
/* I.S. Pemain mendapatkan skill jika setelah sebuah lawan menyerang, bangunan pemain
berkurang 1 menjadi sisa 2 */
/* F.S. Seluruh bangunan yang dimiliki oleh pemain akan memiliki pertahanan selama
2 turn LAWAN. Jika skill digunakan 2 kali berturut-turut, durasi tidak akan bertambah,
namun menjadi nilai maksimum */

void AttackUp(Queue *Q); // Skill ID = 6
/* I.S. Pemain mendapatkan skill ini jika pemain baru saja menyerang tower lawan dan
jumlah towernya menjadi 3 */
/* F.S. Jika Pemain menyerang lawan, Pertahanan lawan termasuk shield tidak 
akan mempengaruhi penyerangan */

void CriticalHit(Queue *Q); // Skill ID = 7
/* I.S. Pemain mendapatkan skill ini jika lawan baru saja mengaktifkan Extra Turn */
/* F.S. Untuk 1 serangan Pemain setelah skill ini diaktifkan, Jumlah pasukan pada
bangunan yang melakukan serangan menjadi 2 kali lipat pasukan.
Skill ini menon-aktifkan pertahanan dan shield lawan*/

void PrintSkillList(Queue Q);
/* I.S. Queue Skill terdefinisi */
/* F.S. Print List Skill */

#endif

