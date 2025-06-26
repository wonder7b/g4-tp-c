#include "visiteur.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// lireLigne n'est plus déclarée ni implémentée ici, elle vient de utils.h/c

void ajouterVisiteurFichier(Visiteur v) {
    FILE *f = fopen("visiteurs.txt", "a");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier visiteurs.txt\n");
        return;
    }
    fprintf(f, "%d;%s;%s;%s;%s\n", v.numero, v.nom, v.prenom, v.nationalite, v.contact);
    fclose(f);
}

int chargerVisiteurs(Visiteur **visiteurs) {
    FILE *f = fopen("visiteurs.txt", "r");
    if (f == NULL) return 0;

    int count = 0;
    char line[256];
    *visiteurs = NULL;

    while (fgets(line, sizeof(line), f) != NULL) {
        *visiteurs = (Visiteur *)realloc(*visiteurs, (count + 1) * sizeof(Visiteur));
        if (*visiteurs == NULL) {
            printf("Erreur d'allocation memoire pour les visiteurs.\n");
            fclose(f);
            return 0;
        }
        sscanf(line, "%d;%49[^;];%49[^;];%49[^;];%49[^\n]",
               &(*visiteurs)[count].numero,
               (*visiteurs)[count].nom,
               (*visiteurs)[count].prenom,
               (*visiteurs)[count].nationalite,
               (*visiteurs)[count].contact);
        count++;
    }
    fclose(f);
    return count;
}

int visiteurExiste(int num) {
    Visiteur *visiteurs;
    int nb = chargerVisiteurs(&visiteurs);
    if (visiteurs == NULL) return 0;
    for (int i = 0; i < nb; i++) {
        if (visiteurs[i].numero == num) {
            free(visiteurs);
            return 1;
        }
    }
    free(visiteurs);
    return 0;
}

void ajouterVisiteur() {
    Visiteur v;
    printf("\n--- Ajouter un visiteur ---\n");

    do {
        printf("Numero du visiteur (entier positif): ");
        if (scanf("%d", &v.numero) != 1 || v.numero <= 0) {
            printf("Saisie invalide. Veuillez entrer un entier positif.\n");
            while (getchar() != '\n');
            continue;
        }
        if (visiteurExiste(v.numero)) {
            printf("Ce numero de visiteur existe deja. Veuillez en choisir un autre.\n");
        } else {
            break;
        }
    } while (1);
    while (getchar() != '\n');

    printf("Nom: ");
    lireLigne(v.nom, sizeof(v.nom));
    printf("Prenom: ");
    lireLigne(v.prenom, sizeof(v.prenom));
    printf("Nationalite: ");
    lireLigne(v.nationalite, sizeof(v.nationalite));
    printf("Contact: ");
    lireLigne(v.contact, sizeof(v.contact));

    ajouterVisiteurFichier(v);
    printf("Visiteur ajoute avec succes!\n");
}
