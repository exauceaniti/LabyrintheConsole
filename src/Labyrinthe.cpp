#include "../include/Labyrinthe.h"
#include <stdexcept>
#include <algorithm>
#include <random>
#include <queue>
#include <stack>  // Pour la génération avec backtracking

// Constructeur du labyrinthe
Labyrinthe::Labyrinthe(int largeur, int hauteur)
    : largeur(largeur), hauteur(hauteur) {

    // Vérifie que les dimensions sont impaires (nécessaire pour les murs autour)
    if (largeur % 2 == 0 || hauteur % 2 == 0) {
        throw std::invalid_argument("Les dimensions du labyrinthe doivent être impaires");
    }

    reset(); // Initialise la grille avec des murs
}

// Lance la génération complète du labyrinthe
void Labyrinthe::generer() {
    reset(); // Réinitialise la grille avant de générer

    // Point de départ au centre du labyrinthe
    int startX = largeur / 2;
    int startY = hauteur / 2;

    creerChemin(startX, startY); // Crée les chemins aléatoires
    creerEntreeSortie();         // Détermine l'entrée et la sortie
}

// Vérifie si une case est un mur
bool Labyrinthe::estMur(int x, int y) const {
    if (!estValide(x, y)) return true;
    return grille[y][x];
}

// Vérifie si une position est valide (dans les limites de la grille)
bool Labyrinthe::estValide(int x, int y) const {
    return x >= 0 && y >= 0 && x < largeur && y < hauteur;
}

// Accesseurs classiques
int Labyrinthe::getLargeur() const { return largeur; }
int Labyrinthe::getHauteur() const { return hauteur; }
Position Labyrinthe::getEntree() const { return entree; }
Position Labyrinthe::getSortie() const { return sortie; }

// Remet tous les murs dans la grille
void Labyrinthe::reset() {
    grille.assign(hauteur, std::vector<bool>(largeur, true));
}

// Algorithme de génération de chemins avec backtracking
void Labyrinthe::creerChemin(int x, int y) {
    std::stack<Position> pile;
    pile.push({x, y});

    while (!pile.empty()) {
        Position current = pile.top();
        x = current.first;
        y = current.second;
        grille[y][x] = false; // Creuse le chemin

        auto directions = melangerDirections();
        bool cheminTrouve = false;

        for (const auto& dir : directions) {
            int nx = x + dir.first * 2;
            int ny = y + dir.second * 2;

            if (estValide(nx, ny) && grille[ny][nx]) {
                // Creuse entre la case actuelle et la nouvelle
                grille[y + dir.second][x + dir.first] = false;
                pile.push({nx, ny});
                cheminTrouve = true;
                break; // On poursuit dans une seule direction à la fois
            }
        }

        if (!cheminTrouve) {
            pile.pop(); // Aucun chemin trouvé, on retourne en arrière
        }
    }
}

// Détermine l'entrée (centre) et la sortie (point le plus éloigné)
void Labyrinthe::creerEntreeSortie() {
    std::vector<std::vector<int>> distances(hauteur, std::vector<int>(largeur, -1));
    std::queue<Position> file;

    int startX = largeur / 2;
    int startY = hauteur / 2;
    file.push({startX, startY});
    distances[startY][startX] = 0;

    // Parcours en largeur pour calculer les distances depuis l'entrée
    while (!file.empty()) {
        auto current = file.front();
        file.pop();

        for (const auto& dir : std::vector<Position>{{0,1}, {1,0}, {0,-1}, {-1,0}}) {
            int nx = current.first + dir.first;
            int ny = current.second + dir.second;

            if (estValide(nx, ny) && !estMur(nx, ny) && distances[ny][nx] == -1) {
                distances[ny][nx] = distances[current.second][current.first] + 1;
                file.push({nx, ny});
            }
        }
    }

    // Trouve la case la plus éloignée pour la sortie
    int maxDist = -1;
    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            if (!estMur(x, y) && distances[y][x] > maxDist) {
                maxDist = distances[y][x];
                sortie = {x, y};
            }
        }
    }

    entree = {startX, startY}; // L'entrée est toujours au centre
}

// Mélange aléatoire des directions (haut, droite, bas, gauche)
std::vector<Position> Labyrinthe::melangerDirections() const {
    std::vector<Position> directions = {{0,-1}, {1,0}, {0,1}, {-1,0}};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(directions.begin(), directions.end(), g);
    return directions;
}
