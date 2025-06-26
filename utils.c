//
// Created by medi on 26/06/2025.
//

#include "utils.h"

// Implémentation de la fonction utilitaire de lecture de ligne
void lireLigne(char *chaine, int taille) {
    if (fgets(chaine, taille, stdin) != NULL) {
        chaine[strcspn(chaine, "\n")] = 0;
    } else {
        chaine[0] = '\0';
    }
}
