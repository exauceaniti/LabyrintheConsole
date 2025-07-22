#include "include/GameEngine.h"
#include <iostream>

/**
 * @brief Fonction principale, point de démarrage du jeu
 */
int main() {
    std::cout << "===== Labyrinthe Console Game =====" << std::endl;
    std::cout << "Commandes : Z (haut), Q (gauche), S (bas), D (droite), X (quitter)" << std::endl;

    int largeur = 21;  // Largeur impaire pour la grille
    int hauteur = 21;  // Hauteur impaire

    try {
        GameEngine jeu(largeur, hauteur); // Initialise le moteur
        jeu.run();                        // Lance la partie
    } catch (const std::exception& e) {
        std::cerr << "[ERREUR] " << e.what() << std::endl;
    }

    std::cout << "Merci d’avoir joué ! 👋" << std::endl;
    return 0;
}
