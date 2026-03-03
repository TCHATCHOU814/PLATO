#include <stdio.h>
#include <string.h>
#include "authentification.h"
#define DATA_FILE "players.dat"


void register_player() {
    FILE *file = fopen(DATA_FILE, "ab+");
    if (!file) {
        printf("\nUnable to open file!");
        return;
    }

    Player p;
    printf("\nEnter username: ");
    scanf("%49s", p.username);
    printf("Enter password: ");
    scanf("%49s", p.password);
    p.score = 0;
printf("DEBUG: enregistre %s / %s\n", p.username, p.password);

    fwrite(&p, sizeof(Player), 1, file);
    fclose(file);
    printf("\nRegistration successful!");
}

int login_player(Player *current) {
    FILE *file = fopen(DATA_FILE, "rb");
    if (!file) {
        printf("\nNo users found. Please register first.");
        return 0;
    }

    char user[50], pass[50];
    Player temp;

    printf("\nUsername: ");
    scanf("%49s", user);
    printf("Password: ");
    scanf("%49s", pass);

    while (fread(&temp, sizeof(Player), 1, file)) {
        if (strcmp(temp.username, user) == 0 &&
            strcmp(temp.password, pass) == 0) {
            *current = temp;
            fclose(file);
            printf("\nLogin successful. Welcome %s!", current->username);
            return 1;
        }
    }

    fclose(file);
    printf("\nInvalid username or password.");
    return 0;
}

void show_score(Player *current) {
    printf("\nPlayer: %s", current->username);
    printf("\nScore: %d\n", current->score);
}

void logout() {
    printf("\nYou have been logged out.");
}

void update_score(Player *current) {
    FILE *file = fopen(DATA_FILE, "rb+");
    if (!file) return;

    Player temp;
    while (fread(&temp, sizeof(Player), 1, file)) {
        if (strcmp(temp.username, current->username) == 0) {
            fseek(file, -(long)sizeof(Player), SEEK_CUR);
            fwrite(current, sizeof(Player), 1, file);
            break;
        }
    }
    fclose(file);
}
