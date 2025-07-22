/**
* @file Affichage.h
 * @brief Fonctions utilitaires pour afficher le labyrinthe et le joueur
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "Labyrinthe.h"

// Affiche la grille du labyrinthe dans la console
void afficherLabyrinthe(const std::vector<std::vector<bool>>& grille);

// Affiche la position actuelle du joueur
void afficherJoueur(int x, int y);

#endif // AFFICHAGE_H
