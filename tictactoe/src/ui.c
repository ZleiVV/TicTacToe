#include "ui.h"
#include <ncurses.h>

// Affichage du tableau de jeu
void draw_board(GameState *game_state) {
    clear();
    // Affichage du tableau de 3x3 avec ncurses
    // Affichage des scores
    refresh();
}

// Fonction pour obtenir le choix du joueur (Joueur contre Joueur, Joueur contre Machine, etc.)
int get_player_move() {
    int choice;
    // Affichage d'un menu pour le joueur
    // Utilisation de ncurses pour gérer les entrées clavier
    return choice;
}
