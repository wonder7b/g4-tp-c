//
// Created by medi on 26/06/2025.
//
#include "guide.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



void ajouterGuideFichier(Guide g) {
    FILE *f = fopen("guides.txt", "a");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier guides.txt\n");
        return;
    }
    fprintf(f, "%d;%s;%s;%s;%s\n", g.numero, g.nom, g.prenom, g.langue, g.statut);
    fclose(f);
}

int chargerGuides(Guide **guides) {
    FILE *f = fopen("guides.txt", "r");
    if (f == NULL) return 0;

    int count = 0;
    char line[256];
    *guides = NULL;

    while (fgets(line, sizeof(line), f) != NULL) {
        *guides = (Guide *)realloc(*guides, (count + 1) * sizeof(Guide));
        if (*guides == NULL) {
            printf("Erreur d'allocation memoire pour les guides.\n");
            fclose(f);
            return 0;
        }
        sscanf(line, "%d;%49[^;];%49[^;];%49[^;];%19[^\n]",
               &(*guides)[count].numero,
               (*guides)[count].nom,
               (*guides)[count].prenom,
               (*guides)[count].langue,
               (*guides)[count].statut);
        count++;
    }
    fclose(f);
    return count;
}

void mettreAJourStatutGuide(int numeroGuide, const char *nouveauStatut) {
    Guide *guides;
    int nbGuides = chargerGuides(&guides);

    if (nbGuides == 0 && guides == NULL) {
        printf("Aucun guide trouve ou erreur de chargement.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < nbGuides; i++) {
        if (guides[i].numero == numeroGuide) {
            strcpy(guides[i].statut, nouveauStatut);
            found = 1;
            break;
        }
    }

    if (found) {
        FILE *f = fopen("guides.txt", "w");
        if (f == NULL) {
            printf("Erreur lors de l'ouverture du fichier guides.txt pour mise a jour.\n");
            free(guides);
            return;
        }
        for (int i = 0; i < nbGuides; i++) {
            fprintf(f, "%d;%s;%s;%s;%s\n", guides[i].numero, guides[i].nom, guides[i].prenom, guides[i].langue, guides[i].statut);
        }
        fclose(f);
        printf("Statut du guide mis a jour avec succes.\n");
    } else {
        printf("Guide avec le numero %d non trouve.\n", numeroGuide);
    }
    free(guides);
}

int guideExiste(int num) {
    Guide *guides;
    int nb = chargerGuides(&guides);
    if (guides == NULL) return 0;
    for (int i = 0; i < nb; i++) {
        if (guides[i].numero == num) {
            free(guides);
            return 1;
        }
    }
    free(guides);
    return 0;
}

void ajouterGuide() {
    Guide g;
    printf("\n--- Ajouter un guide touristique ---\n");

    do {
        printf("Numero du guide (entier positif): ");
        if (scanf("%d", &g.numero) != 1 || g.numero <= 0) {
            printf("Saisie invalide. Veuillez entrer un entier positif.\n");
            while (getchar() != '\n');
            continue;
        }
        if (guideExiste(g.numero)) {
            printf("Ce numero de guide existe deja. Veuillez en choisir un autre.\n");
        } else {
            break;
        }
    } while (1);
    while (getchar() != '\n');

    printf("Nom: ");
    lireLigne(g.nom, sizeof(g.nom));
    printf("Prenom: ");
    lireLigne(g.prenom, sizeof(g.prenom));
    printf("Langue parlee: ");
    lireLigne(g.langue, sizeof(g.langue));

    printf("Statut (disponible/non_disponible): ");
    do {
        lireLigne(g.statut, sizeof(g.statut));
        if (strcmp(g.statut, "disponible") != 0 && strcmp(g.statut, "non_disponible") != 0) {
            printf("Statut invalide. Veuillez entrer 'disponible' ou 'non_disponible': ");
        } else {
            break;
        }
    } while (1);


    ajouterGuideFichier(g);
    printf("Guide ajoute avec succes!\n");
}
