#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "rand.h"
#include "essai.h"
#include "circuit.c"

int main (int argc, char* argv[]){
 	srand(time(NULL));
	struct Circuit *circuit = malloc(sizeof(struct Circuit));
	circuit->secteur1Min = 30.0;
	circuit->secteur1Max = 40.0;
	circuit->secteur2Min = 25.0;
	circuit->secteur2Max = 35.0;
	circuit->secteur3Min = 35.0;
	circuit->secteur3Max = 40.0;
	struct Voiture* tabVoit[20];
	int j;
	for( j = 0 ; j<2 ; j++){
		struct Voiture *voit = malloc(sizeof (struct Voiture));
		voit->numVoiture=j;
		tabVoit[j] = voit;
	}
	pid_t pids[2];
	int n = 2;
	int i;
	for( i = 0 ; i<n ; i++){
		if((pids[i] = fork())<0){
			perror("fork error");
		}
		/*else {
			if(i!=0){
				printf("Voiture numero %d \n", tabVoit[i]->numVoiture);
				//voitRoule(tabVoit[i], circuit);
			}
		}*/
		printf("Voiture numero %d \n", tabVoit[i]->numVoiture);
	}
	return 1;
}
