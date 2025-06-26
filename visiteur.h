//
// Created by medi on 26/06/2025.
//

#ifndef VISITEUR_H
#define VISITEUR_H

#include "structures.h"
#include "utils.h"

// Fonctions d'E/S fichier pour les visiteurs
void ajouterVisiteurFichier(Visiteur v);
int chargerVisiteurs(Visiteur **visiteurs);

// Fonctions de validation et d'action
int visiteurExiste(int num);
void ajouterVisiteur();

#endif
