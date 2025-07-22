#include "../include/GameEngine.h"
#include "../include/Affichage.h"
#include "../include/Utils.h"
#include <iostream>

/**
 * @brief Initialise le moteur du jeu avec un labyrinthe et un joueur
 */
GameEngine::GameEngine(int largeurLaby, int hauteurLaby)
    : labyrinthe(largeurLaby, hauteurLaby), joueur(1, 1), gameOver(false) {
    labyrinthe.generer(); // Génère la structure du labyrinthe au lancement
}

/**
 * @brief Lance la boucle principale du jeu jusqu’à ce que le joueur quitte
 */
void GameEngine::run() {
    while (!gameOver) {
        render();        // Affiche le labyrinthe et le joueur
        processInput();  // Gère les touches
        update();        // Logique du jeu
    }
    std::cout << "[DEBUG] boucle active\n";

}


/**
 * @brief Traite les commandes clavier du joueur
 */
void GameEngine::processInput() {
    if (_kbhit()) {
        char touche = _getch();
        bool aBouge = false;

        switch (touche) {
            case 'z': joueur.deplacer(0, -1, labyrinthe); aBouge = true; break;
            case 'q': joueur.deplacer(-1, 0, labyrinthe); aBouge = true; break;
            case 's': joueur.deplacer(0, 1, labyrinthe); aBouge = true; break;
            case 'd': joueur.deplacer(1, 0, labyrinthe); aBouge = true; break;
            case 'x':
                std::cout << "Fin du jeu demandée. 👋" << std::endl;
                gameOver = true;
                break;
            default:
                std::cout << "[!] Touche inconnue : " << touche << std::endl;
        }

        if (aBouge) {
            score++; // ✅ Incrémente le score uniquement si déplacement
        }
    }
    std::cout << "[DEBUG] touche captée\n";
}


/**
 * @brief Met à jour la logique interne du jeu (détection de victoire possible ici)
 */
void GameEngine::update() {
    // Ex: Tu peux ajouter une condition de victoire si le joueur atteint la sortie
    // if (joueur.getX() == labyrinthe.getSortie().first && joueur.getY() == labyrinthe.getSortie().second) {
    //     std::cout << "Bravo ! Tu as atteint la sortie !" << std::endl;
    //     gameOver = true;
    // }
}

/**
 * @brief Affiche le labyrinthe et les infos du joueur
 */
void GameEngine::render() {
    afficherLabyrinthe(labyrinthe.getGrille());
    afficherJoueur(joueur.getX(), joueur.getY());

    // 👉 Ajout affichage du score
    std::cout << "\n=====================" << std::endl;
    std::cout << "Score: " << score << std::endl;
    std::cout << "=====================\n" << std::endl;
}

