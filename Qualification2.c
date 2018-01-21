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
#include "Qualification3.c"

#define NBVOITURE 20

void afficheLigneQ(struct Voiture voit, int a);
void trieTabQ2(struct Classement *classement);
struct Voiture meilleurS1Q2(struct Voiture voiture[20]);
struct Voiture meilleurS2Q2(struct Voiture voiture[20]);
struct Voiture meilleurS3Q2(struct Voiture voiture[20]);
struct Voiture meilleurTourQ2(struct Voiture voiture[20]);
void aband(struct Classement *class);

void qualification2(struct Classement *classement, struct Circuit *circuit){
	
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
        size = sizeof(struct Voiture) * NBVOITURE;
        shmid = shmget(9879, size, IPC_CREAT | 0666);
        pid_t pids[20];
	sem_t *sem;
        int i;
        int k;
	int nbrTours = 12;
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
                                voitureCourante = classement->tabClass[i];
                                if (k == 1) {
					voitureCourante.meilleurTour = 999;
                                        voitureCourante.nbrPitstop = 0;
                                        voitureCourante.abandon = 0;
					voitureCourante.nbrTour = 0;
                                }
                                if(voitureCourante.abandon == 0 && i<15){
					voitureCourante.nbrTour = k - 1;
                                        classement->tabClass[i] = voitRoule(voitureCourante, circuit, 40);
                                }
				sem_post(sem);
				shmdt(classement);
                                exit(0);
                        }
                        else if(pids[i] > 0 && i == 20){
                                sem_wait(sem);
                                int a = 1;
                                for(a=0 ; a<20 ; a++){
                                        if (a==0) {
                                                printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                                                printf("||                                                              QUALIFICATION 2		                                                        ||\n");
						printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                                                printf("||place |num    |T_s1           |T_s2           |T_s3           |T_tour         |T_actuel       |nbrPit         |nbrTour        |abandon        ||\n");
                                                printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
                                        }
                                        trieTabQ2(classement);
                                        afficheLigneQ(classement->tabClass[a], a);
                                }
                                struct Voiture x1 = meilleurS1Q2(classement->tabClass);
                                double meilleurSecteur1 = x1.tempsSecteur1;
                                if(meilleurS1G > meilleurSecteur1){
                                        meilleurS1G = meilleurSecteur1;
                                        vS1G = x1.numVoiture;
                                }
                                struct Voiture x2 = meilleurS2Q2(classement->tabClass);
                                double meilleurSecteur2 = x2.tempsSecteur2;
                                if(meilleurS2G > meilleurSecteur2){
                                        meilleurS2G = meilleurSecteur2;
                                        vS2G = x2.numVoiture;
                                }
				struct Voiture x3 = meilleurS3Q2(classement->tabClass);
                                double meilleurSecteur3 = x3.tempsSecteur3;
                                if(meilleurS3G > meilleurSecteur3){
                                        meilleurS3G = meilleurSecteur3;
                                        vS3G = x3.numVoiture;
                                }
                                struct Voiture x4 = meilleurTourQ2(classement->tabClass);
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
                                printf("||                                                              MEILLEURS TEMPS TOUR                                                            ||\n");
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
        }
	sem_unlink("semP");
	sem_close(sem);
}

void trieTabQ2(struct Classement *class) {
        struct Voiture v;
        int m;
        int k;
        for (m=0; m<15 ; m++) {
                for (k=0 ; k<15; k++) {
                        
                        if (k != m && (class->tabClass[m]).meilleurTour < (class->tabClass[k]).meilleurTour) {
                                v = class->tabClass[m];
                                class->tabClass[m] = class->tabClass[k];
                                class->tabClass[k] = v;
                        }
                }
        }
}


struct Voiture meilleurS1Q2(struct Voiture voiture[20]){
        double meilleurTemps = 999;
        struct Voiture v;
        int i;
        for(i=0 ; i<15 ; i++){
                if(meilleurTemps > voiture[i].tempsSecteur1){
                        meilleurTemps = voiture[i].tempsSecteur1;
                        v = voiture[i];
                }
        }
        return v;
}

struct Voiture meilleurS2Q2(struct Voiture voiture[20]){
        double meilleurTemps = 999;
        struct Voiture v;
        int i;
        for(i=0 ; i<15 ; i++){
                if(meilleurTemps > voiture[i].tempsSecteur2){
                        meilleurTemps = voiture[i].tempsSecteur2;
                        v = voiture[i];
                }
        }
        return v;
}

struct Voiture meilleurS3Q2(struct Voiture voiture[20]){
        double meilleurTemps = 999;
        struct Voiture v;
        int i;
        for(i=0 ; i<15 ; i++){
                if(meilleurTemps > voiture[i].tempsSecteur3){
                        meilleurTemps = voiture[i].tempsSecteur3;
                        v = voiture[i];
                }
        }
        return v;
}

struct Voiture meilleurTourQ2(struct Voiture voiture[20]){
        double meilleurTemps = 999;
        struct Voiture v;
        int i;
        for(i=0 ; i<15 ; i++){
                if(meilleurTemps > voiture[i].tempsSecteur1 + voiture[i].tempsSecteur2 + voiture[i].tempsSecteur3){
                        meilleurTemps = voiture[i].tempsSecteur1 + voiture[i].tempsSecteur2 + voiture[i].tempsSecteur3;
                        v = voiture[i];
                }
        }
        return v;
}
