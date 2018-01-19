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
void trieTab(struct Classement *classement);
double meilleurS1(struct Voiture voiture[20]);
double meilleurS2(struct Voiture voiture[20]);
double meilleurS3(struct Voiture voiture[20]);
double meilleurTour(struct Voiture voiture[20]);

int main (int argc, char* argv[]){

	//srand(time(NULL))^getpid() <<20;
	int numeroVoitures[20] = {10,22,49,19,25,54,89,62,71,43,68,17,35,81,91,94,50,74,46,99};
	struct Circuit *circuit = malloc(sizeof(struct Circuit));
	struct Classement *classement = malloc(sizeof(struct Classement));
	circuit->secteur1Min = 10.0;
	circuit->secteur1Max = 20.0;
	circuit->secteur2Min = 25.0;
	circuit->secteur2Max = 35.0;
	circuit->secteur3Min = 35.0;
	circuit->secteur3Max = 40.0;
	double meilleurS1G = 999;
	double meilleurS2G = 999;
	double meilleurS3G = 999;
	double meilleurTG = 999;
	key_t key=9879;
	int shmid, size;
	struct shmid_ds *buf;
	size = sizeof(struct Voiture) * NBVOITURE;
	shmid = shmget(9879, size, IPC_CREAT | 0666);
	shmctl(shmid, IPC_RMID, buf);
	shmid = shmget(9879, size, IPC_CREAT | 0666);
	pid_t pids[20];
	int i;
	int k;
	struct Voiture voitureCourante;
	for( k=1; k < 41 ; k++) {
		for( i=0 ; i<21 ; i++ ){
		
		//srand(time(NULL)^getpid()<<20);
		srand(time(NULL) - i*2);
		if (k != 0) {
			usleep(100000);
		}
		if((pids[i]=fork())<0){
			perror("fork");
		}
		else if(pids[i] == 0){
		//printf("shmid fils %i \n", shmid);
		//printf("shmat fils %i \n", shmat(shmid, 0, 0));
		//printf("%p \n", classement);
		classement = shmat(shmid, 0, 0);
		//printf("voiture numéro %d \n", classement->tabClass[i]->numVoiture);
			if (k > 1) {
				voitureCourante = classement->tabClass[i];
			}
			if (k == 1) {
				voitureCourante.numVoiture = numeroVoitures[i];
				voitureCourante.nbrPitstop = 0;
			}
			voitureCourante.nbrTour = k - 1;
			classement->tabClass[i] = voitRoule(voitureCourante, circuit);
			//printf("%f \n", classement->tabClass[i]);
			//shmctl(shmid, IPC_SET, buf);
			//shmdt(classement);
			//printf("%f", (classement->tabClass[i].tempsSecteur1));
			//int a = 1; 
                        //printf("voiture %d \n", classement->tabClass[a]->numVoiture);
                        //afficheLigne(voitureCourante, i);
                        //afficheLigne(classement->tabClass[i],i);
                        exit(0);
		}
		//printf("%f \n", classement->tabClass[0]->tempsSecteur1);
		else if(pids[i] > 0 && i == 20){
			int shmidPere;
			shmidPere = shmget(key, size, 0666);
			//printf("shmid pere %i \n", shmidPere);
			//printf("shmat pere %i \n", shmat(shmidPere, 0, 0));
			classement = shmat(shmidPere, 0, 0);
			int a = 1;
			for(a=0 ; a<20 ; a++){ 
				//printf("voiture %d \n", classement->tabClass[a]->numVoiture);
				if (a==0) {
					printf("||place	|num	|T_s1		|T_s2		|T_s3		|T_tour		|T_actuel	|nbrPit		|nbrTour||\n");
					printf("-------------------------------------------------------------------------------------------------------------------------\n");
				}
				trieTab(classement);					
				afficheLigne(classement->tabClass[a], a);
			}
			double meilleurSecteur1 = meilleurS1(classement->tabClass);
			if(meilleurS1G > meilleurSecteur1){
				meilleurS1G = meilleurSecteur1;
			}
			double meilleurSecteur2 = meilleurS2(classement->tabClass);
			if(meilleurS2G > meilleurSecteur2){
				meilleurS2G = meilleurSecteur2;
			}
			double meilleurSecteur3 = meilleurS3(classement->tabClass);
			if(meilleurS3G > meilleurSecteur3){
                                meilleurS3G = meilleurSecteur3;
                        }
			double meilleurT = meilleurTour(classement->tabClass);
			if(meilleurTG > meilleurT){
                                meilleurTG = meilleurT;
                        }
			//printf("%f \n", meilleurSecteur1);
			struct timeConvert *time = malloc(sizeof(struct timeConvert));
        		tConvert(time,(classement->tabClass[0]).tempsActuel);
        		int min = time->min;
        		int sec = time->tSec;
        		int milli = time->tMilliSec;
        		printf("\n||%i	|%i	|%f	|%f	|%f	|%f	|%i:%i:%i  	|%i		|%i	||\n", 0, 0, meilleurSecteur1, meilleurSecteur2, meilleurSecteur3, meilleurT, min, sec, milli, 0, 0);
			printf("\n||%i	|%i	|%f	|%f	|%f	|%f	|%i:%i:%i	|%i		|%i	||\n", 0, 0, meilleurS1G, meilleurS2G, meilleurS3G, meilleurTG, min, sec, milli, 0, 0);

			printf("\n");
			shmdt(classement);
		}
	}
	}
	//struct timeConvert *time = malloc(sizeof(struct timeConvert));
        //tConvert(time,(classement->tabClass[0]).tempsActuel);
        //int min = time->min;
        //int sec = time->tSec;
        //int milli = time->tMilliSec;

	//printf("||%i     |%i    |%f     |%f     |%f     |%f     |%i:%i:%i       |%i             |%i     ||\n", 0, 0, circuit->meilleurSecteur1, circuit->meilleurSecteur2, circuit->meilleurSecteur3, circuit->meilleurTour, min, sec, milli, 0, 0);
	
	shmdt(classement);
	return 1;
}

