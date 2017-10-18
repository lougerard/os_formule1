#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {

        srand((unsigned int)time(NULL));
        double a = 1.75;
        int i=0;
        for (i;i<20;i++)
                printf("%f\n", ((double)rand()/(double)(RAND_MAX)) * a);
        return 0;


}

