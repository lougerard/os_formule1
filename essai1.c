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

void afficheLigneE(struct Voiture voit, int a, FILE* fichier);
void printFichier(int num, struct Classement *class, int vS1G, int vS2G, int vS3G, int vTG, double meilleurS1G, double meilleurS2G, double meilleurS3G, double meilleurTG);
void afficheLigneQ(struct Voiture voit, int a);
void trieTabQ(struct Classement *classement);
struct Voiture meilleurS1(struct Voiture voiture[20]);
struct Voiture meilleurS2(struct Voiture voiture[20]);
struct Voiture meilleurS3(struct Voiture voiture[20]);
struct Voiture meilleurTour(struct Voiture voiture[20]);
void aband(struct Classement *class);
void departQ1(struct Classement *classement, char text[]);

void essai1(struct Circuit *circuit){
int loop;
for (loop = 1; loop <= 3 ; loop++) {
	struct Classement *classement = malloc(sizeof(struct Classement));
        int numeroVoitures[20] = {44,77,3,33,5,7,11,31,19,18,14,2,10,55,8,20,27,30,9,94};
        double meilleurS1G = 999;
        int vS1G = 0;
        double meilleurS2G = 999;
        int vS2G = 0;
        double meilleurS3G = 999;
        int vS3G = 0;
	double meilleurTG = 999;
        int vTG = 0;
	sem_t *sem;
	struct shmid_ds *buf;
        key_t key=9880;
        int shmid, size;
        size = sizeof(struct Voiture) * NBVOITURE;
        shmid = shmget(9880, size, IPC_CREAT | 0666);
	shmctl(shmid, IPC_RMID, buf);
	shmid = shmget(9880, size, IPC_CREAT | 0666);
        pid_t pids[20];
        int i;
        int k;
	int nbrTours = 5;
	int nombreVoiture=20;
        struct Voiture voitureCourante;
	sem = sem_open("semP", O_CREAT | O_EXCL, 0644, 1);
        for( k=1; k <= nbrTours ; k++) {
                for( i=0 ; i<=nombreVoiture ; i++ ){
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
				if (k > 1) {
                                        voitureCourante = classement->tabClass[i];
                                }
                                if (k == 1) {
                                        voitureCourante.numVoiture = numeroVoitures[i];
					voitureCourante.meilleurTour = 999;
                                        voitureCourante.nbrPitstop = 0;
                                        voitureCourante.abandon = 0;
					voitureCourante.nbrTour = 0;
                                }
                                if(voitureCourante.abandon == 0){
					voitureCourante.nbrTour = k - 1;
                                        classement->tabClass[i] = voitRoule(voitureCourante, circuit, 40);
                                }
				sem_post(sem);
				//shmdt(classement);
                                exit(0);
                        }
                        else if(pids[i] > 0 && i == 20){
				int shmidPere;
				shmidPere = shmget(key, size, 0666);
				classement = shmat(shmidPere, 0, 0);
                                sem_wait(sem);
				int a = 1;
                                for(a=0 ; a<20 ; a++){
                                        if (a==0) {
                                                printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                                                printf("||								ESSAI %i										||\n", loop);
						printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                                                printf("||place	|num	|T_s1		|T_s2		|T_s3		|T_tour		|T_actuel	|nbrPit		|nbrTour	|abandon	||\n");
                                                printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                                        }
                                        trieTabQ(classement);
                                        afficheLigneQ(classement->tabClass[a], a);
                                }
                                struct Voiture x1 = meilleurS1(classement->tabClass);
                                double meilleurSecteur1 = x1.tempsSecteur1;
                                if(meilleurS1G > meilleurSecteur1 && meilleurSecteur1 != 0){
                                        meilleurS1G = meilleurSecteur1;
                                        vS1G = x1.numVoiture;
                                }
                                struct Voiture x2 = meilleurS2(classement->tabClass);
                                double meilleurSecteur2 = x2.tempsSecteur2;
                                if(meilleurS2G > meilleurSecteur2 && meilleurSecteur2 != 0){
                                        meilleurS2G = meilleurSecteur2;
                                        vS2G = x2.numVoiture;
                                }
				struct Voiture x3 = meilleurS3(classement->tabClass);
                                double meilleurSecteur3 = x3.tempsSecteur3;
                                if(meilleurS3G > meilleurSecteur3 && meilleurSecteur3 != 0){
                                        meilleurS3G = meilleurSecteur3;
                                        vS3G = x3.numVoiture;
                                }
                                struct Voiture x4 = meilleurTour(classement->tabClass);
                                double meilleurT = x4.tempsSecteur1 + x4.tempsSecteur2 + x4.tempsSecteur3;
                                if(meilleurTG > meilleurT && meilleurTour != 0){
                                        meilleurTG = meilleurT;
                                        vTG = x4.numVoiture;
                                }
                                struct timeConvert *time = malloc(sizeof(struct timeConvert));
                                tConvert(time,(classement->tabClass[0]).tempsActuel);
                                int min = time->min;
                                int sec = time->tSec;
                                int milli = time->tMilliSec;
                                printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                                printf("||								MEILLEURS TEMPS									||\n");
                                printf("--------------------------------------------------------------------------------------------------------------------------------------------------");
                                printf("\n|| /	| /	|%f %i	|%f %i	|%f %i	|%f %i	| /		| /		| /		| /		||\n",meilleurSecteur1, x1.numVoiture, meilleurSecteur2, x2.numVoiture, meilleurSecteur3, x3.numVoiture, meilleurT, x4.numVoiture);
                                printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                                printf("||                                                              MEILLEURS TEMPS GENERAL                                                         ||\n");
                                printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
				printf("|| /	| /	|%f %i	|%f %i	|%f %i	|%f %i	|%i:%i:%i	| /		| /		| /		||\n", meilleurS1G, vS1G, meilleurS2G, vS2G, meilleurS3G, vS3G, meilleurTG, vTG, min, sec, milli);
                                printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");

				printf("\n");
                                sem_post(sem);
                        }
                }
		printf("%i %i %i %i %f %f %f %f", vS1G, vS2G, vS3G, vTG, meilleurS1G, meilleurS2G, meilleurS3G, meilleurTG);
		if (k == nbrTours) {
			sem_wait(sem);
			printFichier(loop, classement, vS1G, vS2G, vS3G, vTG, meilleurS1G, meilleurS2G, meilleurS3G, meilleurTG);
			sem_post(sem);
		}
        }

	usleep(1000000);
	shmdt(classement);
	sem_unlink("semP");
	sem_close(sem);

}
}

