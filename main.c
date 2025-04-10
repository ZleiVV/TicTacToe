#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // Pour utiliser la fonction rand()

#define TAILLE 3

char grille[TAILLE][TAILLE];
int score_joueur1 = 0, score_joueur2 = 0;
int mode_jeu = 0;

typedef struct {
    char joueur;
    int ligne;
    int col;
} Coup;

Coup historique[9]; // Maximum 9 coups
int nb_coups = 0;  // Compteur de coups

void init_curses() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
}

void cleanup_curses() {
    endwin();
}

void reset_grille() {
    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            grille[i][j] = ' ';
}

void afficher_grille() {
    clear();
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            mvprintw(i * 2, j * 4, "%c", grille[i][j]);
            if (j < 2) mvprintw(i * 2, j * 4 + 2, "|");
        }
        if (i < 2) mvprintw(i * 2 + 1, 0, "-----");
    }
    mvprintw(8, 0, "Score Joueur 1 (X) : %d | Score Joueur 2 (O) : %d", score_joueur1, score_joueur2);
    refresh();
}

int verifier_victoire() {
    for (int i = 0; i < TAILLE; i++) {
        if (grille[i][0] != ' ' && grille[i][0] == grille[i][1] && grille[i][1] == grille[i][2])
            return (grille[i][0] == 'X') ? 1 : -1;
        if (grille[0][i] != ' ' && grille[0][i] == grille[1][i] && grille[1][i] == grille[2][i])
            return (grille[0][i] == 'X') ? 1 : -1;
    }
    if (grille[0][0] != ' ' && grille[0][0] == grille[1][1] && grille[1][1] == grille[2][2])
        return (grille[0][0] == 'X') ? 1 : -1;
    if (grille[0][2] != ' ' && grille[0][2] == grille[1][1] && grille[1][1] == grille[2][0])
        return (grille[0][2] == 'X') ? 1 : -1;
    return 0;
}

void jouer_tour(char joueur) {
    int ligne, col, valide = 0;
    while (!valide) {
        mvprintw(10, 0, "Tour de %c. Choisissez une ligne (0-2): ", joueur);
        refresh();
        ligne = wgetch(stdscr) - '0';

        mvprintw(11, 0, "Choisissez une colonne (0-2): ");
        refresh();
        col = wgetch(stdscr) - '0';

        if (ligne >= 0 && ligne < TAILLE && col >= 0 && col < TAILLE && grille[ligne][col] == ' ') {
            grille[ligne][col] = joueur;
            historique[nb_coups].joueur = joueur;
            historique[nb_coups].ligne = ligne;
            historique[nb_coups].col = col;
            nb_coups++;
            valide = 1;
        } else {
            mvprintw(12, 0, "Mouvement invalide ! Essayez encore.");
            refresh();
            napms(1000);
            mvprintw(12, 0, "                                    ");
        }
    }
}

void init_random() {
    srand(time(NULL));  // Initialisation de la seed aléatoire
}

int minimax(int profondeur, int maximiser) {
    int resultat = verifier_victoire();
    if (resultat == 1) return -1;
    if (resultat == -1) return 1;
    if (profondeur == 9) return 0;

    int meilleur_score = maximiser ? -1000 : 1000;
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (grille[i][j] == ' ') {
                grille[i][j] = maximiser ? 'O' : 'X';
                int score = minimax(profondeur + 1, !maximiser);
                grille[i][j] = ' ';

                if (maximiser) {
                    if (score > meilleur_score) {
                        meilleur_score = score;
                    } else if (score == meilleur_score) {
                        if (rand() % 2 == 0) {
                            meilleur_score = score;
                        }
                    }
                } else {
                    if (score < meilleur_score) {
                        meilleur_score = score;
                    } else if (score == meilleur_score) {
                        if (rand() % 2 == 0) {
                            meilleur_score = score;
                        }
                    }
                }
            }
        }
    }
    return meilleur_score;
}

