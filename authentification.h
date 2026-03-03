#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H

#define DATA_FILE "players.dat"

typedef struct {
    char username[50];
    char password[50];
    int score;
} Player;

void register_player();
int login_player(Player *current);
void show_score(Player *current);
void logout();
void update_score(Player *current);

#endif
