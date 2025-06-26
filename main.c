#include <stdio.h>
#include <stdlib.h>

// Inclusion des en-tetes des modules principaux
#include "visiteur.h"
#include "guide.h"
#include "fonctions.h" // Contient les autres fonctions du menu

// Fonction pour afficher le menu principal
void afficherMenu() {
    printf("\n--- Menu Principal Gestion Site Touristique ---\n");
    printf("1. Ajouter un visiteur\n");
    printf("2. Ajouter un guide touristique\n");
    printf("3. Ajouter un type de visite\n");
    printf("4. Enregistrer une visite\n");
    printf("5. Afficher les visites d'un visiteur donne\n");
    printf("6. Afficher les guides disponibles selon une langue donnee\n");
    printf("7. Afficher les statistiques globales\n");
    printf("0. Quitter\n");
    printf("Choisissez une option: ");
}

int main() {
    int choix;

    // Creation des fichiers s'ils n'existent pas
    // Cette étape est placée ici pour s'assurer que les fichiers existent au démarrage
    FILE *f;
    f = fopen("visiteurs.txt", "a+"); if (f) fclose(f);
    f = fopen("guides.txt", "a+"); if (f) fclose(f);
    f = fopen("tarifs.txt", "a+"); if (f) fclose(f);
    f = fopen("visites.txt", "a+"); if (f) fclose(f);

    do {
        afficherMenu();
        if (scanf("%d", &choix) != 1) {
            printf("Saisie invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n');
            choix = -1;
        } else {
            while (getchar() != '\n');
        }

        switch (choix) {
            case 1:
                ajouterVisiteur();
                break;
            case 2:
                ajouterGuide();
                break;
            case 3:
                ajouterTypeVisite();
                break;
            case 4:
                enregistrerVisite();
                break;
            case 5:
                afficherVisitesVisiteur();
                break;
            case 6:
                afficherGuidesDisponibles();
                break;
            case 7:
                afficherStatistiques();
                break;
            case 0:
                printf("Merci d'avoir utilise le programme. Au revoir!\n");
                break;
            default:
                printf("Option invalide. Veuillez reessayer.\n");
                break;
        }
        printf("\nAppuyez sur Entree pour continuer...");
        while (getchar() != '\n');
    } while (choix != 0);

    return 0;
}
