#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "sudoku.h"
#include "authentification.h"


int est_valide(int grille[9][9], int ligne, int col, int val);
int resoudre_sudoku(int grille[9][9], int ligne, int col);
void generer_partie(Sudoku *s, int difficulte);
void afficher_grille(Sudoku *s, Player *p);
void play_sudoku(Player *current);


int est_valide(int grille[9][9], int ligne, int col, int val) {
    for (int i = 0; i < 9; i++) {
        if (grille[ligne][i] == val || grille[i][col] == val) return 0;
    }
    // Vérification du carré 3x3
    int debutL = ligne - ligne % 3;
    int debutC = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grille[i + debutL][j + debutC] == val) return 0;
        }
    }
    return 1;
}

int resoudre_sudoku(int grille[9][9], int ligne, int col) {
    if (col == 9) {
        if (ligne == 8) return 1;
        ligne++; col = 0;
    }
    if (grille[ligne][col] != 0) return resoudre_sudoku(grille, ligne, col + 1);

    for (int num = 1; num <= 9; num++) {
        if (est_valide(grille, ligne, col, num)) {
            grille[ligne][col] = num;
            if (resoudre_sudoku(grille, ligne, col + 1)) return 1;
            grille[ligne][col] = 0;
        }
    }
    return 0;
}

// --- GÉNÉRATION DE LA PARTIE ---

void generer_partie(Sudoku *s, int difficulte) {
    srand(time(NULL));
    // 1. Vider la grille
    for(int i=0; i<9; i++) 
        for(int j=0; j<9; j++) s->grille[i][j] = 0;

    // 2. Remplir la diagonale pour aider le solveur à créer une grille unique
    for (int i = 0; i < 9; i += 3) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                int num;
                do { num = rand() % 9 + 1; } while (!est_valide(s->grille, i+row, i+col, num));
                s->grille[i+row][i+col] = num;
            }
        }
    }

    // 3. Résoudre complètement pour avoir la solution
    resoudre_sudoku(s->grille, 0, 0);
    for(int i=0; i<9; i++) 
        for(int j=0; j<9; j++) s->solution[i][j] = s->grille[i][j];

    // 4. Retirer des chiffres selon la difficulté
    int a_retirer = (difficulte == 1) ? 30 : (difficulte == 2) ? 45 : 60;
    while (a_retirer > 0) {
        int r = rand() % 9;
        int c = rand() % 9;
        if (s->grille[r][c] != 0) {
            s->grille[r][c] = 0;
            s->masque[r][c] = 0; // Case modifiable
            a_retirer--;
        }
    }
    // Verrouiller les cases restantes
    for(int i=0; i<9; i++) 
        for(int j=0; j<9; j++) 
            if(s->grille[i][j] != 0) s->masque[i][j] = 1;
}

// --- AFFICHAGE ---

void afficher_grille(Sudoku *s, Player *p) {
    system("cls");
    printf("\n\t[ SUDOKU - PLATO ]  Joueur: %s", p->username);
    printf("\n\tZ,Q,S,D: Bouger | 1-9: Chiffre | C: Corriger | 0: Quitter\n\n");

    printf("\t    0 1 2   3 4 5   6 7 8\n");
    printf("\t  +-------+-------+-------+\n");

    for (int i = 0; i < 9; i++) {
        if (i > 0 && i % 3 == 0) printf("\t  |-------+-------+-------|\n");
        printf("\t%d | ", i);
        for (int j = 0; j < 9; j++) {
            if (j > 0 && j % 3 == 0) printf("| ");

            // Couleurs
            if (i == s->curseurL && j == s->curseurC) 
                printf("\033[42m"); // Fond Vert (Curseur)
            else if (s->masque[i][j] == 1) 
                printf("\033[47m\033[30m"); // Fond Blanc (Chiffre fixe)
            else 
                printf("\033[36m"); // Cyan (Chiffre joueur)

            if (s->grille[i][j] == 0) printf(". ");
            else printf("%d ", s->grille[i][j]);
            
            printf("\033[0m"); // Reset
        }
        printf("|\n");
    }
    printf("\t  +-------+-------+-------+\n");
}

// --- BOUCLE DE JEU PRINCIPALE ---

void play_sudoku(Player *current) {
    Sudoku s;
    s.curseurL = 0; s.curseurC = 0;
    int diff;

    // Menu difficulté
    system("cls");
    printf("\n=== NIVEAU DE DIFFICULTE ===\n");
    printf("1. Facile (30 vides)\n2. Moyen  (45 vides)\n3. Difficile (60 vides)\nChoix : ");
    scanf("%d", &diff);
    if(diff < 1 || diff > 3) diff = 1;

    generer_partie(&s, diff);

    char ch;
    while (1) {
        afficher_grille(&s, current);
        ch = getch(); // Lecture de touche sans Entrée

        if (ch == '0'){
          system("cls");
          break;
        }  // Quitter
        
        // Déplacements
        if (ch == 'z' || ch == 'Z') if (s.curseurL > 0) s.curseurL--;
        if (ch == 's' || ch == 'S') if (s.curseurL < 8) s.curseurL++;
        if (ch == 'q' || ch == 'Q') if (s.curseurC > 0) s.curseurC--;
        if (ch == 'd' || ch == 'D') if (s.curseurC < 8) s.curseurC++;

        // Saisie chiffre
        if (ch >= '1' && ch <= '9') {
            if (s.masque[s.curseurL][s.curseurC] == 0) {
                s.grille[s.curseurL][s.curseurC] = ch - '0';
            }
        }
        // Effacer
        if (ch == ' ' || ch == 8) { // Espace ou Backspace
            if (s.masque[s.curseurL][s.curseurC] == 0) s.grille[s.curseurL][s.curseurC] = 0;
        }

        // Corriger (Solution)
        if (ch == 'c' || ch == 'C') {
            for(int i=0; i<9; i++) 
                for(int j=0; j<9; j++) s.grille[i][j] = s.solution[i][j];
            afficher_grille(&s, current);
            printf("\n[CORRIGE] Voici la solution. Appuyez sur une touche...");
            getch();
            break;
        }
    }
}