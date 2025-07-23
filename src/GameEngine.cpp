#include "../include/GameEngine.h"
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

struct termios GameEngine::oldTermios;

// Constructeur
GameEngine::GameEngine(int width, int height)
    : labyrinthe(width, height), joueur(1, 1), gameOver(false) {
    labyrinthe.generer();
}

void GameEngine::update() {
    // Accès correct à la paire (std::pair) de la sortie
    auto sortie = labyrinthe.getSortie();
    if (joueur.getX() == sortie.first && joueur.getY() == sortie.second) {
        gameOver = true;
        std::cout << "\n*** Victoire ! ***\n";
    }
}

void GameEngine::render() {
    system("clear");

    // Utilisation des méthodes get() pour les dimensions
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
}

// [Le reste de votre code existant reste inchangé]

// --- Fonctions existantes (gestion du clavier) ---
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

    if (input == '\033') { // Flèches directionnelles (ASCII 27)
        if (!keyPressed()) return;
        getKey(); // Ignore le '['
        switch(getKey()) {
            case 'A': joueur.deplacer(0, -1, labyrinthe); break; // Haut
            case 'B': joueur.deplacer(0, 1, labyrinthe); break;  // Bas
            case 'D': joueur.deplacer(-1, 0, labyrinthe); break; // Gauche
            case 'C': joueur.deplacer(1, 0, labyrinthe); break;   // Droite
        }
    } else {
        switch(input) {
            case 'z': case 'Z': joueur.deplacer(0, -1, labyrinthe); break;
            case 'q': case 'Q': joueur.deplacer(-1, 0, labyrinthe); break;
            case 's': case 'S': joueur.deplacer(0, 1, labyrinthe); break;
            case 'd': case 'D': joueur.deplacer(1, 0, labyrinthe); break;
            case 'x': case 'X': gameOver = true; break; // Quitter
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
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }
    restoreKeyboard();
}