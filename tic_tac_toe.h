#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include "authentification.h"
#define DATA_FILE "players.dat"


#define BOARD_SIZE 3
#define PION_X 'X'
#define PION_O 'O'
#define VIDE ' '

void play_game(Player *current);
void print_board(char board[BOARD_SIZE][BOARD_SIZE], Player *current);
void clear_screen();

#endif