void jouer_ia(char ia) {
    int meilleur_score = -1000, ligne = -1, col = -1;
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (grille[i][j] == ' ') {
                grille[i][j] = ia;
                int score = minimax(0, ia == 'O');
                grille[i][j] = ' ';
                if (score > meilleur_score) {
                    meilleur_score = score;
                    ligne = i;
                    col = j;
                } else if (score == meilleur_score) {
                    if (rand() % 2 == 0) {
                        ligne = i;
                        col = j;
                    }
                }
            }
        }
    }
    grille[ligne][col] = ia;
}

void revisionner_partie() {
    reset_grille();
    for (int i = 0; i < nb_coups; i++) {
        afficher_grille();
        grille[historique[i].ligne][historique[i].col] = historique[i].joueur;
        mvprintw(10, 0, "Tour %d: Joueur %c joue en [%d, %d]", i + 1, historique[i].joueur, historique[i].ligne, historique[i].col);
        refresh();
        napms(1000);  // Attendre 1 seconde avant de montrer le coup suivant
    }
    getch();  // Attendre que l'utilisateur appuie sur une touche pour revenir au menu
}

void jouer_partie() {
    char joueur = 'X';
    int fin = 0, tours = 0;

    reset_grille();
    while (!fin && tours < 9) {
        afficher_grille();

        if (mode_jeu == 1 || (mode_jeu == 2 && joueur == 'X')) {
            jouer_tour(joueur);
        } else {
            jouer_ia(joueur);
            napms(500);
        }

        int resultat = verifier_victoire();
        if (resultat == 1) {
            afficher_grille();
            mvprintw(10, 0, "Le joueur X gagne !");
            score_joueur1++;
            fin = 1;
        } else if (resultat == -1) {
            afficher_grille();
            mvprintw(10, 0, "Le joueur O gagne !");
            score_joueur2++;
            fin = 1;
        }

        joueur = (joueur == 'X') ? 'O' : 'X';
        tours++;
    }

    if (!fin) {
        mvprintw(10, 0, "Match nul!");
    }

    refresh();
    getch();
}

void afficher_scores() {
    clear();
    mvprintw(4, 0, "Scores actuels :");
    mvprintw(6, 0, "Joueur 1 (X) : %d", score_joueur1);
    mvprintw(7, 0, "Joueur 2 (O) : %d", score_joueur2);
    mvprintw(9, 0, "Appuyez sur une touche pour revenir au menu.");
    refresh();
    getch();
}

void reset_jeu() {
    score_joueur1 = 0;
    score_joueur2 = 0;
    nb_coups = 0;  // Réinitialiser le nombre de coups enregistrés
    mvprintw(10, 0, "Scores réinitialisés.");
    refresh();
    getch();
}

int main() {
    init_curses();
    init_random();  // Initialisation du générateur de nombres aléatoires
    int choix = 0;

    while (1) {
        clear();
        mvprintw(2, 0, "Tic-Tac-Toe");
        mvprintw(4, 0, "1. Joueur vs Joueur");
        mvprintw(5, 0, "2. Joueur vs IA");
        mvprintw(6, 0, "3. IA vs IA");
        mvprintw(7, 0, "4. Voir les scores");
        mvprintw(8, 0, "5. Réinitialiser scores");
        mvprintw(9, 0, "6. Revisionner la dernière partie");
        mvprintw(10, 0, "7. Quitter");
        mvprintw(12, 0, "Choisissez une option (1-7): ");
        refresh();

        choix = wgetch(stdscr) - '0';

        if (choix == 7) break;
        else if (choix == 6) revisionner_partie();
        else if (choix == 5) reset_jeu();
        else if (choix == 4) afficher_scores();
        else if (choix == 1 || choix == 2 || choix == 3) {
            mode_jeu = choix;
            jouer_partie();
        }
    }

    cleanup_curses();
    return 0;
}
