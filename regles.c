#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // Nécessaire pour getch()
#include "regles.h"

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
        printf("\n\t\t4. Tour de hanoi");
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
                printf("\n- La Dame peut se deplacer de plusieurs cases en diagonale.");
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
            case 4:
                printf("\n--- REGLES DE LA TOUR DE HANOI ---");
                printf("\n- But : Deplacer tous les disques du pilier 1 vers le pilier 3.");
                printf("\n- Vous ne pouvez deplacer qu'UN SEUL disque a la fois.");
                printf("\n- Un disque ne peut etre place que sur un emplacement vide");
                printf("\n  OU sur un disque plus GRAND que lui.");
                printf("\n- INTERDICTION de placer un gros disque sur un petit disque.");
                printf("\n- Astuce : Le nombre minimum de coups est 2^n - 1 (n = nb disques).");
                break;
            default:
                break;
        } // Fin du switch

        if (choix != 0) {
            printf("\n\nAppuyez sur une touche pour revenir au menu des regles...");
            getch();
        }
    } while (choix != 0); // Fin du do-while
    
    system("cls");
}