void printFichier(int num, struct Classement *class, int vS1G, int vS2G, int vS3G, int vTG, double meilleurS1G, double meilleurS2G, double meilleurS3G, double meilleurTG) {
	FILE* fichier = NULL;
    	int k = num;
    	if (k == 1) {
    	fichier = fopen("essai1.txt", "w");
    	}
    	else if (k == 2) {
    		fichier = fopen("essai2.txt", "w");
    	}
    	else if (k == 3) {
    		fichier = fopen("essai3.txt", "w");
    	}
    	if (fichier != NULL)
    	{	
		fprintf(fichier, "--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                                                fprintf(fichier, "||								ESSAI % i									||\n", k);
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

void trieTabQ(struct Classement *class) {
        struct Voiture v;
        int m;
        int k;
        for (m=0; m<20 ; m++) {
                for (k=0 ; k<20; k++) {
			
                        if (k != m && (class->tabClass[m]).meilleurTour < (class->tabClass[k]).meilleurTour) {
                                v = class->tabClass[m];
                                class->tabClass[m] = class->tabClass[k];
                                class->tabClass[k] = v;
                        }
                }
        }
}


void afficheLigneE(struct Voiture voit, int a, FILE* fichier) {
        struct timeConvert *time = malloc(sizeof(struct timeConvert));
        tConvert(time, voit.tempsActuel);
        int min = time->min;
        int sec = time->tSec;
        int milli = time->tMilliSec;
        fprintf(fichier, "||%i	|%i	|%f	|%f	|%f	|%f	|%i:%i:%i	|%i		|%i		|%i		||\n", a+1, voit.numVoiture, voit.tempsSecteur1, voit.tempsSecteur2, voit.tempsSecteur3, voit.meilleurTour, min, sec, milli, voit.nbrPitstop, voit.nbrTour,voit.abandon);
 }
void afficheLigneQ(struct Voiture voit, int a) {
        struct timeConvert *time = malloc(sizeof(struct timeConvert));
        tConvert(time, voit.tempsActuel);
        int min = time->min;
        int sec = time->tSec;
        int milli = time->tMilliSec;
        printf( "||%i	|%i	|%f	|%f	|%f	|%f	|%i:%i:%i	|%i		|%i		|%i		||\n", a+1, voit.numVoiture, voit.tempsSecteur1, voit.tempsSecteur2, voit.tempsSecteur3, voit.meilleurTour, min, sec, milli, voit.nbrPitstop, voit.nbrTour,voit.abandon);
 }

void aband(struct Classement *class){
        struct Voiture v;
        int i;
        int j;
        for(i=0 ; i<20 ; i++){
                for(j=i+1 ; j<20 ; j++){
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






int main(int argc, char* argv[]) {
	struct Circuit *circuit = malloc(sizeof(struct Circuit));
	circuit->secteur1Min = 10.0;
        circuit->secteur1Max = 20.0;
        circuit->secteur2Min = 25.0;
        circuit->secteur2Max = 35.0;
        circuit->secteur3Min = 35.0;
        circuit->secteur3Max = 40.0;
	essai1(circuit);
}



