#include "essai.h"
#include "rand.h"


int main(int argc, char* argv[]){

//printf("%f", ourRandom(1.2));
return 0;
}

void afficheLigne(int numVoiture, double tempsSecteur1, double tempsSecteur2, double tempsSecteur3, double tempsActuel, int nbrPitstop, int nbrTour){
	printf("||%i     |%f      |%f     |%f   |%f      |%i     |%i     ||", numVoiture, 		tempsSecteur1, tempsSecteur2, tempsSecteur3, tempsActuel, nbrPitstop, nbrTour);
}
