#include "../include/Joueur.h"

// Initialise la position du joueur au point de départ
Joueur::Joueur(int xDepart, int yDepart)
    : x(xDepart), y(yDepart) {}

// Déplace le joueur en fonction de dx, dy si la case n’est pas un mur
void Joueur::deplacer(int dx, int dy, const Labyrinthe& laby) {
    int nx = x + dx;
    int ny = y + dy;

    // Vérifie que la nouvelle position est valide et non bloquée
    if (laby.estValide(nx, ny) && !laby.estMur(nx, ny)) {
        x = nx;
        y = ny;
    }
}

// Accesseurs simples pour récupérer la position
int Joueur::getX() const { return x; }
int Joueur::getY() const { return y; }
