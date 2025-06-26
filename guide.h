//
// Created by medi on 26/06/2025.
//

#ifndef GUIDE_H
#define GUIDE_H

#include "structures.h"
#include "utils.h" // Inclut lireLigne

// Fonctions d'E/S fichier pour les guides
void ajouterGuideFichier(Guide g);
int chargerGuides(Guide **guides);
void mettreAJourStatutGuide(int numeroGuide, const char *nouveauStatut);

// Fonctions de validation et d'action
int guideExiste(int num);
void ajouterGuide();

#endif
