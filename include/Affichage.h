#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <iostream>
#include <sstream>
#include <vector>
#include "Labyrinthe.h"
#include "Joueur.h"

inline void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void afficherLabyrinthe(const std::vector<std::vector<bool>>& grille,
                       const Joueur& joueur,
                       const Position& entree,
                       const Position& sortie);

#endif