#ifndef HANOI_H
#define HANOI_H

#include "authentification.h"

#define MAX_DISQUES 8

typedef struct {
    int colonnes[3][MAX_DISQUES]; // 3 piliers
    int sommets[3];               // Indice du prochain emplacement libre par pilier
    int nb_disques;
    int coups;
} Hanoi;

void play_hanoi(Player *current);

#endif