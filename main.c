#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int numero;
    char nom[50];
    char prenom[50];
    char nationalite[50];
    char contact[50];
} Visiteur;

typedef struct {
    int numero;
    char nom[50];
    char prenom[50];
    char langue[50];
    char statut[20];
} Guide;

typedef struct {
    char code[10];
    char libelle[50];
    float tarif;
} TypeVisite;

typedef struct {
    int numeroVisite;
    char date[20];
    int numeroVisiteur;
    char codeTypeVisite[10];
    int numeroGuide;
    int duree;
    float montantPaye;
} Visite;
