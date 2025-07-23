
#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <vector>
#include <utility>

using Position = std::pair<int, int>;

class Labyrinthe {

private:
    int largeur;
    int hauteur;
    std::vector<std::vector<bool>> grille;
    Position entree;
    Position sortie;

    void creerChemin(int x, int y);
    void creerEntreeSortie();
    void reset();
    std::vector<Position> melangerDirections() const;


public:

    Labyrinthe(int largeur, int hauteur);
    void generer();
    bool estMur(int x, int y) const;
    bool estValide(int x, int y) const;
    int getLargeur() const;
    int getHauteur() const;
    Position getEntree() const { return entree; }
    Position getSortie() const { return sortie; }


    friend bool operator==(const Position& a, const Position& b) {
        return a.first == b.first && a.second == b.second;
    }

    const std::vector<std::vector<bool>>& getGrille() const { return grille; }
};

#endif // LABYRINTHE_H