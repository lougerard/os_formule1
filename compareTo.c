#include <stdio.h>
#include <stdlib.h>

void testCompareTo(double a, double b);

int main(int argc, char* argv[]){

	testCompareTo(1.2,0.5);
	testCompareTo(1.45,1.45);
	testCompareTo(0.12,5.98);

}

/*
Methode compareTo
time1 : temps en secondes de type double
time2 : temps en secondes de type double
retourne 1 si time1 est plus grand que time2, 0 si time1 = time2, -1 sinon
*/
int compareTo(double time1, double time2){
	if(time1>time2){
		return 1;
	}else if(time1==time2){
		return 0;
	}else{
		return -1;
	}
}

/*
Test compareTo
affiche le resultat de compareTo
*/
void testCompareTo(double t1, double t2){
	if(compareTo(t1,t2)==1){
		printf("t1 est plus grand que t2\n") ;
	}else if(compareTo(t1,t2)==0){
		printf("t1 = t2\n");
	}else if(compareTo(t1,t2)==-1){
		printf("t1 est plus petit que t2\n");
	}
}
