#include "../include/GameEngine.h"
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cctype>
#include <iomanip>
#include <ncurses.h>

// Nouveau constructeur avec niveau
GameEngine::GameEngine(int width, int height, int niveau)
    : labyrinthe(width, height), joueur(1, 1), gameOver(false),
      score(0), niveauActuel(niveau), victoire(false) {
    labyrinthe.generer();
}

void GameEngine::update() {
    if (joueur.isGameOver()) {
        gameOver = true;
        return;
    }

    if (!victoire) {
        auto sortie = labyrinthe.getSortie();
        if (joueur.getX() == sortie.first && joueur.getY() == sortie.second) {
            victoire = true;
            score += 100 * niveauActuel;
        }
    }
}

void GameEngine::render() {
    clear();

    if (victoire) {
        printw("\n\n ╔════════════════════════════╗\n");
        printw("        FÉLICITATIONS !           \n");
        printw("        Vous avez réussi          \n");
        printw("     ╠════════════════════════════╣\n");
        printw("        Score: %10d       \n", score);
        printw("        Niveau: %8d       \n", niveauActuel);
        printw("     ╚════════════════════════════╝\n\n");
        printw("    ► [N]iveau suivant\n");
        printw("    ► [Q]uitter\n\n");
        printw("  Sélection: ");
        refresh();
        return;
    }

    if (gameOver) {
        printw("\n\n  ╔════════════════════════════╗\n");
        printw("             GAME OVER!           \n");
        printw("       Trop de collisions         \n");
        printw("      ╠════════════════════════════╣\n");
        printw("        Score: %10d      \n", score);
        printw("        Niveau: %8d       \n", niveauActuel);
        printw("      ╚════════════════════════════╝\n\n");
        printw("    ► [R]ecommencer\n");
        printw("    ► [Q]uitter\n\n");
        printw("  Sélection: ");
        refresh();
        return;
    }

    // Affichage du labyrinthe
    for (int y = 0; y < labyrinthe.getHauteur(); ++y) {
        for (int x = 0; x < labyrinthe.getLargeur(); ++x) {
            if (joueur.getX() == x && joueur.getY() == y) {
                if (joueur.getCollisionsCount() > 0) {
                    attron(COLOR_PAIR(2));
                    printw("P");
                    attroff(COLOR_PAIR(2));
                } else {
                    attron(COLOR_PAIR(1));
                    printw("P");
                    attroff(COLOR_PAIR(1));
                }
            }
            else if (x == labyrinthe.getSortie().first && y == labyrinthe.getSortie().second) {
                attron(COLOR_PAIR(3));
                printw("S");
                attroff(COLOR_PAIR(3));
            }
            else if (labyrinthe.estMur(x, y)) {
                attron(COLOR_PAIR(4));
                printw("#");
                attroff(COLOR_PAIR(4));
            }
            else {
                printw(" ");
            }
        }
        printw("\n");
    }

    // Informations du jeu
    printw("\nContrôles: Z (haut), Q (gauche), S (bas), D (droite), X (quitter)\n");
	printw("Niveau: %d | Score: %d | Collisions: %d/%d\n",
       niveauActuel, score, joueur.getCollisionsCount(), maxCollisions);

    if (joueur.getCollisionsCount() >= 3) {
        attron(COLOR_PAIR(2));
        printw("Attention! %d/%d collisions\n", joueur.getCollisionsCount(), maxCollisions);
        attroff(COLOR_PAIR(2));
    }

    refresh();
}


void GameEngine::niveauSuivant() {
    niveauActuel++;
    score += 100 * niveauActuel;
    labyrinthe = Labyrinthe(labyrinthe.getLargeur(), labyrinthe.getHauteur());
    labyrinthe.generer();
    joueur = Joueur(1, 1);
    victoire = false;
    gameOver = false;
}


void GameEngine::handleInput() {
    int ch = getch(); // Utilise directement getch() de ncurses

    if (gameOver || victoire) {
        if (ch != ERR) {
            if (victoire) {
                switch(ch) {
                    case 'n': case 'N':
                        niveauSuivant();
                        break;
                    case 'q': case 'Q':
                        gameOver = true;
                        break;
                }
            } else {
                switch(ch) {
                    case 'r': case 'R':
                        resetGame();
                        break;
                    case 'q': case 'Q':
                        gameOver = true;
                        break;
                }
            }
        }
        return;
    }

    if (ch != ERR) {  // ERR = aucune touche pressée
        switch(ch) {
            case 'z': case 'Z': case KEY_UP:
                joueur.deplacer(0, -1, labyrinthe);
                break;
            case 'q': case 'Q': case KEY_LEFT:
                joueur.deplacer(-1, 0, labyrinthe);
                break;
            case 's': case 'S': case KEY_DOWN:
                joueur.deplacer(0, 1, labyrinthe);
                break;
            case 'd': case 'D': case KEY_RIGHT:
                joueur.deplacer(1, 0, labyrinthe);
                break;
            case 'x': case 'X':
                gameOver = true;
                break;
        }
    }
}




void GameEngine::resetGame() {
    gameOver = false;
    victoire = false;
    labyrinthe = Labyrinthe(labyrinthe.getLargeur(), labyrinthe.getHauteur());
    labyrinthe.generer();
    joueur = Joueur(1, 1);
    score = 0;
    niveauActuel = 1;
    joueur.resetCollisions();
}


void GameEngine::run() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();

    // Configure les paires de couleurs
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);

    // Message d'accueil
    clear();
    printw("===== LABYRINTHE CONSOLE =====\n");
    printw("Commandes : Z (haut), Q (gauche), S (bas), D (droite), X (quitter)\n");
    printw("Appuyez sur une touche pour commencer...");
    refresh();
    getch(); // Attend une touche

    // Boucle principale
    while (!gameOver) {
        handleInput();
        update();
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 10 FPS
    }

    // Message de fin
    clear();
    printw("Merci d'avoir joué ! Appuyez sur une touche pour quitter...");
    refresh();
    getch();
    endwin(); // Restaure le terminal
}