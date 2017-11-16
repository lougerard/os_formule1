#include <stdlib.h>
#include "rand.c"
#include <stdio.h>
#include "essai.h"

//double ourRandom(double truc);

/*int main(int argc, char* argv[]){
	double a = tempsParSecteur(30.0, 45.0);
	printf("%f\n",a);
	return 0;
}*/

double tempsParSecteur(double tempsSecteurMin, double tempsSecteurMax){
	double temps = ourRandom((double)(tempsSecteurMax - tempsSecteurMin));
	temps += tempsSecteurMin;
	return temps;
}
