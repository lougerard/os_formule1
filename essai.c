#include <stdlib.h>
#include "rand.c"
#include <stdio.h>
#include "essai.h"

#define MICROSECS_PAR_SEC  1000000
#define MILLISECS_PAR_SEC  1000


/*
// convertisseur 2e forme d ecriture
tConvert ( struct timeConvert *t, double nbre){
	int n = 8;
	int sec;
	int milli;
	int micro;
	for( int i = 0 ; i<n ; i++){
		sec + i;
		t->sec= t;      	 /* ex:  sec= 30 */
		t->milli= t/1000;	 /* ex: milli= 024 */
		t->micro= t/100000;	 /* ex: micro= 348 */			
	}
}
*/





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
