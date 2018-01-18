#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "rand.h"
#include "essai.h"
#include "circuit.c"

int main (int argc, char* argv[]){

	//srand(time(NULL)^getpid()<<20);
	struct Circuit *circuit = malloc(sizeof(struct Circuit));
	circuit->secteur1Min = 10.0;
	circuit->secteur1Max = 20.0;
	circuit->secteur2Min = 25.0;
	circuit->secteur2Max = 35.0;
	circuit->secteur3Min = 35.0;
	circuit->secteur3Max = 40.0;
	struct Voiture* tabVoit[20];
	int j;
	for( j = 0 ; j<20 ; j++){
		struct Voiture *voit = malloc(sizeof (struct Voiture));
		voit->numVoiture=j+1;
		tabVoit[j] = voit;
	}
	pid_t pids[20];
	int i;
	for(i=0 ; i<21 ; i++){
		srand(time(NULL)^getpid()<<20);
		usleep(5000000);
		if((pids[i]=fork())<0){
			perror("fork");
		}
		else if(pids[i] == 0 && i<20){
			printf("voiture numéro %d \n", tabVoit[i]->numVoiture);
			voitRoule(tabVoit[i], circuit);
			exit(0);
		}
		else if(pids[i] > 0){
			printf("j'affiche \n");

		}
	}
	return 1;
}
