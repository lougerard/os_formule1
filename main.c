#include <semaphore.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include "rand.h"
#include "essai.h"
#include "circuit.c"

#define NBVOITURE 20

void afficheLigne(struct Voiture voit, int a);


int main (int argc, char* argv[]){

	//srand(time(NULL)^getpid()<<20);
	int numeroVoitures[20] = {10,22,49,19,25,54,89,62,71,43,68,17,35,81,91,94,50,74,46,99};
	struct Circuit *circuit = malloc(sizeof(struct Circuit));
	struct Classement *classement = malloc(sizeof(struct Classement));
	circuit->secteur1Min = 10.0;
	circuit->secteur1Max = 20.0;
	circuit->secteur2Min = 25.0;
	circuit->secteur2Max = 35.0;
	circuit->secteur3Min = 35.0;
	circuit->secteur3Max = 40.0;
	key_t key=9876;
	const void *shmaddr = (const void *) 99999;
	int shmid, size;
	size = sizeof(struct Voiture) * NBVOITURE;
	shmid = shmget(9876, size, IPC_CREAT | 0666);
	struct shmid_ds *buf;
	pid_t pids[20];
	int i;
	for( i=0 ; i<20 ; i++ ){
		srand(time(NULL)^getpid()<<20);
		usleep(1000000);
		if((pids[i]=fork())<0){
			perror("fork");
		}
		else if(pids[i] == 0){
			//printf("shmid fils %i \n", shmid);
			//printf("shmat fils %i \n", shmat(shmid, 0, 0));
			//printf("%p \n", classement);
			classement = shmat(shmid, 0, 0);
			//printf("voiture numéro %d \n", classement->tabClass[i]->numVoiture);
			struct Voiture voitureCourante;
			voitureCourante.numVoiture = numeroVoitures[i];
			voitureCourante = voitRoule(classement->tabClass[i], circuit);
			shmctl(shmid, IPC_SET, buf);
			//shmdt(classement);
			//printf("%f", (classement->tabClass[i].tempsSecteur1));
			//int a = 1; 
                        //printf("voiture %d \n", classement->tabClass[a]->numVoiture);
                        //afficheLigne(voitureCourante, i);
                        exit(0);
		}
		//printf("%f \n", classement->tabClass[0]->tempsSecteur1);
		else if(pids[i] > 0){
			int shmidPere;
			shmidPere = shmget(key, size, 0666);
			//printf("shmid pere %i \n", shmidPere);
			//printf("shmat pere %i \n", shmat(shmidPere, 0, 0));
			classement = shmat(shmidPere, 0, 0);
			int a = 1;
			for(a=0 ; a<20 ; a++){ 
				//printf("voiture %d \n", classement->tabClass[a]->numVoiture);
				afficheLigne(classement->tabClass[a], a);
			}
			printf("\n");
			shmdt(classement);
		}
	}
	return 1;
}


void afficheLigne(struct Voiture voit, int a) {
	printf("||%i     |%i	|%f	|%f	|%f	|%f	|%i	|%i	||\n", a+1, voit.numVoiture, voit.tempsSecteur1, voit.tempsSecteur2, voit.tempsSecteur3, voit.tempsActuel, voit.nbrPitstop, voit.nbrTour);
}
