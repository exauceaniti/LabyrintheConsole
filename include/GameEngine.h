
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Labyrinthe.h"
#include "Joueur.h"

class GameEngine {
public:

    GameEngine(int largeurLaby, int hauteurLaby);


    void run();

private:
    Labyrinthe labyrinthe;
    Joueur joueur;
    bool gameOver;
    int score;


    void processInput();


    void update();

    void checkVictory();
    void render();
};

#endif // GAMEENGINE_H