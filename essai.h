#ifndef ESSAI_H
#define ESSAI_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "rand.h"
#include <stdbool.h>
struct Voiture {
<<<<<<< HEAD
	int numVoiture;			//Numéro de la voiture

	double tempsSecteur1;		//Temps actuel secteur 1
	double tempsSecteur2;		//Temps actuel secteur 2
	double tempsSecteur3; 		//Temps actuel secteur 3
	double tempsActuel;		//Somme des secteurs en temps réel

	double meilleurTourEssai;	//Meilleur tour durant essais
	int nbrTourEssai;		//Nbr. tour d'essais

	double meilleurTourQualif;	//Meilleur tour durant qualifs
	int nbrTourQualif;		//Nbr. tour de qualifs

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
=======
	int numVoiture;
	double tempsSecteur1;
	double tempsSecteur2;
	double tempsSecteur3; // temps actuel secteur 3
	double tempsActuel;

	double meilleurTourEssai;
	int nbrTourEssai1;

	double meilleurTourQualif;
	int nbrTourQualif;

	double tempsFinal;
	int positionFinal;
	bool pitstop;
	int nbrPitstop;
	bool abandon;
	};

// convertisseur secondes, millisec

struct timeConvert {
	int tSec;
	int tMilliSec;
};




struct Circuit {
	double secteur1Min;
	double secteur2Min;
	double secteur3Min;
	double secteur1Max;
	double secteur2Max;
	double secteur3Max;
	double meilleurSecteur1;
	int numVoitureS1;
	double meilleurSecteur2;
	int numVoitureS2;
	double meilleurSecteur3;
	int numVoitureS3;
	};

struct Essai {
	double meilleurTourEssai;
	};
	
struct Qualification {
	double meilleurTourQualif;
	};

struct Course {
	double meilleurTourCourse;
	int nbrTour;
	};
struct Classement {
	int position;
	int numVoiture;
	int nbrPitstop;
	double tempsFinal;
	};

//Pitstop: temps a chaque pitstop
double ourRandom(double truc);
double tempsParSecteur(double tempsSecteurMin, double tempsSecteurMax);
>>>>>>> a05ca4e0f040cb1b2cb3d7bef42f6840c8046c32

#endif

