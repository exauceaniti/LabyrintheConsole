/**
* @file GameEngine.h
 * @brief Déclaration du moteur principal du jeu
 */

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Labyrinthe.h"
#include "Joueur.h"

/**
 * @class GameEngine
 * @brief Contrôle la boucle principale du jeu et les interactions
 */
class GameEngine {
public:
    GameEngine(int largeurLaby, int hauteurLaby);  // Initialise le moteur
    void run();                                    // Lance le jeu

private:
    Labyrinthe labyrinthe;  // Grille du jeu
    Joueur joueur;          // Joueur contrôlé
    bool gameOver;          // État du jeu (terminé ou non)
    int score = 0;
    bool gameOver = false; // ✅ Initialise à false

    // Méthodes internes
    void processInput();    // Gère les touches appuyées
    void update();          // Logique d'évolution du jeu
    void render();          // Affichage du jeu
};

#endif // GAMEENGINE_H
