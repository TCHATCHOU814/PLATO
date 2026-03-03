#include <stdio.h>
#include <stdlib.h>

void afficherREADME() {
    int choix;
    do {
        system("cls");
        printf("\n\t\t========================================");
        printf("\n\t\t       REGLES DES JEUX - PLATO");
        printf("\n\t\t========================================");
        printf("\n\t\t1. Les Dames");
        printf("\n\t\t2. Tic-Tac-Toe (Morpion)");
        printf("\n\t\t3. Sudoku");
        printf("\n\t\t0. Retour au menu principal");
        printf("\n\t\tChoix : ");
        scanf("%d", &choix);

        system("cls");
        switch(choix) {
            case 1:
                printf("\n--- REGLES DES DAMES ---");
                printf("\n- Les pions se deplacent en diagonale sur les cases noires.");
                printf("\n- Pour prendre un pion adverse, il faut sauter par-dessus.");
                printf("\n- Un pion qui atteint la derniere ligne devient une DAME.");
                printf("\n- La Dame peut se deplacer de plusieurs cases en diagonale selon la quantité de bouffe.");
                break;
            case 2:
                printf("\n--- REGLES DU TIC-TAC-TOE ---");
                printf("\n- Phase 1 (Placement) : Posez vos 3 pions chacun tour a tour.");
                printf("\n- Phase 2 (Deplacement) : Deplacez un de vos pions vers une case");
                printf("\n  voisine vide (horizontale, verticale ou diagonale).");
                printf("\n- But : Aligner 3 pions pour gagner.");
                break;
            case 3:
                printf("\n--- REGLES DU SUDOKU ---");
                printf("\n- Remplissez la grille avec des chiffres de 1 a 9.");
                printf("\n- Chaque chiffre ne doit apparaitre qu'une seule fois par :");
                printf("\n  Ligne, Colonne et Carre de 3x3 cases.");
                printf("\n- Utilisez ZQSD pour naviguer et les touches 1-9 pour remplir.");
                printf("\n- Appuyez sur C pour voir le corriger.");
                break;
        }
        if (choix != 0) {
            printf("\n\nAppuyez sur une touche pour revenir au menu des regles...");
            getch();
        }
    } while (choix != 0);
    system("cls");
}