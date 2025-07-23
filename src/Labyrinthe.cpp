#include "../include/Labyrinthe.h"
#include <stdexcept>
#include <algorithm>
#include <random>
#include <queue>
#include <stack>


Labyrinthe::Labyrinthe(int largeur, int hauteur)
    : largeur(largeur), hauteur(hauteur) {
    if (largeur % 2 == 0 || hauteur % 2 == 0) {
        throw std::invalid_argument("Les dimensions du labyrinthe doivent être impaires");
    }
    reset();
}


void Labyrinthe::generer() {
    reset();
    creerChemin(largeur / 2, hauteur / 2);
    creerEntreeSortie();
}


bool Labyrinthe::estMur(int x, int y) const {
    if (!estValide(x, y)) return true;
    return grille[y][x];
}

bool Labyrinthe::estValide(int x, int y) const {
    return x >= 0 && y >= 0 && x < largeur && y < hauteur;
}

void Labyrinthe::reset() {
    grille.assign(hauteur, std::vector<bool>(largeur, true));
}


void Labyrinthe::creerChemin(int x, int y) {
    std::stack<Position> pile;
    pile.push({x, y});

    while (!pile.empty()) {
        Position current = pile.top();
        x = current.first;
        y = current.second;
        grille[y][x] = false;

        auto directions = melangerDirections();
        bool cheminTrouve = false;

        for (const auto& dir : directions) {
            int nx = x + dir.first * 2;
            int ny = y + dir.second * 2;

            if (estValide(nx, ny) && grille[ny][nx]) {
                grille[y + dir.second][x + dir.first] = false;
                pile.push({nx, ny});
                cheminTrouve = true;
                break;
            }
        }

        if (!cheminTrouve) {
            pile.pop();
        }
    }
}

/**
 * @brief Positionne l'entrée et la sortie
 * @details :
 * - L'entrée est toujours au centre
 * - La sortie est la case accessible la plus éloignée
 * @uses Parcours en largeur (BFS) pour calculer les distances
 */
void Labyrinthe::creerEntreeSortie() {
    std::vector<std::vector<int>> distances(hauteur, std::vector<int>(largeur, -1));
    std::queue<Position> file;

    int startX = largeur / 2;
    int startY = hauteur / 2;
    file.push({startX, startY});
    distances[startY][startX] = 0;

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

    int maxDist = -1;
    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            if (!estMur(x, y) && distances[y][x] > maxDist) {
                maxDist = distances[y][x];
                sortie = {x, y};
            }
        }
    }

    entree = {startX, startY};
}

/**
 * @brief Génère des directions aléatoires
 * @return Vecteur des 4 directions cardinales mélangées
 * @note Utilise un générateur aléatoire sécurisé (std::random_device)
 */
std::vector<Position> Labyrinthe::melangerDirections() const {
    std::vector<Position> directions = {{0,-1}, {1,0}, {0,1}, {-1,0}};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(directions.begin(), directions.end(), g);
    return directions;
}