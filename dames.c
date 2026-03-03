#include <stdio.h>
#include <stdlib.h>
#include "dame.h"
#include "affichage.h"
#include "structure.h"
#include "authentification.h"

void jouer_dames(Player *current) {
    int choix = 1; // On force le choix à 1 pour lancer "Nouvelle Partie"
    int option = 1; // Niveau facile par défaut
    Damier *damier = NULL;

    // NETTOYAGE DU CLAVIER
    while (getchar() != '\n' && getchar() != EOF); 

    damier = creerDamier();
    if (damier == NULL) return;

    printf("\n--- PREPARATION DU PLATEAU POUR %s ---\n", current->username);

    // On appelle directement la fonction qui gère le jeu
    // sans passer par le menu interne des dames
    nouvellePartie(damier, option, &choix);

    // MISE A JOUR DU SCORE
    current->score += 20; 
    update_score(current);

    printf("\nPartie terminee ! Score enregistre : %d\n", current->score);
    printf("Appuyez sur Entree pour revenir au Plato...");
    while (getchar() != '\n'); 
}