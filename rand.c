#include <stdio.h>
#include <time.h>
#include <stdlib.h>

double ourRandom(double input) {
	double randomNumber = (double) input * (double) rand() / (double) RAND_MAX;
	return randomNumber;
}

double timeTour(double a, double b, double c) {
	double time;
	time = ourRandom(a) + ourRandom(b) + ourRandom(c);
	return time;
}

