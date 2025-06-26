#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



void ajouterTypeVisiteFichier(TypeVisite tv) {
    FILE *f = fopen("tarifs.txt", "a");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier tarifs.txt\n");
        return;
    }
    fprintf(f, "%s;%s;%.2f\n", tv.code, tv.libelle, tv.tarif);
    fclose(f);
}

void ajouterVisiteFichier(Visite v) {
    FILE *f = fopen("visites.txt", "a");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier visites.txt\n");
        return;
    }
    fprintf(f, "%d;%s;%d;%s;%d;%d;%.2f\n", v.numeroVisite, v.date, v.numeroVisiteur,
            v.codeTypeVisite, v.numeroGuide, v.duree, v.montantPaye);
    fclose(f);
}

int chargerTypesVisites(TypeVisite **typesVisites) {
    FILE *f = fopen("tarifs.txt", "r");
    if (f == NULL) return 0;

    int count = 0;
    char line[256];
    *typesVisites = NULL;

    while (fgets(line, sizeof(line), f) != NULL) {
        *typesVisites = (TypeVisite *)realloc(*typesVisites, (count + 1) * sizeof(TypeVisite));
        if (*typesVisites == NULL) {
            printf("Erreur d'allocation memoire pour les types de visites.\n");
            fclose(f);
            return 0;
        }
        sscanf(line, "%9[^;];%49[^;];%f\n",
               (*typesVisites)[count].code,
               (*typesVisites)[count].libelle,
               &(*typesVisites)[count].tarif);
        count++;
    }
    fclose(f);
    return count;
}

int chargerVisites(Visite **visites) {
    FILE *f = fopen("visites.txt", "r");
    if (f == NULL) return 0;

    int count = 0;
    char line[256];
    *visites = NULL;

    while (fgets(line, sizeof(line), f) != NULL) {
        *visites = (Visite *)realloc(*visites, (count + 1) * sizeof(Visite));
        if (*visites == NULL) {
            printf("Erreur d'allocation memoire pour les visites.\n");
            fclose(f);
            return 0;
        }
        sscanf(line, "%d;%19[^;];%d;%9[^;];%d;%d;%f\n",
               &(*visites)[count].numeroVisite,
               (*visites)[count].date,
               &(*visites)[count].numeroVisiteur,
               (*visites)[count].codeTypeVisite,
               &(*visites)[count].numeroGuide,
               &(*visites)[count].duree,
               &(*visites)[count].montantPaye);
        count++;
    }
    fclose(f);
    return count;
}

int typeVisiteExiste(const char *code) {
    TypeVisite *typesVisites;
    int nb = chargerTypesVisites(&typesVisites);
    if (typesVisites == NULL) return 0;
    for (int i = 0; i < nb; i++) {
        if (strcmp(typesVisites[i].code, code) == 0) {
            free(typesVisites);
            return 1;
        }
    }
    free(typesVisites);
    return 0;
}

int numeroVisiteExiste(int num) {
    Visite *visites;
    int nb = chargerVisites(&visites);
    if (visites == NULL) return 0;
    for (int i = 0; i < nb; i++) {
        if (visites[i].numeroVisite == num) {
            free(visites);
            return 1;
        }
    }
    free(visites);
    return 0;
}

float getTarifTypeVisite(const char *code) {
    TypeVisite *typesVisites;
    int nb = chargerTypesVisites(&typesVisites);
    if (typesVisites == NULL) return -1.0;
    for (int i = 0; i < nb; i++) {
        if (strcmp(typesVisites[i].code, code) == 0) {
            float tarif = typesVisites[i].tarif;
            free(typesVisites);
            return tarif;
        }
    }
    free(typesVisites);
    return -1.0;
}

Guide *trouverGuide(int numGuide, int *nbGuides) {
    Guide *guides;
    *nbGuides = chargerGuides(&guides);
    if (guides == NULL) return NULL;
    for (int i = 0; i < *nbGuides; i++) {
        if (guides[i].numero == numGuide) {
            return &guides[i];
        }
    }
    return NULL;
}


