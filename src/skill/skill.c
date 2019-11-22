// Update 28 Oktober 2019
// Implementasi Skill

#include <stdio.h>
#include "queue.h"
#include "skill.h"
#include "../bangunan/bangunan.h"

void addSkill(Queue *Q, int skillID) {
	/* I.S. X adalah skill dan Q terdefisini */
	/* F.S. X dimasukkan kedalam Queue dan TailQueue(Q) = X */
	SKILL X;
	int queueLen;

	SkillID(X) = skillID;

	queueLen = NBElmtQueue(*Q);

	if (queueLen <= 10) {
		AddQueue(Q, X);
	}
	else {
		// Queue Skill Penuh
	}
}

void InstantUpgrade(Queue *Q, int Owner, TBangunan *T) { // Skill Code = IU
/* I.S. Pemain memiliki bangunan */
/* F.S. Seluruh bangunan yang dimiliki pemain akan naik 1 level  */
    SKILL SklOut;
    int i;

    Del(Q, &SklOut);
    if (Owner == 1) { // Owner Pemain 1
        for (i = 1; i <= 30; i++) { // Iterasi Cek semua bangunan
            if (owner(Bgn(*T, i)) == 1) {
               
                if (level(Bgn(*T, i)) != 4) {
                    level(Bgn(*T, i)) += 1;
                } 

            }


        }
    } // End of if

    else { // Owner Pemain 2

        for (i = 1; i <= 30; i++) { // Iterasi Cek Semua bangunan
            if (owner(Bgn(*T, i)) == 1) {
               
                if (level(Bgn(*T, i)) != 4) {
                    level(Bgn(*T, i)) += 1;
                } 

            }
        }

    } // End of Else

}


void ExtraTurn(Queue *Q, boolean *IsExtraTurn) { // Skill Code = ET
/* I.S. Turn berakhir dengan Pemain X telah menggunakan Skill ExtraTurn */
/* F.S. Turn Selanjutnya dilanjutkan oleh Pemain X */
    *IsExtraTurn = true;

}

void InstantReinforcement(Queue *Q, int Owner, TBangunan *T) { // Skill Code = IR
/* I.S. Semua bangunan milik pemain sudah menjadi level 4 */
/* F.S. Semua bangunan mendapatkan tambahan 5 pasukan */
    SKILL SklOut;
    int i, newArmy;

    Del(Q, SklOut);

    if (Owner == 1) { // Owner Pemain 1
        for (i = 1; i <= 30; i++) { // Iterasi Cek semua bangunan
            if (owner(Bgn(*T, i)) == 1) {
               
                if (level(Bgn(*T, i)) == 4) {
                    // +5 Army Here
                    newArmy = nbPas(Bgn(*T,i)) + 5;

                    if (newArmy > M(Bgn(*T,i))) {
                        nbPas(Bgn(*T,i)) = M(Bgn(*T,i));
                    }
                    else {
                        nbPas(Bgn(*T,i)) = newArmy;
                    }

                } 

            }


        }
    } // End of if

    else { // Owner Pemain 2

        for (i = 1; i <= 30; i++) { // Iterasi Cek Semua bangunan
            if (owner(Bgn(*T, i)) == 1) {
               
                if (level(Bgn(*T, i)) != 4) {
                    // +5 Army Here
                    newArmy = nbPas(Bgn(*T,i)) + 5;

                    if (newArmy > M(Bgn(*T,i))) {
                        nbPas(Bgn(*T,i)) = M(Bgn(*T,i));
                    }
                    else {
                        nbPas(Bgn(*T,i)) = newArmy;
                    }

                } 

            }
        }

    } // End of Else



}

void Barrage(Queue *Q, int Owner, TBangunan *T) { // Skill Code = B
/* I.S. Bangunan Pemain baru saja menjadi 10 bangunan */
/* F.S. Jumlah pasukan pada seluruh bangunan musuh akan berkurang sebanyak 10 */
    SKILL SklOut;
    int i, newArmy;
    int Lawan;

    Del(Q, SklOut);

    if (Owner == 1) { // Owner Pemain 1
        Lawan = 2;
        for (i = 1; i <= 30; i++) { // Iterasi Cek semua bangunan
            if (owner(Bgn(*T, i)) == Lawan) {
               // Remove 10 Army from Lawan
                newArmy = nbPas(Bgn(*T,i)) - 10;

                if (newArmy < 0) {
                    nbPas(Bgn(*T,i)) = newArmy;
                }
                else {
                    nbPas(Bgn(*T,i)) = 0;
                }


            }


        }
    } // End of if

    else { // Owner Pemain 2
        Lawan = 1;
        for (i = 1; i <= 30; i++) { // Iterasi Cek Semua bangunan
            if (owner(Bgn(*T, i)) == Lawan) {
               // Remove 10 Army from lawan 
                newArmy = nbPas(Bgn(*T,i)) - 10;

                if (newArmy < 0) {
                    nbPas(Bgn(*T,i)) = newArmy;
                }
                else {
                    nbPas(Bgn(*T,i)) = 0;
                }

            }
        }

    } // End of Else

    
}

// BONUS

void Shield(Queue *Q); // Skill Code = S
/* I.S. Pemain mendapatkan skill jika setelah sebuah lawan menyerang, bangunan pemain
berkurang 1 menjadi sisa 2 */
/* F.S. Seluruh bangunan yang dimiliki oleh pemain akan memiliki pertahanan selama
2 turn LAWAN. Jika skill digunakan 2 kali berturut-turut, durasi tidak akan bertambah,
namun menjadi nilai maksimum */

void AttackUp(Queue *Q); // Skill Code = AU
/* I.S. Pemain mendapatkan skill ini jika pemain baru saja menyerang tower lawan dan
jumlah towernya menjadi 3 */
/* F.S. Jika Pemain menyerang lawan, Pertahanan lawan termasuk shield tidak 
akan mempengaruhi penyerangan */

void CriticalHit(Queue *Q); // Skill Code = CH
/* I.S. Pemain mendapatkan skill ini jika lawan baru saja mengaktifkan Extra Turn */
/* F.S. Untuk 1 serangan Pemain setelah skill ini diaktifkan, Jumlah pasukan pada
bangunan yang melakukan serangan menjadi 2 kali lipat pasukan.
Skill ini menon-aktifkan pertahanan dan shield lawan*/