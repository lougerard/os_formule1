all : essai GP Qualification rand

essai : essai.c essai.h
	gcc -Wall -Werror -std=c99 -D_SVID_SOURCE -o essai essai.c essai.h

GP : GP.c
	gcc -Wall -Werror -std=c99 -D_SVID_SOURCE -o GP GP.c 

Qualification : Qualification.c
	gcc -Wall -Werror -std=c99 -D_SVID_SOURCE -o Qualification  Qualification.c

rand : rand.c rand.h
	gcc -Wall -Werror -std=c99 -D_SVID_SOURCE -o rand rand.c rand.h  

clean : 
	rm -rf a.out essai GP test tester Qualification
