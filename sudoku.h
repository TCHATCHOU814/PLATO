#ifndef SUDOKU_H
#define SUDOKU_H

#include "authentification.h"

#define TAILLE 9
#define VIDE_SUDOKU 0

typedef struct {
    int grille[TAILLE][TAILLE];   // La grille que le joueur modifie
    int solution[TAILLE][TAILLE]; // La solution complète
    int masque[TAILLE][TAILLE];   // 1 si chiffre d'origine (fixe), 0 si modifiable
    int curseurL;                // Position ligne du curseur
    int curseurC;                // Position colonne du curseur
} Sudoku;

void play_sudoku(Player *current);

#endif