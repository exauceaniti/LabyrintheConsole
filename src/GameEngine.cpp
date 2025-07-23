#include "../include/GameEngine.h"
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cctype> // Pour tolower()

struct termios GameEngine::oldTermios;

// Nouveau constructeur avec niveau
GameEngine::GameEngine(int width, int height, int niveau)
    : labyrinthe(width, height), joueur(1, 1), gameOver(false),
      score(0), niveauActuel(niveau), victoire(false) {
    labyrinthe.generer();
}

void GameEngine::update() {
    auto sortie = labyrinthe.getSortie();
    if (joueur.getX() == sortie.first && joueur.getY() == sortie.second) {
        victoire = true;
        gameOver = true;
        score += 100 * niveauActuel; // Calcul du score
    }
}

void GameEngine::render() {
    system("clear");

    if (victoire) {
        std::cout << "================================\n";
        std::cout << " FÉLICITATIONS ! Vous avez réussi\n";
        std::cout << " Score: " << score << " points\n";
        std::cout << " Niveau: " << niveauActuel << "\n";
        std::cout << "================================\n\n";
        std::cout << " [N]iveau suivant\n";
        std::cout << " [Q]uitter\n";
        return;
    }

    for (int y = 0; y < labyrinthe.getHauteur(); ++y) {
        for (int x = 0; x < labyrinthe.getLargeur(); ++x) {
            if (joueur.getX() == x && joueur.getY() == y) {
                std::cout << 'P';  // Joueur
            } else if (labyrinthe.estMur(x, y)) {
                std::cout << '#';  // Mur
            } else {
                auto sortie = labyrinthe.getSortie();
                if (x == sortie.first && y == sortie.second) {
                    std::cout << 'S';  // Sortie
                } else {
                    std::cout << ' ';  // Chemin vide
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Contrôles : ZQSD ou flèches | X pour quitter" << std::endl;
    std::cout << "Niveau: " << niveauActuel << " | Score: " << score << std::endl;
}

void GameEngine::initKeyboard() {
    tcgetattr(STDIN_FILENO, &oldTermios);
    struct termios newTermios = oldTermios;
    newTermios.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL);
    newTermios.c_cc[VMIN] = 0;
    newTermios.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void GameEngine::restoreKeyboard() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
}

bool GameEngine::keyPressed() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

char GameEngine::getKey() {
    char ch;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}

void GameEngine::handleInput() {
    if (!keyPressed()) return;

    char input = getKey();

    if (victoire) {
        switch(tolower(input)) {
            case 'n':
                niveauActuel++;
                gameOver = false;
                victoire = false;
                // Réinitialiser le jeu avec nouveau niveau
                labyrinthe = Labyrinthe(labyrinthe.getLargeur() + 2, labyrinthe.getHauteur() + 2);
                labyrinthe.generer();
                joueur = Joueur(1, 1);
                break;
            case 'q': // Quitter
                gameOver = true;
                break;
        }
        return;
    }

    if (input == '\033') {
        if (!keyPressed()) return;
        getKey(); // Ignore le '['
        switch(getKey()) {
            case 'A': joueur.deplacer(0, -1, labyrinthe); break;
            case 'B': joueur.deplacer(0, 1, labyrinthe); break;
            case 'D': joueur.deplacer(-1, 0, labyrinthe); break;
            case 'C': joueur.deplacer(1, 0, labyrinthe); break;
        }
    } else {
        switch(input) {
            case 'z': case 'Z': joueur.deplacer(0, -1, labyrinthe); break;
            case 'q': case 'Q': joueur.deplacer(-1, 0, labyrinthe); break;
            case 's': case 'S': joueur.deplacer(0, 1, labyrinthe); break;
            case 'd': case 'D': joueur.deplacer(1, 0, labyrinthe); break;
            case 'x': case 'X': gameOver = true; break;
        }
    }
}

void GameEngine::run() {
    initKeyboard();
    atexit(restoreKeyboard);

    while (!gameOver) {
        update();
        render();
        handleInput();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    restoreKeyboard();
}