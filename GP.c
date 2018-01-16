#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "essai.h"
/*int main(int argc, char *argv[]) {

        return 0;


}*/
int abandon(){
	if ( ourRandom(1.0) > 0.05){
		return 1; //continue
	}
	return 0; // abandon
}

void pitstop(struct Voiture *voiture){
	double rand = ourRandom(14.0);
	if(rand>=5.0 && rand<6.0 ){
		voiture->tempsSecteur3 += ourRandom(0.10)+0.05;
	}
}
		
