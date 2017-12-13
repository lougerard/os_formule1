#ifndef ESSAI_H
#define ESSAI_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "rand.h"
#include <stdbool.h>
struct Voiture {
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

#endif

