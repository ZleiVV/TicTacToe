#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "game.h"
#include "ui.h"
#include "history.h"
#include "ai.h"

int main() {
    // Initialisation de ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Déclaration des variables pour le jeu
    int game_over = 0;
    int player_choice;
    GameState game_state;
    initialize_game(&game_state);

    // Affichage de l'interface
    while (!game_over) {
        draw_board(&game_state);
        player_choice = get_player_move();

        // Mise à jour de l'état du jeu
        if (player_choice == 1) { // Joueur contre Joueur
            game_over = play_game(&game_state);
        } else if (player_choice == 2) { // Joueur contre Machine
            game_over = play_game_vs_ai(&game_state);
        } else if (player_choice == 3) { // Machine contre Machine
            game_over = play_game_ai_vs_ai(&game_state);
        }

        // Historique des parties
        save_game_history(&game_state);
    }

    // Fin de l'application
    endwin();
    return 0;
}
