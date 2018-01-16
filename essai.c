#include <stdlib.h>
#include "rand.c"
#include <stdio.h>
#include "essai.h"

#define MICROSECS_PAR_SEC  1000000
#define MILLISECS_PAR_SEC  1000



// convertisseur 2e forme d ecriture
void tConvert (struct timeConvert *t, double nbr){
	int sec = (int) nbr;
	int milli = (int) (nbr - sec) * 1000;
	t->tSec = sec;
	t->tMilliSec = milli;
}




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
