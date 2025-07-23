#include "../include/Affichage.h"
#include <iostream>


void afficherLabyrinthe(const std::vector<std::vector<bool>>& grille,
                       const Joueur& joueur,
                       const Position& entree,
                       const Position& sortie) {
    for (size_t y = 0; y < grille.size(); ++y) {
        for (size_t x = 0; x < grille[y].size(); ++x) {
            if (x == joueur.getX() && y == joueur.getY()) {
                std::cout << "P";
            } else if (x == entree.first && y == entree.second) {
                std::cout << "E";
            } else if (x == sortie.first && y == sortie.second) {
                std::cout << "S";
            } else {
                std::cout << (grille[y][x] ? "#" : " ");
            }
        }
        std::cout << std::endl;
    }
}


void afficherJoueur(int x, int y) {
    std::cout << "Position du joueur : (" << x << ", " << y << ")" << std::endl;
}