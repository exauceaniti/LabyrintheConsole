/**
* @file Utils.h
 * @brief Fonctions système pour gérer les entrées clavier sous Linux
 */

#ifndef UTILS_H
#define UTILS_H

#ifdef __linux__
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * @brief Vérifie si une touche a été pressée (non bloquant)
 * @return 1 si une touche est disponible, 0 sinon
 */
int _kbhit();

/**
 * @brief Lit une touche pressée sans attendre Enter
 * @return Code ASCII de la touche
 */
int _getch();

#endif // __linux__

#endif // UTILS_H
