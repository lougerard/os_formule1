#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "rand.c"
#include "essai.c"

int main (int argc, char* argv[]){
	struct Circuit circuit;
	circuit.secteur1Min = 30.0;
	circuit.secteur1Max = 40.0;
	circuit.secteur2Min = 25.0;
	circuit.secteur2Max = 35.0;
	circuit.secteur3Min = 35.0;
	circuit.secteur3Max = 40.0;
	struct Voiture tabVoit[20];
	struct Voiture *voit1 = malloc(sizeof(struct Voiture));
	voitRoule(voit1, circuit);
	//tabVoit[0] = voit1;
}

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
