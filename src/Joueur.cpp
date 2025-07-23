#include "../include/Joueur.h"

/**
 * @brief Constructeur initialisant la position du joueur
 * @param[in] xDepart Coordonnée X initiale (doit être valide dans le labyrinthe)
 * @param[in] yDepart Coordonnée Y initiale (doit être valide dans le labyrinthe)
 * @details :
 * - Initialise les coordonnées (x,y) du joueur
 * - Ne vérifie pas la validité immédiate (vérifiée lors des déplacements)
 * @warning Les positions négatives sont acceptées mais causeront des erreurs lors des déplacements
 */
Joueur::Joueur(int xDepart, int yDepart)
    : x(xDepart), y(yDepart) {}

/**
 * @brief Tente un déplacement relatif du joueur
 * @param[in] dx Déplacement horizontal (-1: gauche, +1: droite)
 * @param[in] dy Déplacement vertical (-1: haut, +1: bas)
 * @param[in] laby Référence constante au labyrinthe pour validation
 * @details :
 * 1. Calcule la nouvelle position (nx, ny)
 * 2. Vérifie la validité via laby.estValide()
 * 3. Vérifie l'absence de mur via laby.estMur()
 * 4. Met à jour la position si les conditions sont remplies
 * @note Le déplacement est silencieusement ignoré si invalide
 * @warning Ne gère pas encore les animations ou effets spéciaux
 */
void Joueur::deplacer(int dx, int dy, const Labyrinthe& laby) {
    int nx = x + dx;
    int ny = y + dy;

    if (laby.estValide(nx, ny) && !laby.estMur(nx, ny)) {
        x = nx;
        y = ny;
    }
}

/**
 * @brief Accesseur pour la coordonnée X
 * @return Position horizontale actuelle (0-based)
 * @note Méthode const - garantit l'immuabilité de l'objet
 */
int Joueur::getX() const { return x; }

/**
 * @brief Accesseur pour la coordonnée Y
 * @return Position verticale actuelle (0-based)
 * @note Méthode const - garantit l'immuabilité de l'objet
 */
int Joueur::getY() const { return y; }