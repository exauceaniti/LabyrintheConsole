#ifndef JOUEUR_H
#define JOUEUR_H

#include "Labyrinthe.h"

class Joueur {
private:
    int x;
    int y;
    int collisionsCount;
    bool gameOver;

public:
    Joueur(int xDepart, int yDepart);
    void deplacer(int dx, int dy, const Labyrinthe& laby);
    void resetPosition() { x = 1; y = 1; collisionsCount = 0; gameOver = false; }
    int getX() const;
    int getY() const;


    bool isGameOver() const { return gameOver; }
    int getCollisionsCount() const { return collisionsCount; }
    void resetCollisions() { collisionsCount = 0; gameOver = false; }
};

#endif // JOUEUR_H