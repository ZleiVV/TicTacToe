#include "game.h"
#include <stdio.h>

// Initialisation du jeu
void initialize_game(GameState *game_state) {
    // Remplir l'état initial du jeu (ex : tableau vide, scores à zéro)
    for (int i = 0; i < 9; i++) {
        game_state->board[i] = ' ';
    }
    game_state->player_score = 0;
    game_state->computer_score = 0;
}

// Vérification d'une victoire
int check_winner(GameState *game_state) {
    // Code pour vérifier les combinaisons gagnantes
    // Retourne 1 si un joueur a gagné, 0 sinon
}

// Fonction pour jouer un tour
int play_game(GameState *game_state) {
    // Implémenter la gestion des tours pour un joueur contre un joueur
    // Appeler les fonctions qui permettent de jouer à tour de rôle
}
