#include <stdio.h>
#include <stdlib.h>
#include "tic_tac_toe.h"
#include "authentification.h"
#include <windows.h>

/* Prototypes internes */
int ma_abs(int n);
void human_move(char board[BOARD_SIZE][BOARD_SIZE], char symbol);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE], int difficulty);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);
int count_pieces(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void sauvegarder_tictactoe(char board[3][3], char turn);
int charger_tictactoe(char board[3][3], char *turn);
void afficherPlateauTicTacToe(char board[3][3], char *joueur1, char *joueur2);


int ma_abs(int n) {
    return (n < 0) ? -n : n;
}

void sauvegarder_tictactoe(char board[3][3], char turn) {
    FILE *f = fopen("./Sauvegarde/tictactoe.plato", "wb");
    if (f != NULL) {
        fwrite(board, sizeof(char), 9, f);
        fwrite(&turn, sizeof(char), 1, f);
        fclose(f);
        printf("\n[Systeme] Partie sauvegarde automatiquement !");
    }
}

int charger_tictactoe(char board[3][3], char *turn) {
    FILE *f = fopen("./Sauvegarde/tictactoe.plato", "rb");
    if (f == NULL) return 0; // Pas de sauvegarde trouvée

    fread(board, sizeof(char), 9, f);
    fread(turn, sizeof(char), 1, f);
    fclose(f);
    return 1; // Chargement réussi
}

void afficherPlateauTicTacToe(char board[3][3], char *nomJ1, char *nomJ2) {
    // --- ACTIVER LES COULEURS SUR WINDOWS ---
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | 0x0004); 

    system("cls");

    
    printf("\n\t\t  ______________________________\n");
    printf("\t\t      %s VS %s\n", nomJ1, nomJ2);
    printf("\t\t  ______________________________\n\n");

    printf("\t\t       0     1     2\n"); 

    for (int i = 0; i < 3; i++) {
        printf("\t\t  %d ", i);

        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 'X') {
                // Style PION_VERT : Fond blanc (47), Texte vert (32)
                printf("\033[47m\033[32m  X  \033[0m"); 
            } else if (board[i][j] == 'O') {
                // Style PION_ROUGE : Fond blanc (47), Texte rouge (31)
                printf("\033[47m\033[31m  O  \033[0m");
            } else {
                // Case vide : Fond noir (40)
                printf("\033[40m     \033[0m");
            }
            
            if (j < 2) printf("|"); 
        }
        
        printf(" %d\n", i); 
        
        if (i < 2) {
            printf("\t\t    -----------------\n"); 
        }
    }
    printf("\t\t       0     1     2\n");
    printf("\t\t  ______________________________\n\n");
}void play_game(Player *current) {
    char board[3][3];
    char turn = PION_X; 
    int mode = 1; 
    char second_player_name[25] = "Ordinateur";
    int row, col, moves = 0, choice;
    int game_over = 0;

    system("cls");
    printf("\n=== TIC-TAC-TOE : CONFIGURATION ===");
    printf("\n1. Humain VS Machine");
    printf("\n2. Humain VS Humain");
    printf("\nChoix du mode : ");
    scanf("%d", &mode);
    while(getchar() != '\n'); // Nettoyer le tampon

    if (mode == 2) {
        printf("Entrez le nom du Joueur 2 (O) : ");
        scanf("%s", second_player_name);
        while(getchar() != '\n');
    }

    system("cls");
    printf("\n=== TIC-TAC-TOE : MENU PARTIE ===");
    printf("\n1. Nouvelle Partie");
    printf("\n2. Reprendre la partie sauvegardee");
    printf("\nChoix : ");
    scanf("%d", &choice);
    while(getchar() != '\n');

    // Utilisation de VIDE_TTT pour éviter le conflit avec Sudoku
    if (choice == 2 && charger_tictactoe(board, &turn)) {
        printf("\nPartie chargee !\n");
        moves = 0;
        for(int i=0; i<3; i++)
            for(int j=0; j<3; j++)
                if(board[i][j] != VIDE) moves++;
    } else {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = VIDE;
        turn = PION_X;
        moves = 0;
    }

    while (!game_over) {
        afficherPlateauTicTacToe(board, current->username, second_player_name);
        
        char *nom_actuel = (turn == PION_X) ? current->username : second_player_name;
        printf("\nC'est au tour de : %s (%c)\n", nom_actuel, turn);

        if (turn == PION_O && mode == 1) {
            printf("\nL'ordinateur reflechit...\n");
            Sleep(1000); 
            computer_move(board, 1);
            if (moves < 6) moves++; // IMPORTANT : On compte le placement de l'ordinateur
        } 
        else {
            if (moves < 6) {
                // PHASE 1 : PLACEMENT
                printf("\n%s, PLACEMENT (%d/6). Ligne Col (0-2) : ", nom_actuel, moves + 1);
                if (scanf("%d %d", &row, &col) != 2) {
                    while(getchar() != '\n');
                    continue;
                }

                if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == VIDE) {
                    board[row][col] = turn;
                    moves++;
                } else {
                    printf("\nCase invalide ou occupee !");
                    system("pause");
                    continue;
                }
            } 
            else {
                // PHASE 2 : DEPLACEMENT
                int r_old, c_old;
                printf("\n%s, DEPLACEMENT. Ligne Col du pion a bouger : ", nom_actuel);
                if (scanf("%d %d", &r_old, &c_old) != 2) {
                    while(getchar() != '\n');
                    continue;
                }

                if (r_old < 0 || r_old > 2 || c_old < 0 || c_old > 2 || board[r_old][c_old] != turn) {
                    printf("\nCe n'est pas votre pion !");
                    system("pause");
                    continue;
                }

                printf("Vers quelle case vide ADJACENTE (Ligne Col) ? : ");
                if (scanf("%d %d", &row, &col) != 2) {
                    while(getchar() != '\n');
                    continue;
                }

                int dist_r = ma_abs(row - r_old);
                int dist_c = ma_abs(col - c_old);

                if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == VIDE 
                    && dist_r <= 1 && dist_c <= 1) {
                    
                    board[r_old][c_old] = VIDE;
                    board[row][col] = turn;
                } else {
                    printf("\nMouvement interdit ! (Case vide voisine uniquement)");
                    system("pause");
                    continue;
                }
            }
        }

        if (check_win(board, turn)) {
            game_over = 1;
            afficherPlateauTicTacToe(board, current->username, second_player_name);
            printf("\nFELICITATIONS ! %s (%c) a gagne !\n", nom_actuel, turn);
            
            if (turn == PION_X) {
                current->score += 10;
                update_score(current);
                printf("Nouveau score de %s : %d\n", current->username, current->score);
            }
            remove("./Sauvegarde/tictactoe.plato");
        } else {
            turn = (turn == PION_X) ? PION_O : PION_X;
            sauvegarder_tictactoe(board, turn);
        }
    }
    printf("\nAppuyez sur Entree pour quitter...");
    while(getchar() != '\n'); getchar(); 
}
void human_move(char board[BOARD_SIZE][BOARD_SIZE], char symbol) {
    int r, c, r2, c2;
    if (count_pieces(board, symbol) < 3) {
        do {
            printf("\nJoueur %c (Ligne Col 1-3) : ", symbol);
            if (scanf("%d %d", &r, &c) != 2) {
                while(getchar() != '\n'); 
                continue;
            }
            r--; c--;
        } while (!is_valid_move(board, r, c));
        board[r][c] = symbol;
    } else {
        do {
            printf("\nDeplacer %c - De (L C) a (L C) : ", symbol);
            if (scanf("%d %d %d %d", &r, &c, &r2, &c2) != 4) {
                while(getchar() != '\n');
                continue;
            }
            r--; c--; r2--; c2--;
        } while (r<0 || r>2 || c<0 || c>2 || board[r][c] != symbol || !is_valid_move(board, r2, c2));
        board[r][c] = ' ';
        board[r2][c2] = symbol;
    }
}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE], int difficulty) {
    // Logique simplifiée : l'ordinateur place son pion sur la première case vide qu'il trouve
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == ' ') { 
                board[i][j] = PION_O; // Utilisation de PION_O au lieu de O
                return; 
            }
        }
    }
}

int count_pieces(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    int count = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == player) count++;
    return count;
}

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ');
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return 1;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return 1;
    }
    return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
           (board[2][0] == player && board[1][1] == player && board[0][2] == player);
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE], Player *current) {
    clear_screen();
    printf("Joueur : %s | Score : %d\n\n", current->username, current->score);
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
        if (i < 2) printf("\n---+---+---\n");
    }
    printf("\n");
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("cls");
#endif
}