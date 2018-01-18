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
#include <string.h>
#include "rand.h"
#include "essai.h"
#include "circuit.c"

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
	int j;
	for( j=0 ; j<20 ; j++ ){
		struct Voiture *voit = malloc(sizeof (struct Voiture));
		voit->numVoiture = numeroVoitures[j];
		classement->tabClass[j] = voit;
		classement->position[j] = j+1;
	}
	int fd;
	fd = shm_open("/MyMemory", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	void* sharedMemory = mmap(NULL, sizeof(struct Classement), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(sharedMemory == MAP_FAILED){
		printf("erreur map");
	} 
	pid_t pids[20];
	int i;
	for( i=0 ; i<21 ; i++ ){
		srand(time(NULL)^getpid()<<20);
		usleep(5000000);
		if((pids[i]=fork())<0){
			perror("fork");
		}
		else if(pids[i] == 0 && i<20){
			//printf("voiture numéro %d \n", classement->tabClass[i]->numVoiture);
			int fdFils = shm_open("/MyMemory", O_RDWR, S_IRUSR | S_IWUSR);
			voitRoule(classement->tabClass[i], circuit);
			close(fdFils);
			exit(0);
		}
		else if(pids[i] > 0){
			int fdPere = shm_open("/MyMemory", O_RDWR, S_IRUSR);
			int a;
			for(a=0 ; a<20 ; a++){ 
				printf("voiture %d \n", classement->tabClass[a]->numVoiture);
			}
			close(fdPere);
		}
	}
	return 1;
}
