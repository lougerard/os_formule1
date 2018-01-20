CC=gcc -std=gnu99 -lrt

all : essai.o GP.o rand.o compareTo.o main.o circuit.o
	$(CC) -o main essai.o GP.o rand.o compareTo.o circuit.o main.o

essai.o : essai.c
	 $(CC) -c essai.c

GP.o : GP.c
	$(CC) -c GP.c 

rand.o : rand.c
	$(CC) -c rand.c

main.o : main.c
	$(CC) -c main.c

compareTo.o : compareTo.c
	$(CC) -c compareTo.c 

circuit.o : circuit.c
	$(CC) -c circuit.c

clean : 
	rm -rf *.o main
