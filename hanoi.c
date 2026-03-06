#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "hanoi.h"

// Initialise le jeu : tous les disques sur le pilier 0
void init_hanoi(Hanoi *h, int n) {
    h->nb_disques = n;
    h->coups = 0;
    for (int i = 0; i < 3; i++) h->sommets[i] = 0;

    for (int i = n; i > 0; i--) {
        h->colonnes[0][h->sommets[0]++] = i;
    }
}

// Affiche les tours de manière graphique
void afficher_hanoi(Hanoi *h, Player *p) {
    system("cls");
    printf("\n\t[ TOUR DE HANOI ] - Joueur: %s", p->username);
    printf("\n\tObjectif: Deplacer tout vers la droite. Coups: %d\n\n", h->coups);

    for (int i = h->nb_disques - 1; i >= 0; i--) {
        printf("\t");
        for (int j = 0; j < 3; j++) {
            if (i < h->sommets[j]) {
                printf("  [%d]  ", h->colonnes[j][i]);
            } else {
                printf("   |   ");
            }
        }
        printf("\n");
    }
    printf("\t -----   -----   -----\n");
    printf("\t ( 1 )   ( 2 )   ( 3 )\n");
    printf("\n\tAppuyez sur '0' pour quitter.");
}

int deplacer_disque(Hanoi *h, int de, int vers) {
    if (de < 0 || de > 2 || vers < 0 || vers > 2) return 0;
    if (h->sommets[de] == 0) return 0; // Tour source vide

    int disque_a_deplacer = h->colonnes[de][h->sommets[de] - 1];

    // Vérifier si le déplacement est valide (petit sur grand)
    if (h->sommets[vers] > 0) {
        if (h->colonnes[vers][h->sommets[vers] - 1] < disque_a_deplacer) {
            return 0; // Interdit
        }
    }

    // Effectuer le déplacement
    h->sommets[de]--;
    h->colonnes[vers][h->sommets[vers]++] = disque_a_deplacer;
    h->coups++;
    return 1;
}

void play_hanoi(Player *current) {
    Hanoi h;
    int n, de, vers;

    system("cls");
    printf("\n=== TOUR DE HANOI ===");
    printf("\nNombre de disques (3-8) : ");
    scanf("%d", &n);
    if (n < 3) n = 3;
    if (n > MAX_DISQUES) n = MAX_DISQUES;

    init_hanoi(&h, n);

    while (1) {
        afficher_hanoi(&h, current);

        // Victoire
        if (h.sommets[2] == n) {
            printf("\nBRAVO ! Vous avez gagne en %d coups !\n", h.coups);
            current->score += (10 + (MAX_DISQUES - n));
            update_score(current);
            getch();
            break;
        }

        printf("\nDeplacer de (1-3) vers (1-3) [Ex: 1 3] : ");
        if (scanf("%d %d", &de, &vers) != 2) {
            // Gestion sortie ou erreur
            char c = getch();
            if (c == '0') break;
            continue;
        }

        if (!deplacer_disque(&h, de - 1, vers - 1)) {
            printf("\nMouvement invalide !");
            getch();
        }
    }
    system("cls");
}