void afficheLigne(struct Voiture voit, int a) {
	struct timeConvert *time = malloc(sizeof(struct timeConvert));
	tConvert(time, voit.tempsActuel);
	int min = time->min;
	int sec = time->tSec;
	int milli = time->tMilliSec;
	double tps = voit.tempsSecteur1 + voit.tempsSecteur2 + voit.tempsSecteur3;
	printf("||%i     |%i	|%f	|%f	|%f	|%f	|%i:%i:%i	|%i		|%i	||\n", a+1, voit.numVoiture, voit.tempsSecteur1, voit.tempsSecteur2, voit.tempsSecteur3, tps, min, sec, milli, voit.nbrPitstop, voit.nbrTour);
	//printf("||%i     |%i    |%f     |%f     |%f     |%f     |%i     |%i     ||\n", a+1, voit.numVoiture, voit.tempsSecteur1, voit.tempsSecteur2, voit.tempsSecteur3, voit.tempsActuel, voit.nbrPitstop, voit.nbrTour);
}
       
void trieTab(struct Classement *class) {
	struct Voiture v;
	int m;
	int k;
	int count = 0;
	for (m=0; m<20 ; m++) {
		for (k=0 ; k<20; k++) {
			if (k != m && (class->tabClass[m]).tempsActuel < (class->tabClass[k]).tempsActuel) {
				v = class->tabClass[m];
				class->tabClass[m] = class->tabClass[k];
				class->tabClass[k] = v;
				count ++;
			}
		}	
	}
	

}

double meilleurS1(struct Voiture voiture[20]){
	double meilleurTemps = 999;
	int i;
	for(i=0 ; i<20 ; i++){
		if(meilleurTemps > voiture[i].tempsSecteur1){
			meilleurTemps = voiture[i].tempsSecteur1;
		}
	}
	return meilleurTemps;
}

double meilleurS2(struct Voiture voiture[20]){
        double meilleurTemps = 999;
        int i;
        for(i=0 ; i<20 ; i++){
                if(meilleurTemps > voiture[i].tempsSecteur2){
                        meilleurTemps = voiture[i].tempsSecteur2;
                }
        }
        return meilleurTemps;
}

double meilleurS3(struct Voiture voiture[20]){
        double meilleurTemps = 999;
        int i;
        for(i=0 ; i<20 ; i++){
                if(meilleurTemps > voiture[i].tempsSecteur3){
                        meilleurTemps = voiture[i].tempsSecteur3;
                }
        }
        return meilleurTemps;
}

double meilleurTour(struct Voiture voiture[20]){
        double meilleurTemps = 999;
        int i;
        for(i=0 ; i<20 ; i++){
                if(meilleurTemps > voiture[i].tempsSecteur1 + voiture[i].tempsSecteur2 + voiture[i].tempsSecteur3){
                        meilleurTemps = voiture[i].tempsSecteur1 + voiture[i].tempsSecteur2 + voiture[i].tempsSecteur3;
                }
        }
        return meilleurTemps;
}
