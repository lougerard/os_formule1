#ifndef ESSAI_H
#define ESSAI_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "rand.h"
struct Voiture {
	int numVoiture;			//Numéro de la voiture

	double tempsSecteur1;		//Temps actuel secteur 1
	double tempsSecteur2;		//Temps actuel secteur 2
	double tempsSecteur3; 		//Temps actuel secteur 3
	double tempsActuel;		//Somme des secteurs en temps réel

	double meilleurTourEssai;	//Meilleur tour durant essais
	int nbrTourEssai;		//Nbr. tour d'essais

	double meilleurTourQualif;	//Meilleur tour durant qualifs
	int nbrTourQualif;		////Nbr. tour de qualifs

	bool pitstop;			//Si la voiture s'arrete au stand
	bool abandon;			//Si la voiture a abandonner la course
	}

struct Circuit {
	double secteur1; 		//Temps réf. secteur 1
	double secteur2;		//Temps réf. secteur 2
	double secteur3;		//Temps réf. secteur 3
	
	double meilleurSecteur1;	//Meilleur temps secteur 1
	int numVoitureS1;		//Num. de la voiture la plus rapide S1
	double meilleurSecteur2;	//Meilleur temps secteur 2
	int numVoitureS2;		//Num. de la voiture la plus rapide S2
	double meilleurSecteur3;	//Meilleur temps secteur 3
	int numVoitureS2;		//Num. de la voiture la plus rapide S3
	
	double meilleurTourEssai;	//Meilleur tour durant les essais

	double meilleurTourQualif;	//Meilleur tour durant les qualifs

	double meilleurTourCourse;	//Meilleur tour durant la course
	}

struct Pitstop {
	double temps pitstop; 		//Temps de pitstop référence
	}

struct Classement {
	int position;			//Position final de la course
	int numVoiture;			//Num. de la voiture par position
	int nbrPitstop;			//Nombre de pitstop par voiture
	int nbrTour;			//Nombre de tour pour la course
	double tempsFinal;		//Temps total de la course
	}

#endif

