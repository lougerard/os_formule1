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
#include "Qualification1.c"

#define NBVOITURE 20

void afficheLigne(struct Voiture voit, int a);
void trieTab(struct Classement *classement);
void printFichier(int num, struct Classement *class, int vS1G, int vS2G, int vS3G, int vTG, double meilleurS1G, double meilleurS2G, double meilleurS3G, double meilleurTG);
void afficheLigneE(struct Voiture voit, int a, FILE* fichier);
struct Voiture meilleurS1(struct Voiture voiture[20]);
struct Voiture meilleurS2(struct Voiture voiture[20]);
struct Voiture meilleurS3(struct Voiture voiture[20]);
struct Voiture meilleurTour(struct Voiture voiture[20]);
void aband(struct Classement *class, int nb);
void depart(struct Classement *classement, char text[]);

int main (int argc, char* argv[]){
	//qualification(20);
	int nbrTours = atoi(argv[1]);
	int numeroVoitures[20] = {44,77,3,33,5,7,11,31,19,18,14,2,10,55,8,20,27,30,9,94};
	struct Circuit *circuit = malloc(sizeof(struct Circuit));
	struct Classement *classement = malloc(sizeof(struct Classement));
	circuit->secteur1Min = 10.0;
	circuit->secteur1Max = 20.0;
	circuit->secteur2Min = 25.0;
	circuit->secteur2Max = 35.0;
	circuit->secteur3Min = 35.0;
	circuit->secteur3Max = 40.0;
	double meilleurS1G = 999;
	int vS1G = 0;
	double meilleurS2G = 999;
	int vS2G = 0;
	double meilleurS3G = 999;
	int vS3G = 0;
	double meilleurTG = 999;
	int vTG = 0;
	key_t key=9879;
	int shmid, size;
	struct shmid_ds *buf;
	size = sizeof(struct Voiture) * NBVOITURE;
	shmid = shmget(9879, size, IPC_CREAT | 0666);
	shmctl(shmid, IPC_RMID, buf);
	shmid = shmget(9879, size, IPC_CREAT | 0666);
	classement = shmat(shmid, 0, 0);
	qualification1(classement, circuit);
	usleep(1000000);
	char text[] = "Depart de Qualification 2";
	depart(classement, text);
	usleep(1000000);
	qualification2(classement, circuit);
	usleep(1000000);
	char text2[] = "Depart de Qualification 3";
	depart(classement, text2);
	usleep(1000000);
	qualification3(classement, circuit);
	usleep(1000000);
	char text3[] = "Depart du Grand Prix de F1";
	depart(classement, text3);
	usleep(1000000);
	pid_t pids[20];
	int i;
	int k;
	sem_t *sem;
	int nbVoit = 20;
	struct Voiture voitureCourante;
	sem = sem_open("semP", O_CREAT | O_EXCL, 0644, 1);
	for( k=1; k <= nbrTours ; k++) {
		for( i=0 ; i<21 ; i++ ){
			srand(time(NULL) - i*20);
			if (k != 0) {
				usleep(100000);
			}
			if((pids[i]=fork())<0){
				perror("fork");
			}
			else if(pids[i] == 0){
				classement = shmat(shmid, 0, 0);
				sem_wait(sem);
				voitureCourante = classement->tabClass[i];
				if (k == 1) {
					voitureCourante.nbrPitstop = 0;
					voitureCourante.tempsActuel = 0;
					voitureCourante.abandon = 0;
				}	
				if(voitureCourante.abandon == 0){
					voitureCourante.nbrTour = k - 1;
					classement->tabClass[i] = voitRoule(voitureCourante, circuit, nbrTours);
					if (classement->tabClass[i].abandon == 1) {nbVoit --;}
				}
				sem_post(sem);
                        	exit(0);
			}
			else if(pids[i] > 0 && i == 20){
				int shmidPere;
				shmidPere = shmget(key, size, 0666);
				classement = shmat(shmidPere, 0, 0);
				int a = 1;
				sem_wait(sem);
				for(a=0 ; a<20 ; a++){ 
					if (a==0) {
						printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                                		printf("||                                                              GRAND PRIX DE FORMULE 1                                                         ||\n");
						printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
						printf("||place	|num	|T_s1		|T_s2		|T_s3		|T_tour		|T_actuel	|nbrPit		|nbrTour	|abandon	||\n");
						printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
					}
					trieTab(classement);
					aband(classement, nbVoit);					
					afficheLigne(classement->tabClass[a], a);
				}
				struct Voiture x1 = meilleurS1(classement->tabClass);	
				double meilleurSecteur1 = x1.tempsSecteur1;
				if(meilleurS1G > meilleurSecteur1){
					meilleurS1G = meilleurSecteur1;
					vS1G = x1.numVoiture;
				}
				struct Voiture x2 = meilleurS2(classement->tabClass);	
				double meilleurSecteur2 = x2.tempsSecteur2;
				if(meilleurS2G > meilleurSecteur2){
					meilleurS2G = meilleurSecteur2;
					vS2G = x2.numVoiture;
				}	
				struct Voiture x3 = meilleurS3(classement->tabClass);
				double meilleurSecteur3 = x3.tempsSecteur3;
				if(meilleurS3G > meilleurSecteur3){
                                	meilleurS3G = meilleurSecteur3;
					vS3G = x3.numVoiture;
                        	}	
				struct Voiture x4 = meilleurTour(classement->tabClass);
				double meilleurT = x4.tempsSecteur1 + x4.tempsSecteur2 + x4.tempsSecteur3;
				if(meilleurTG > meilleurT){
                               		meilleurTG = meilleurT;
					vTG = x4.numVoiture;
                        	}
				struct timeConvert *time = malloc(sizeof(struct timeConvert));
        			tConvert(time,(classement->tabClass[0]).tempsActuel);
        			int min = time->min;
        			int sec = time->tSec;
        			int milli = time->tMilliSec;
				printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
				printf("||								MEILLEURS TEMPS TOUR								||\n");
				printf("--------------------------------------------------------------------------------------------------------------------------------------------------");
        			printf("\n|| /	| /	|%f %i	|%f %i	|%f %i	|%f %i	| /	  	| /		| /		| /		||\n",meilleurSecteur1, x1.numVoiture, meilleurSecteur2, x2.numVoiture, meilleurSecteur3, x3.numVoiture, meilleurT, x4.numVoiture);
				printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
				printf("||								MEILLEURS TEMPS GENERAL								||\n");
				printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");

				printf("|| /	| /	|%f %i	|%f %i	|%f %i	|%f %i	|%i:%i:%i	| /		| /		| /		||\n", meilleurS1G, vS1G, meilleurS2G, vS2G, meilleurS3G, vS3G, meilleurTG, vTG, min, sec, milli);
				printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
				printf("\n");
				sem_post(sem);
			}
		}
		if (k == nbrTours) {
			sem_wait(sem);
			printFichier(2, classement, vS1G, vS2G, vS3G, vTG, meilleurS1G, meilleurS2G, meilleurS3G, meilleurTG);
			sem_post(sem);
		}
	}
	sem_unlink("semP");
	sem_close(sem);
	shmdt(classement);
	free(circuit);
	return 1;
}

