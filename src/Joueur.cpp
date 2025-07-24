#include "Joueur.h"

Joueur::Joueur(int xDepart, int yDepart)
    : x(xDepart), y(yDepart), collisionsCount(0), gameOver(false) {}

void Joueur::deplacer(int dx, int dy, const Labyrinthe& laby) {
    if (gameOver) return;

    int newX = x + dx;
    int newY = y + dy;

    if (laby.estMur(newX, newY)) {
        collisionsCount++;
        if (collisionsCount >= 5) {
            gameOver = true;
        }
    } else {
        x = newX;
        y = newY;
    }
}

int Joueur::getX() const { return x; }
int Joueur::getY() const { return y; }

