/**
 * @file Joueur.h
 * @brief Déclaration de la classe Joueur représentant l'entité contrôlable du jeu
 * @author [Votre nom]
 * @version 1.0
 * @date [JJ/MM/AAAA]
 */

#ifndef JOUEUR_H
#define JOUEUR_H

#include "Labyrinthe.h"

/**
 * @class Joueur
 * @brief Représente le personnage principal contrôlé par le joueur
 * @details Gère :
 * - Le positionnement dans le labyrinthe
 * - Les déplacements avec vérification de validité
 * - L'accès sécurisé aux coordonnées
 */
class Joueur {
private:
    int x; ///< Position horizontale (colonne) dans la grille (0 = gauche)
    int y; ///< Position verticale (ligne) dans la grille (0 = haut)

public:
    /**
     * @brief Constructeur initialisant la position de départ
     * @param[in] xDepart Coordonnée X initiale
     * @param[in] yDepart Coordonnée Y initiale
     * @pre Les coordonnées doivent être valides (≥0)
     * @post Crée une instance avec (x,y) = (xDepart,yDepart)
     */
    Joueur(int xDepart, int yDepart);

    /**
     * @brief Tente un déplacement relatif
     * @param[in] dx Déplacement horizontal souhaité (-1: gauche, +1: droite)
     * @param[in] dy Déplacement vertical souhaité (-1: haut, +1: bas)
     * @param[in] laby Référence constante au labyrinthe pour vérification
     * @details :
     * - Vérifie la validité du déplacement (pas de mur, pas hors limites)
     * - Met à jour les coordonnées si mouvement valide
     * @return void (le déplacement est silencieusement ignoré si invalide)
     * @warning Ne vérifie pas les collisions avec d'autres entités (si existantes)
     */
    void deplacer(int dx, int dy, const Labyrinthe& laby);

    /**
     * @brief Accesseur pour la position X
     * @return Coordonnée horizontale actuelle (0-based)
     * @note Méthode const - ne modifie pas l'objet
     */
    int getX() const;

    /**
     * @brief Accesseur pour la position Y
     * @return Coordonnée verticale actuelle (0-based)
     * @note Méthode const - ne modifie pas l'objet
     */
    int getY() const;
};

#endif // JOUEUR_H