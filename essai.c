#include <stdlib.h>
//#include "rand.h"
//#include "rand.c"
#include <stdio.h>
//#include "essai.h"

//double ourRandom(double truc);

/*int main(int argc, char* argv[]){
	//double a = ourRandom((double) 0.8);
	//printf("%f\n",a);
	return 0;
}*/

double tempsParSecteur(double tempsSecteurMin, double tempsSecteurMax){
	double temps = ourRandom((double)(tempsSecteurMax - tempsSecteurMin));
	temps += tempsSecteurMin;
	return temps;
}