void depart(struct Classement *classement, char text[]){
	int y;
	for(y=0 ; y<20 ; y++){
		classement->tabClass[y].tempsSecteur1 = 0.000000;
		classement->tabClass[y].tempsSecteur2 = 0.000000;
		classement->tabClass[y].tempsSecteur3 = 0.000000;
		classement->tabClass[y].tempsActuel = 0.000000;
		classement->tabClass[y].pitstop = 0;
		classement->tabClass[y].nbrPitstop = 0;
		classement->tabClass[y].nbrTour = 0;
		classement->tabClass[y].abandon = 0;
                if (y==0) {
        	        printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                        printf("||								%s                                                       ||\n", text);
                        printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                        printf("||place	|num	|T_s1		|T_s2		|T_s3		|T_tour		|T_actuel	|nbrPit		|nbrTour	|abandon	||\n");
                        printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                 }
		 afficheLigneQ(classement->tabClass[y], y);
         }
	printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                                printf("||                                                              MEILLEURS TEMPS TOUR                                                            ||\n");
                                printf("--------------------------------------------------------------------------------------------------------------------------------------------------");
                                printf("\n|| /  | /     |%f %i  |%f %i  |%f %i  |%f %i  | /             | /             | /             | /             ||\n",0, 0, 0, 0, 0, 0, 0, 0);
                                printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                                printf("||                                                              MEILLEURS TEMPS GENERAL                                                         ||\n");
                                printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");

                                printf("|| /    | /     |%f %i  |%f %i  |%f %i  |%f %i  |%i:%i:%i       | /             | /             | /             ||\n", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
                                printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
}        

void printFichier(int num, struct Classement *class, int vS1G, int vS2G, int vS3G, int vTG, double meilleurS1G, double meilleurS2G, double meilleurS3G, double meilleurTG) {
	FILE* fichier = NULL;
    	int k = num;
	char texte[] = "CLASSEMENT FINAL";
    	if (k == 1) {
    		fichier = fopen("Qualif3.txt", "w");
    	}
    	else if (k == 2) {
    		fichier = fopen("GP.txt", "w");
    	}
    	if (fichier != NULL)
    	{	
		fprintf(fichier, "--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                                                fprintf(fichier, "||								%s								||\n",texte);
						fprintf(fichier, "--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                                                fprintf(fichier, "||place	|num	|T_s1		|T_s2		|T_s3		|T_tour		|T_actuel	|nbrPit		|nbrTour	|abandon	||\n");
                                                fprintf(fichier, "--------------------------------------------------------------------------------------------------------------------------------------------------\n");		
		int lo;
		for (lo = 0; lo < 20; lo++ ) {
			afficheLigneE(class->tabClass[lo],lo, fichier);
		}
		fprintf(fichier, "--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                                fprintf(fichier, "||								MEILLEURS TEMPS	GENERAL								||\n");
                                fprintf(fichier, "--------------------------------------------------------------------------------------------------------------------------------------------------\n");
				fprintf(fichier, "|| /	| /	|%f %i	|%f %i	|%f %i	|%f %i	|%i:%i:%i	| /		| /		| /		||\n", meilleurS1G, vS1G, meilleurS2G, vS2G, meilleurS3G, vS3G, meilleurTG, vTG, 0, 0, 0);
                                fprintf(fichier, "--------------------------------------------------------------------------------------------------------------------------------------------------\n");
        	fclose(fichier);
    	}
}

void afficheLigne(struct Voiture voit, int a) {
	struct timeConvert *time = malloc(sizeof(struct timeConvert));
	tConvert(time, voit.tempsActuel);
	int min = time->min;
	int sec = time->tSec;
	int milli = time->tMilliSec;
	double tps = voit.tempsSecteur1 + voit.tempsSecteur2 + voit.tempsSecteur3;
	printf("||%i	|%i	|%f	|%f	|%f	|%f	|%i:%i:%i	|%i		|%i		|%i		||\n", a+1, voit.numVoiture, voit.tempsSecteur1, voit.tempsSecteur2, voit.tempsSecteur3, tps, min, sec, milli, voit.nbrPitstop, voit.nbrTour,voit.abandon);
}

void afficheLigneE(struct Voiture voit, int a, FILE* fichier) {
        struct timeConvert *time = malloc(sizeof(struct timeConvert));
        tConvert(time, voit.tempsActuel);
        int min = time->min;
        int sec = time->tSec;
        int milli = time->tMilliSec;
        fprintf(fichier, "||%i	|%i	|%f	|%f	|%f	|%f	|%i:%i:%i	|%i		|%i		|%i		||\n", a+1, voit.numVoiture, voit.tempsSecteur1, voit.tempsSecteur2, voit.tempsSecteur3, voit.meilleurTour, min, sec, milli, voit.nbrPitstop, voit.nbrTour,voit.abandon);
}
       
void trieTab(struct Classement *class) {
	struct Voiture v;
	int m;
	int k;
	for (m=0; m<20 ; m++) {
		for (k=0 ; k<20; k++) {
			if (k != m && (class->tabClass[m]).tempsActuel < (class->tabClass[k]).tempsActuel && (class->tabClass[m]).abandon==0) {
				v = class->tabClass[m];
				class->tabClass[m] = class->tabClass[k];
				class->tabClass[k] = v;
			}
		}		
	}
}

void aband(struct Classement *class, int nb){
	struct Voiture v;
	int i;
	int j;
	for(i=0 ; i<nb ; i++){
		for(j=i+1 ; j<nb ; j++){
			if (i != j && (class->tabClass[i]).nbrTour < (class->tabClass[j]).nbrTour && (class->tabClass[i]).abandon == 1) {
                                v = class->tabClass[i];
                                class->tabClass[i] = class->tabClass[j];
                                class->tabClass[j] = v;
                        }
		}
	}
}


struct Voiture meilleurS1(struct Voiture voiture[20]){
	double meilleurTemps = 999;
	struct Voiture v;
	int i;
	for(i=0 ; i<20 ; i++){
		if(meilleurTemps > voiture[i].tempsSecteur1){
			meilleurTemps = voiture[i].tempsSecteur1;
			v = voiture[i];
		}
	}
	return v;
}

struct Voiture meilleurS2(struct Voiture voiture[20]){
        double meilleurTemps = 999;
	struct Voiture v;
        int i;
        for(i=0 ; i<20 ; i++){
                if(meilleurTemps > voiture[i].tempsSecteur2){
                        meilleurTemps = voiture[i].tempsSecteur2;
			v = voiture[i];
                }
        }
        return v;
}

struct Voiture meilleurS3(struct Voiture voiture[20]){
        double meilleurTemps = 999;
	struct Voiture v;
        int i;
        for(i=0 ; i<20 ; i++){
                if(meilleurTemps > voiture[i].tempsSecteur3){
                        meilleurTemps = voiture[i].tempsSecteur3;
			v = voiture[i];
                }
        }
        return v;
}

struct Voiture meilleurTour(struct Voiture voiture[20]){
        double meilleurTemps = 999;
	struct Voiture v;
        int i;
        for(i=0 ; i<20 ; i++){
                if(meilleurTemps > voiture[i].tempsSecteur1 + voiture[i].tempsSecteur2 + voiture[i].tempsSecteur3){
                        meilleurTemps = voiture[i].tempsSecteur1 + voiture[i].tempsSecteur2 + voiture[i].tempsSecteur3;
			v = voiture[i];
                }
        }
        return v;
}
