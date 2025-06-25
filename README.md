# Groupe 4 TP de Langage C
## Project numéro 13 Gestion d’un site touristique
****

Concevoir un programme en langage C permettant de gérer les principales
opérations liées à un site touristique. Le système devra permettre d’enregistrer les
visiteurs, les guides touristiques, les types de visites, les visites effectuées, ainsi que de
suivre les recettes générées et les statistiques de fréquentation.
Le programme devra utiliser les fichiers suivants pour enregistrer les données :
• visiteurs.txt : contient les informations sur les visiteurs (numéro, nom, prénom,
nationalité, contact)
• guides.txt : contient les informations sur les guides (numéro, nom, prénom,
langue parlée, statut : disponible ou non)
• tarifs.txt : contient les types de visites proposées (code, libellé, tarif en FCFA)
• visites.txt : enregistre les visites effectuées (numéro de la visite, date, numéro du
visiteur, code du type de visite, numéro du guide, durée, montant payé)
Le programme devra afficher un menu interactif permettant d’exécuter les opérations
suivantes :
- [ ] 1. Ajouter un visiteur : Saisie du numéro, nom, prénom, nationalité, contact. Les
         données sont enregistrées dans visiteurs.txt.
- [ ] 2. Ajouter un guide touristique : Saisie du numéro, nom, prénom, langue parlée,
         statut. Enregistrement dans guides.txt.
- [ ] 3. Ajouter un type de visite : Saisie du code, libellé (ex. : “visite libre”, “visite
         guidée”, “scolaire”) et du tarif. Enregistrement dans tarifs.txt.
- [ ] 4. Enregistrer une visite : Saisie du numéro de visite, date, numéro du visiteur, type
         de visite, numéro du guide, durée. Le montant à payer est calculé
         automatiquement selon le tarif. La visite est enregistrée dans visites.txt.
- [ ] 5. Afficher les visites d’un visiteur donné : Affichage de toutes les visites effectuées
         par ce visiteur, avec les détails (date, type, durée, guide, montant payé).
- [ ] 6. Afficher les guides disponibles selon une langue donnée : Recherche et
         affichage de tous les guides parlant la langue spécifiée et disponibles.
- [ ] 7. Afficher les statistiques globales : Nombre total de visiteurs, nombre de visites
         enregistrées, recettes totales générées, durée moyenne des visites, guide le
         plus sollicité.
         Le programme devra utiliser des structures (struct) pour représenter les visiteurs, guides,
         types de visites et visites. Toutes les informations doivent être stockées dans des fichiers
         texte, avec des fonctions distinctes pour chaque opération. Le système doit aussi
         assurer la cohérence des données (ex. : un guide indisponible ne peut être affecté à
         une visite).
****
# Plan de Travail
****
...
