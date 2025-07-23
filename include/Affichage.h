#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <vector>
#include "Labyrinthe.h"
#include "Joueur.h"

void afficherLabyrinthe(const std::vector<std::vector<bool>>& grille, 
                       const Joueur& joueur,
                       const Position& entree,
                       const Position& sortie);

#endif