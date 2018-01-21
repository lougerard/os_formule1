#include <stdlib.h>
#include "rand.c"
#include <stdio.h>
#include "essai.h"

#define MICROSECS_PAR_SEC  1000000
#define MILLISECS_PAR_SEC  1000

// convertisseur 2e forme d ecriture
void tConvert (struct timeConvert *t, double nbr){
	int sec = (int) nbr;
	int milli = (int) ((nbr - sec) * 1000);
	int min = 0;
	while (sec >= 60) {
		sec = sec - 60;
		min = min +1;	
	}
	t->tSec = sec;
	t->tMilliSec = milli;
	t->min = min;
}

//double ourRandom(double truc);

double tempsParSecteur(double tempsSecteurMin, double tempsSecteurMax){
	double temps = ourRandom((double)(tempsSecteurMax - tempsSecteurMin));
	temps += tempsSecteurMin;
	return temps;
}
