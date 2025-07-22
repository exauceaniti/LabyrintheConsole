/**
* @file Joueur.h
 * @brief Déclaration de la classe Joueur représentant le personnage principal
 */

#ifndef JOUEUR_H
#define JOUEUR_H

#include "Labyrinthe.h"

class Joueur {
private:
    int x; // Position horizontale
    int y; // Position verticale

public:
    Joueur(int xDepart, int yDepart);             // Constructeur du joueur
    void deplacer(int dx, int dy, const Labyrinthe& laby); // Déplacement selon direction
    int getX() const;                             // Accès à la position X
    int getY() const;                             // Accès à la position Y
};

#endif // JOUEUR_H
