#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Labyrinthe.h"
#include "Joueur.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <ncurses.h>

class GameEngine {
private:
    Labyrinthe labyrinthe;
    Joueur joueur;
    bool gameOver;
    int score;
    int niveauActuel;
    bool victoire;

    void handleInput();
    void niveauSuivant();
    void update();
    void checkVictory();
    void render();
    void showGameResult(const std::string& title);
    static const int maxCollisions = 5;
    std::chrono::time_point<std::chrono::steady_clock> nextFrame;
    std::chrono::nanoseconds frameDuration;

public:
    GameEngine(int largeurLaby, int hauteurLaby, int niveau = 1);
    void run();
    void resetGame();
};
#endif