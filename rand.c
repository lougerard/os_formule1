#include <stdio.h>
#include <time.h>
#include <stdlib.h>



double ourRandom(double input) {

        srand(time(NULL));
	double randomNumber = (double) input * (double) rand() / (double) RAND_MAX;
       	//printf("%f\n", randomNumber);
	return randomNumber;
}


int main(int argc, char* argv[]) {
	printf("%f\n", ourRandom(1.5));
	return 1;
}