void ajouterTypeVisite() {
    TypeVisite tv;
    printf("\n--- Ajouter un type de visite ---\n");

    do {
        printf("Code du type de visite (ex: LIBRE, GUIDEE, SCOLAIRE - max 9 caracteres): ");
        lireLigne(tv.code, sizeof(tv.code));
        if (strlen(tv.code) == 0) {
            printf("Le code ne peut pas etre vide.\n");
            continue;
        }
        if (typeVisiteExiste(tv.code)) {
            printf("Ce code de type de visite existe deja. Veuillez en choisir un autre.\n");
        } else {
            break;
        }
    } while (1);

    printf("Libelle (ex: Visite libre, Visite guidee, Scolaire): ");
    lireLigne(tv.libelle, sizeof(tv.libelle));

    do {
        printf("Tarif en FCFA (entier ou decimal positif): ");
        if (scanf("%f", &tv.tarif) != 1 || tv.tarif <= 0) {
            printf("Saisie invalide. Veuillez entrer un nombre positif.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);
    while (getchar() != '\n');

    ajouterTypeVisiteFichier(tv);
    printf("Type de visite ajoute avec succes!\n");
}

void enregistrerVisite() {
    Visite v;
    printf("\n--- Enregistrer une visite ---\n");

    do {
        printf("Numero de la visite (entier positif): ");
        if (scanf("%d", &v.numeroVisite) != 1 || v.numeroVisite <= 0) {
            printf("Saisie invalide. Veuillez entrer un entier positif.\n");
            while (getchar() != '\n');
            continue;
        }
        if (numeroVisiteExiste(v.numeroVisite)) {
            printf("Ce numero de visite existe deja. Veuillez en choisir un autre.\n");
        } else {
            break;
        }
    } while (1);
    while (getchar() != '\n');

    printf("Date de la visite (JJ/MM/AAAA): ");
    lireLigne(v.date, sizeof(v.date));

    do {
        printf("Numero du visiteur: ");
        if (scanf("%d", &v.numeroVisiteur) != 1 || v.numeroVisiteur <= 0) {
            printf("Saisie invalide. Veuillez entrer un entier positif.\n");
            while (getchar() != '\n');
            continue;
        }
        if (!visiteurExiste(v.numeroVisiteur)) {
            printf("Ce visiteur n'existe pas. Veuillez l'ajouter d'abord.\n");
        } else {
            break;
        }
    } while (1);
    while (getchar() != '\n');

    do {
        printf("Code du type de visite (ex: LIBRE, GUIDEE): ");
        lireLigne(v.codeTypeVisite, sizeof(v.codeTypeVisite));
        if (!typeVisiteExiste(v.codeTypeVisite)) {
            printf("Ce type de visite n'existe pas. Veuillez l'ajouter d'abord.\n");
        } else {
            break;
        }
    } while (1);

    v.montantPaye = getTarifTypeVisite(v.codeTypeVisite);
    if (v.montantPaye == -1.0) {
        printf("Erreur: Type de visite non trouve pour le calcul du montant.\n");
        return;
    }

    int nbGuides;
    Guide *guideTemp = NULL;
    do {
        printf("Numero du guide (0 si pas de guide, ex: visite libre): ");
        if (scanf("%d", &v.numeroGuide) != 1 || v.numeroGuide < 0) {
            printf("Saisie invalide. Veuillez entrer un entier positif ou 0.\n");
            while (getchar() != '\n');
            continue;
        }

        if (v.numeroGuide == 0) {
            break;
        }

        Guide *allGuides;
        int totalGuides = chargerGuides(&allGuides);
        if (totalGuides == 0 && allGuides == NULL) {
            printf("Aucun guide disponible dans le systeme.\n");
            v.numeroGuide = 0;
            break;
        }

        int guideFound = 0;
        for (int i = 0; i < totalGuides; i++) {
            if (allGuides[i].numero == v.numeroGuide) {
                guideTemp = &allGuides[i];
                guideFound = 1;
                break;
            }
        }

        if (!guideFound) {
            printf("Ce guide n'existe pas. Veuillez en choisir un existant ou entrer 0.\n");
        } else if (strcmp(guideTemp->statut, "non_disponible") == 0) {
            printf("Ce guide est non disponible. Veuillez en choisir un autre ou entrer 0.\n");
        } else {
            break;
        }
        free(allGuides);
    } while (1);
    while (getchar() != '\n');

    printf("Duree de la visite en minutes: ");
    do {
        if (scanf("%d", &v.duree) != 1 || v.duree <= 0) {
            printf("Saisie invalide. Veuillez entrer une duree positive.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);
    while (getchar() != '\n');

    ajouterVisiteFichier(v);
    printf("Visite enregistree avec succes! Montant a payer: %.2f FCFA\n", v.montantPaye);

    if (v.numeroGuide != 0 && guideTemp != NULL) {
        printf("Mise a jour du statut du guide (numero %d) a 'non_disponible'...\n", v.numeroGuide);
        mettreAJourStatutGuide(v.numeroGuide, "non_disponible");
    }
}

void afficherVisitesVisiteur() {
    printf("\n--- Afficher les visites d'un visiteur ---\n");
    int numVisiteur;
    printf("Entrez le numero du visiteur: ");
    if (scanf("%d", &numVisiteur) != 1 || numVisiteur <= 0) {
        printf("Saisie invalide. Veuillez entrer un entier positif.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    if (!visiteurExiste(numVisiteur)) {
        printf("Le visiteur avec le numero %d n'existe pas.\n", numVisiteur);
        return;
    }

    Visite *visites;
    int nbVisites = chargerVisites(&visites);
    if (visites == NULL) {
        printf("Aucune visite enregistree.\n");
        return;
    }

    Visiteur *allVisiteurs;
    int nbAllVisiteurs = chargerVisiteurs(&allVisiteurs);

    TypeVisite *allTypesVisites;
    int nbAllTypesVisites = chargerTypesVisites(&allTypesVisites);

    Guide *allGuides;
    int nbAllGuides = chargerGuides(&allGuides);


    printf("\nVisites pour le visiteur %d:\n", numVisiteur);
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("%-10s | %-12s | %-20s | %-10s | %-20s | %-10s | %-15s\n",
           "N Visite", "Date", "Type Visite", "Duree", "Guide", "Montant", "Nom Visiteur");
    printf("-----------------------------------------------------------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < nbVisites; i++) {
        if (visites[i].numeroVisiteur == numVisiteur) {
            found = 1;
            char nomVisiteur[100] = "Inconnu";
            for (int j = 0; j < nbAllVisiteurs; j++) {
                if (allVisiteurs[j].numero == visites[i].numeroVisiteur) {
                    sprintf(nomVisiteur, "%s %s", allVisiteurs[j].nom, allVisiteurs[j].prenom);
                    break;
                }
            }

            char libelleTypeVisite[50] = "Inconnu";
            for (int j = 0; j < nbAllTypesVisites; j++) {
                if (strcmp(allTypesVisites[j].code, visites[i].codeTypeVisite) == 0) {
                    strcpy(libelleTypeVisite, allTypesVisites[j].libelle);
                    break;
                }
            }

            char nomGuide[100] = "N/A";
            if (visites[i].numeroGuide != 0) {
                for (int j = 0; j < nbAllGuides; j++) {
                    if (allGuides[j].numero == visites[i].numeroGuide) {
                        sprintf(nomGuide, "%s %s", allGuides[j].nom, allGuides[j].prenom);
                        break;
                    }
                }
            }

            printf("%-10d | %-12s | %-20s | %-10d | %-20s | %-10.2f | %-15s\n",
                   visites[i].numeroVisite, visites[i].date, libelleTypeVisite,
                   visites[i].duree, nomGuide, visites[i].montantPaye, nomVisiteur);
        }
    }
    if (!found) {
        printf("Aucune visite trouvee pour ce visiteur.\n");
    }
    printf("-----------------------------------------------------------------------------------------------------------------\n");

    if (visites != NULL) free(visites);
    if (allVisiteurs != NULL) free(allVisiteurs);
    if (allTypesVisites != NULL) free(allTypesVisites);
    if (allGuides != NULL) free(allGuides);
}

void afficherGuidesDisponibles() {
    printf("\n--- Afficher les guides disponibles par langue ---\n");
    char langueCherchee[50];
    printf("Entrez la langue recherchee: ");
    lireLigne(langueCherchee, sizeof(langueCherchee)); // Utilise lireLigne de utils.h/c

    Guide *guides;
    int nbGuides = chargerGuides(&guides);
    if (guides == NULL) {
        printf("Aucun guide enregistre.\n");
        return;
    }

    printf("\nGuides disponibles parlant '%s':\n", langueCherchee);
    printf("----------------------------------------------------------------------\n");
    printf("%-10s | %-20s | %-20s | %-10s\n", "Numero", "Nom", "Prenom", "Langue");
    printf("----------------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < nbGuides; i++) {
        if (strcmp(guides[i].langue, langueCherchee) == 0 && strcmp(guides[i].statut, "disponible") == 0) {
            found = 1;
            printf("%-10d | %-20s | %-20s | %-10s\n",
                   guides[i].numero, guides[i].nom, guides[i].prenom, guides[i].langue);
        }
    }
    if (!found) {
        printf("Aucun guide disponible trouve pour cette langue.\n");
    }
    printf("----------------------------------------------------------------------\n");
    free(guides);
}

void afficherStatistiques() {
    printf("\n--- Statistiques globales ---\n");

    Visiteur *visiteurs;
    int nbVisiteurs = chargerVisiteurs(&visiteurs);
    printf("Nombre total de visiteurs uniques: %d\n", nbVisiteurs);
    if (visiteurs != NULL) free(visiteurs);

    Visite *visites;
    int nbVisites = chargerVisites(&visites);
    printf("Nombre de visites enregistrees: %d\n", nbVisites);

    float recettesTotales = 0.0;
    int dureeTotale = 0;
    int *sollicitationGuides = NULL;
    int maxGuideNum = 0;

    if (nbVisites > 0) {
        for (int i = 0; i < nbVisites; i++) {
            recettesTotales += visites[i].montantPaye;
            dureeTotale += visites[i].duree;
            if (visites[i].numeroGuide > maxGuideNum) {
                maxGuideNum = visites[i].numeroGuide;
            }
        }

        printf("Recettes totales generees: %.2f FCFA\n", recettesTotales);
        printf("Duree moyenne des visites: %.2f minutes\n", (float)dureeTotale / nbVisites);

        if (maxGuideNum > 0) {
            sollicitationGuides = (int *)calloc(maxGuideNum + 1, sizeof(int));
            if (sollicitationGuides == NULL) {
                printf("Erreur d'allocation memoire pour les statistiques de guide.\n");
            } else {
                for (int i = 0; i < nbVisites; i++) {
                    if (visites[i].numeroGuide > 0 && visites[i].numeroGuide <= maxGuideNum) {
                        sollicitationGuides[visites[i].numeroGuide]++;
                    }
                }

                int guideLePlusSollicite = -1;
                int maxSollicitations = -1;
                for (int i = 1; i <= maxGuideNum; i++) {
                    if (sollicitationGuides[i] > maxSollicitations) {
                        maxSollicitations = sollicitationGuides[i];
                        guideLePlusSollicite = i;
                    }
                }

                if (guideLePlusSollicite != -1) {
                    Guide *guides;
                    int nbG = chargerGuides(&guides);
                    char nomGuideSollicite[100] = "Inconnu";
                    if (guides != NULL) {
                        for (int i = 0; i < nbG; i++) {
                            if (guides[i].numero == guideLePlusSollicite) {
                                sprintf(nomGuideSollicite, "%s %s", guides[i].nom, guides[i].prenom);
                                break;
                            }
                        }
                        free(guides);
                    }
                    printf("Guide le plus sollicite: %s (Numero: %d, %d sollicitations)\n",
                           nomGuideSollicite, guideLePlusSollicite, maxSollicitations);
                } else {
                    printf("Aucun guide n'a ete sollicite pour des visites.\n");
                }
                free(sollicitationGuides);
            }
        } else {
             printf("Aucun guide n'a ete affecte a des visites.\n");
        }
    } else {
        printf("Aucune visite enregistree pour calculer les statistiques.\n");
    }

    if (visites != NULL) free(visites);
}
