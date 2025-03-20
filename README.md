# Tic-Tac-Toe en C avec ncurses

## Description
Ce projet implémente un jeu de Tic-Tac-Toe en C avec une interface en mode texte en utilisant la bibliothèque `ncurses`. Le jeu permet de jouer dans plusieurs modes :
- Joueur contre Joueur
- Joueur contre Machine
- Machine contre Machine (avec une IA utilisant l'algorithme Minimax).

Le jeu permet également de gérer les scores et l'historique des parties. Le tout est développé avec une interface utilisateur en mode texte permettant de jouer facilement dans un terminal.

## Fonctionnalités
- **Interface utilisateur en mode texte** avec `ncurses`.
- **Modes de jeu** :
  - Joueur contre Joueur.
  - Joueur contre Machine (l'IA utilise l'algorithme Minimax pour prendre des décisions).
  - Machine contre Machine.
- **Gestion des scores** : Suivi des scores des joueurs.
- **Historique des parties** : Enregistrement de l'historique des parties jouées.
- **Réinitialisation du jeu** : Réinitialisation des scores et des parties.

## Prérequis
- Compiler avec `gcc` (ou tout autre compilateur compatible C).
- La bibliothèque `ncurses` doit être installée sur votre machine.

## Installation

### Cloner le repository
```bash
git clone https://github.com/ZleiVV/tictactoe.git
cd tictactoe
