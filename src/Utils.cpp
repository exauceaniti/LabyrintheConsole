#include "../include/Utils.h"

#ifdef __linux__
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * @brief Vérifie si une touche a été pressée sans bloquer l'exécution
 */
int _kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    // Sauvegarde de l'état terminal
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);          // Mode non canonique + pas d'écho
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Active la lecture non bloquante
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar(); // Lecture

    // Restaure l'état
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin); // Remet le caractère dans le flux
        return 1;
    }

    return 0;
}

/**
 * @brief Lit une touche pressée immédiatement (sans enter)
 */
int _getch() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Lecture immédiate
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar(); // Lecture bloquante

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restaure le terminal
    return ch;
}
#endif
