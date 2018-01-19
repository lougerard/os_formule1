#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "essai.c"

int pitstop();

struct Voiture voitRoule(struct Voiture voiture, struct Circuit *circuit){

	
	voiture.pitstop = 0;
	//int status = 500000;
		//printf("Tour : %d\n", i);
		voiture.tempsSecteur1 = tempsParSecteur(circuit->secteur1Min, circuit->secteur1Max);
		voiture.tempsActuel = voiture.tempsActuel + voiture.tempsSecteur1;
		if(circuit->meilleurSecteur1 > voiture.tempsSecteur1){
			circuit->meilleurSecteur1 = voiture.tempsSecteur1;
		}
		//printf("sec1 %f\n", voiture.tempsSecteur1);
		//usleep(300000);
		voiture.tempsSecteur2 = tempsParSecteur(circuit->secteur2Min, circuit->secteur2Max);
		voiture.tempsActuel = voiture.tempsActuel + voiture.tempsSecteur2;
		if(circuit->meilleurSecteur2 > voiture.tempsSecteur2){
			circuit->meilleurSecteur2 = voiture.tempsSecteur2;
		}
		//printf("sec2 %f\n", voiture->tempsSecteur2);
		//usleep(300000);
		voiture.tempsSecteur3 = tempsParSecteur(circuit->secteur3Min, circuit->secteur3Max);
		int pit =  0 ;
		pit = pitstop();
                if(pit == 1){
                        voiture.nbrPitstop = voiture.nbrPitstop + 1;
                        voiture.tempsSecteur3 = voiture.tempsSecteur3 + (ourRandom(5.0)+5.0);
			voiture.pitstop = 1;
                }
		if (voiture.nbrTour == 4 && voiture.nbrPitstop < 1 && pit != 1) {
			voiture.nbrPitstop = voiture.nbrPitstop + 1;
                        voiture.tempsSecteur3 = voiture.tempsSecteur3 + (ourRandom(5.0)+5.0);
                        voiture.pitstop = 1;
		}
		if (voiture.nbrTour == 8 && voiture.nbrPitstop < 2 && pit != 1) {
                        voiture.nbrPitstop = voiture.nbrPitstop + 1;
                        voiture.tempsSecteur3 = voiture.tempsSecteur3 + (ourRandom(5.0)+5.0);
                        voiture.pitstop = 1;
                }

		voiture.tempsActuel = voiture.tempsActuel + voiture.tempsSecteur3;
		if(circuit->meilleurSecteur3 > voiture.tempsSecteur3){
			circuit->meilleurSecteur3 = voiture.tempsSecteur3;
		}
		double mTps = voiture.tempsSecteur1 + voiture.tempsSecteur2 + voiture.tempsSecteur3;
		if (mTps < circuit-> meilleurTour) {
			circuit->meilleurTour = mTps;
		}
		//printf("sec3 %f\n", voiture->tempsSecteur3);
		//usleep(300000);
		voiture.nbrTour = voiture.nbrTour + 1;	
	
	return voiture;
}

int pitstop(){
	double rand = ourRandom(14.0);
	if(rand>=5.0 && rand<=7.0){
		return 1;
	}
	return 0;
}
