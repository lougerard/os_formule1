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





/*
Convertir le temps en seconde, milliseconde, microseconde:
sample in (tps en sec avec 6 decimales):
35.403019
*/
/*

int timeConvert(double time, struct TimeClass *timeConverti) { 
	int tempsSeconde, tempsMilliseconde, tempsMicroseconde;
	int i = 0;
	for (i ; i < (int) time ; i++) {
		tempsSeconde += 1;	
	{
 
       // Etape de conversion
       tempsMilliseconde = tempsSeconde  MILLISECS_PAR_SEC;
       tempsMicroseconde = tempsSeconde % MICROSECS_PAR_SEC;
 
       // Affiche les temps convertis 
       printf("\n%d day(s), %d hour(s), %d minute(s), and %d second(s).\n", days, hours, minutes, seconds);
       return 0;
}

*/
/*
sample out: 
tempsMilliseconde
tempsMicroseconde
*/




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
