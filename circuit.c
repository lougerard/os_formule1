#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "essai.c"

void voitRoule(struct Voiture *voiture, struct Circuit circuit){

	int i;
	for(i=0 ; i<3 ; i++){
		voiture->tempsSecteur1 = tempsParSecteur(circuit.secteur1Min, circuit.secteur1Max);
		if(circuit.meilleurSecteur1 > voiture->tempsSecteur1){
			circuit.meilleurSecteur1 = voiture->tempsSecteur1;
		}
		voiture->tempsSecteur2 = tempsParSecteur(circuit.secteur2Min, circuit.secteur2Max);
		if(circuit.meilleurSecteur2 > voiture->tempsSecteur2){
			circuit.meilleurSecteur2 = voiture->tempsSecteur2;
		}
		voiture->tempsSecteur3 = tempsParSecteur(circuit.secteur3Min, circuit.secteur3Max);
		if(circuit.meilleurSecteur3 > voiture->tempsSecteur3){
			circuit.meilleurSecteur3 = voiture->tempsSecteur3;
		}
		printf("Tour : %d\n", i);
		printf("sec1 %d\n", voiture->tempsSecteur1);
		printf("sec2 %d\n", voiture->tempsSecteur2);
		printf("sec3 %d\n", voiture->tempsSecteur3);
		printf("\n");
	}
}
