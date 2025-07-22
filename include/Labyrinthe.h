/**
* @file Labyrinthe.h
 * @brief Déclaration de la classe Labyrinthe représentant la structure du jeu
 */

#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <vector>
#include <utility> // pour std::pair

// Alias de type pour simplifier l’écriture des positions
using Position = std::pair<int, int>;

class Labyrinthe {
private:
    int largeur;                              // Largeur du labyrinthe (doit être impaire)
    int hauteur;                              // Hauteur du labyrinthe (doit être impaire)
    std::vector<std::vector<bool>> grille;    // Matrice représentant murs (true) et chemins (false)
    Position entree;                          // Position de départ du joueur
    Position sortie;                          // Position d’arrivée

    void creerChemin(int x, int y);           // Algorithme de génération du labyrinthe
    void creerEntreeSortie();                 // Définition des points d’entrée et sortie
    void reset();                             // Remet la grille entièrement à l’état initial (murs)
    std::vector<Position> melangerDirections() const; // Mélange aléatoire des directions

public:
    Labyrinthe(int largeur, int hauteur);     // Constructeur avec dimensions
    void generer();                           // Lance la génération du labyrinthe

    // Méthodes d'accès
    bool estMur(int x, int y) const;          // Retourne true si la case est un mur
    bool estValide(int x, int y) const;       // Vérifie que les coordonnées sont dans la grille
    int getLargeur() const;                   // Accès à la largeur
    int getHauteur() const;                   // Accès à la hauteur
    Position getEntree() const;               // Accès à l’entrée
    Position getSortie() const;               // Accès à la sortie
    const std::vector<std::vector<bool>>& getGrille() const { return grille; } // Accès direct à la grille
};

#endif // LABYRINTHE_H
