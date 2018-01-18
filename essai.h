#ifndef ESSAI_H
#define ESSAI_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "rand.h"
#include <stdbool.h>
struct Voiture {
    int numVoiture;            //Numéro de la voiture

    int pitstop;            //Si la voiture s'arrete au stand
    int nbrPitstop;            //Nbr. de pitstop total

    double tempsSecteur1;        //Temps actuel secteur 1
    double tempsSecteur2;        //Temps actuel secteur 2
    double tempsSecteur3;         //Temps actuel secteur 3

    int abandon;            //Si la voiture a abandonner la course

    double tempsActuel;        //Somme des secteurs (et pitstop) en temps réel

    int nbrTour;            //Nombre de tour effectué par une voiture
    };

struct timeConvert {
    int tSec;
    int tMilliSec;
    };

struct Circuit {
    double secteur1Min;        //Temps minimum secteur 1
    double secteur1Max;        //Temps maximum secteur 1

    double secteur2Min;        //Temps minimum secteur 2
    double secteur2Max;        //Temps minimum secteur 2

    double secteur3Min;        //Temps minimum secteur 3
    double secteur3Max;        //Temps minimum secteur 3

    double meilleurSecteur1;    //Meilleur temps secteur 1
    int numVoitureS1;        //Num. de la voiture la plus rapide S1
    double meilleurSecteur2;    //Meilleur temps secteur 2
    int numVoitureS2;        //Num. de la voiture la plus rapide S2
    double meilleurSecteur3;    //Meilleur temps secteur 3
    int numVoitureS3;        //Num. de la voiture la plus rapide S3
    };
struct Pitstop {
    double pistopMin;        //Temps minimum du pitstop
    double pistopMax;        //Temps maximum du pitstop
    };

struct Essai {
    double meilleurTourEssai;    //Meilleur tour durant les essais
    int numVoitureE;        //Num. de la voiture la plus rapide Essai
    };

struct Qualification {
    double meilleurTourQualif;    //Meilleur tour durant les qualifs
    int numvoitureQ;        //Num. de la voiture la plus rapide Qualif
    };

struct Course {
    double meilleurTourCourse;    //Meilleur tour durant la course
    int numvoitureC;        //Num. de la voiture la plus rapide Course
    int nbrTourTotal;        //Nbr. de tour total de la course
    };

struct Classement {
    int position[20];            //Position de la voiture
    struct Voiture* tabClass[20];    //Tableau contenant le classement
    };

double ourRandom(double truc);
double tempsParSecteur(double tempsSecteurMin, double tempsSecteurMax);

#endif
