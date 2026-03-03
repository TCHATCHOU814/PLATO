#include <stdio.h>
#include <stdlib.h>
#include "authentification.h"
#include "dame.h"
#include "tic_tac_toe.h"
#include "sudoku.h"
#include "regles.h"

int main() {
    Player current_player;
    int logged_in = 0; 
    int choice;

    while (1) {
        printf("\n========================");
        printf("\n    MENU PRINCIPAL");
        printf("\n    Statut : %s", logged_in ? "CONNECTE" : "DECONNECTE");
        printf("\n========================");
        printf("\n1. S'inscrire");
        printf("\n2. Se connecter");
        printf("\n3. JOUER au TicTacToe");
        printf("\n4. JOUER au Dames");
        printf("\n5. JOUER au Sudoku");
        printf("\n6. LIRE LES REGLES (README)");
        printf("\n7. Voir Score");
        printf("\n8. Se deconnecter");
        printf("\n9. Quitter");
        printf("\nChoix : ");

        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); 
            continue;
        }
        while(getchar() != '\n'); 

        switch (choice) {
            case 1:
                register_player();
                break;
            case 2:
                // On s'assure que la valeur retourne est bien stocke
                logged_in = login_player(&current_player);
                if (logged_in) {
                    printf("\nSucces ! Bonjour %s.", current_player.username);
                }
                break;
            case 3:
                if (logged_in == 1) {
                    play_game(&current_player);
                } else {
                    printf("\n[!] Erreur : Vous devez vous connecter (Option 2)");
                }
                break;
case 4:
    if (logged_in == 1) {
        jouer_dames(&current_player);
    } else {
        printf("\nConnectez-vous d'abord !");
    }
    break;
    case 5: // Si 3 est le Sudoku
    play_sudoku(&current_player);
    break;

    case 6:
    afficherREADME();
    break;
                case 7:
                if (logged_in == 1) show_score(&current_player);
                else printf("\n[!] Erreur : Connectez-vous d'abord.");
                break;
                // Dans ton switch(choice)
            case 8:
                logged_in = 0;
                logout();
                break;
            case 9:
                printf("\nAu revoir !\n");
                return 0;
            default:
                printf("\nChoix invalide.");
        }
    }
    return 0;
}