all : essai GP Qualification rand compareTo main

essai : essai.c essai.h
	gcc -Wall -Werror -std=c99 -D_SVID_SOURCE -o essai essai.c essai.h

GP : GP.c
	gcc -Wall -Werror -std=c99 -D_SVID_SOURCE -o GP GP.c 

Qualification : Qualification.c
	gcc -Wall -Werror -std=c99 -D_SVID_SOURCE -o Qualification  Qualification.c

rand : rand.c rand.h
	gcc -Wall -Werror -std=c99 -D_SVID_SOURCE -o rand rand.c rand.h  

main : main.c
	gcc -Wall -Werror -std=c99 -D_SVID_SOURCE -o main main.c

compareTo : compareTo.c
	gcc -Wall -Werror -std=c99 -D_SVID_SOURCE -o compareTo compareTo.c 

clean : 
	rm -rf rand a.out essai GP test tester Qualification compareTo compareTo.compile main
