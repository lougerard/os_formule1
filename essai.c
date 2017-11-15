#include <stdlib.h>
#include "essai.h"
#include <stdio.h>
#include "rand.h"

double ourRandom(double truc);

int main (int argc, char* argv[]){
//	double a = ourRandom((double) 0.8);
	printf("%f\n",1.2);

}

double tempsParSecteur(double tempsSecteurMin, double tempsSecteurMax){
	double temps = tempsSecteurMin + ourRandom(tempsSecteurMax - tempsSecteurMin);
	return temps;
}
