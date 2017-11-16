#include <stdio.h>
#include <time.h>
#include <stdlib.h>



double ourRandom(double input) {
	usleep(300000);
        srand(time(NULL));
	double randomNumber = (double) input * (double) rand() / (double) RAND_MAX;
       	//printf("%f\n", randomNumber);
       	usleep(300000);
	return randomNumber;
}

double timeTour(double a, double b, double c) {
	double time;
	time = ourRandom(a) + ourRandom(b) + ourRandom(c);
	return time;
}



/*int main(int argc, char* argv[]) {
	printf("%f\n", ourRandom(1.45));
	printf("%f\n", timeTour(0.5,0.4,0.55));
	return 1;
}*/
