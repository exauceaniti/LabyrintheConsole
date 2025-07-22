#include "../include/Affichage.h"
#include <iostream>

/**
 * @brief Affiche chaque ligne de la grille du labyrinthe
 * @param grille Matrice booléenne représentant le labyrinthe (true = mur, false = chemin)
 */
void afficherLabyrinthe(const std::vector<std::vector<bool>>& grille) {
    for (size_t y = 0; y < grille.size(); ++y) {
        for (size_t x = 0; x < grille[y].size(); ++x) {
            std::cout << (grille[y][x] ? "#" : " "); // # = mur, espace = chemin
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Affiche la position du joueur
 * @param x Coordonnée horizontale du joueur
 * @param y Coordonnée verticale du joueur
 */
void afficherJoueur(int x, int y) {
    std::cout << "Position du joueur : (" << x << ", " << y << ")" << std::endl;
}
