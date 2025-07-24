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

class GameEngine {
private:
    Labyrinthe labyrinthe;
    Joueur joueur;
    bool gameOver;
    int score;
    int niveauActuel;
    int maxCollisions = 5;
    bool victoire;
    static struct termios oldTermios;

    // Gestion clavier
    static void initKeyboard();
    static void restoreKeyboard();
    static bool keyPressed();
    static char getKey();
    void handleInput();

    void update();
    void checkVictory();
    void render();
    void showGameResult(const std::string& title);

public:
    GameEngine(int largeurLaby, int hauteurLaby, int niveau = 1);
    void run();
    void resetGame();
};

#endif