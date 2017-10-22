#include "rand.h"

double ourRandom(double truc);

int main (int argc, char* argv[]){
	printf("%f\n",ourRandom(1.2));

}

double ourRandom(double input) {

        srand(time(NULL));
        double randomNumber = (double) input * (double) rand() / (double) RAND_MAX;
        //printf("%f\n", randomNumber);
        return randomNumber;
}
