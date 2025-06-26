//
// Created by medi on 26/06/2025.
//

#ifndef FONCTIONS_H
#define FONCTIONS_H

#include "structures.h"
#include "visiteur.h" // Pour visiteurExiste, chargerVisiteurs (via leurs .c)
#include "guide.h"    // Pour guideExiste, chargerGuides, mettreAJourStatutGuide (via leurs .c)
#include "utils.h"    // Pour lireLigne

// Fonctions d'E/S fichier
void ajouterTypeVisiteFichier(TypeVisite tv);
void ajouterVisiteFichier(Visite v);
int chargerTypesVisites(TypeVisite **typesVisites);
int chargerVisites(Visite **visites);

// Fonctions de validation et utilitaires
int typeVisiteExiste(const char *code);
int numeroVisiteExiste(int num);
float getTarifTypeVisite(const char *code);
Guide *trouverGuide(int numGuide, int *nbGuides);

// Fonctions d'action du menu
void ajouterTypeVisite();
void enregistrerVisite();
void afficherVisitesVisiteur();
void afficherGuidesDisponibles();
void afficherStatistiques();

#endif
