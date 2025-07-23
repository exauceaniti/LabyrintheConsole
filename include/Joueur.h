#ifndef JOUEUR_H
#define JOUEUR_H

#include "Labyrinthe.h"

class Joueur {
private:
    int x;
    int y;

public:

    Joueur(int xDepart, int yDepart);
    void deplacer(int dx, int dy, const Labyrinthe& laby);
    void resetPosition() { x = 1; y = 1; }
    int getX() const;
    int getY() const;
};

#endif // JOUEUR_H