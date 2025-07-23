#include "../include/GameEngine.h"
#include "../include/Affichage.h"
#include "../include/Utils.h"
#include <iostream>
#include <chrono>
#include <thread>


GameEngine::GameEngine(int largeurLaby, int hauteurLaby)
    : labyrinthe(largeurLaby, hauteurLaby), joueur(1, 1),
    gameOver(false), score(0) {
    labyrinthe.generer();
}

void GameEngine::run() {
    Keyboard::init();
    atexit(Keyboard::restore);

    while (!gameOver) {
        system("clear");
        render();

        if (Keyboard::keyPressed()) {
            char input = Keyboard::getChar();
            switch(input) {
                case 'z': joueur.deplacer(0, -1, labyrinthe); break;
                case 'q': joueur.deplacer(-1, 0, labyrinthe); break;
                case 's': joueur.deplacer(0, 1, labyrinthe); break;
                case 'd': joueur.deplacer(1, 0, labyrinthe); break;
                case 'x': gameOver = true; break;
            }
        }

        if (joueur.getX() == labyrinthe.getSortie().first &&
            joueur.getY() == labyrinthe.getSortie().second) {
            render();
            std::cout << "Victoire !\n";
            gameOver = true;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}


void GameEngine::update() {
    checkVictory();
}

void GameEngine::checkVictory() {
    Position playerPos(joueur.getX(), joueur.getY());
    if (playerPos == labyrinthe.getSortie()) {
        gameOver = true;
    }
}

void GameEngine::render() {
    system("clear");
    std::cout << "=== LABYRINTHE DE ANITI EXAUCE ===" << std::endl;
    std::cout << "Contrôles: Z (haut), Q (gauche), S (bas), D (droite)" << std::endl;
    std::cout << "X pour quitter | Objectif: Atteindre la sortie (S)\n" << std::endl;

    afficherLabyrinthe(labyrinthe.getGrille(), joueur, labyrinthe.getEntree(),
        labyrinthe.getSortie());

    std::cout << "\nPosition: (" << joueur.getX() << "," << joueur.getY() << ")";
    std::cout << " | Score: " << score << std::endl;
}