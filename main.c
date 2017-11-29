#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "rand.h"
#include "essai.h"
#include "circuit.c"

int main (int argc, char* argv[]){
	srand(time(NULL));
	struct Circuit *circuit = malloc(sizeof(struct Circuit));
	circuit->secteur1Min = 30.0;
	circuit->secteur1Max = 40.0;
	circuit->secteur2Min = 25.0;
	circuit->secteur2Max = 35.0;
	circuit->secteur3Min = 35.0;
	circuit->secteur3Max = 40.0;
	struct Voiture tabVoit[20];
	struct Voiture *voit1 = malloc(sizeof(struct Voiture));
	voitRoule(voit1, circuit);
	//tabVoit[0] = voit1;
	return 1;
}
