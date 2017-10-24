#include <stdlib.h>

#include <stdio.h>
#include "rand.h"

double ourRandom(double truc);

int main (int argc, char* argv[]){
	double a = ourRandom((double) 0.8);
	printf("%f\n",a);

}

