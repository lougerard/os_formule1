#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "essai.c"

struct Voiture voitRoule(struct Voiture voiture, struct Circuit *circuit){

	int i;
	//int status = 500000;
	for(i=1 ; i<11 ; i++){
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
		voiture.tempsActuel = voiture.tempsActuel + voiture.tempsSecteur3;
		if(circuit->meilleurSecteur3 > voiture.tempsSecteur3){
			circuit->meilleurSecteur3 = voiture.tempsSecteur3;
		}
		//printf("sec3 %f\n", voiture->tempsSecteur3);
		//usleep(300000);
		voiture.nbrTour = voiture.nbrTour + 1;	
	}
	return voiture;
}
