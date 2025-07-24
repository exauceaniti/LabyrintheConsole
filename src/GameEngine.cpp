#include "../include/GameEngine.h"
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cctype>
#include <iomanip>

struct termios GameEngine::oldTermios;

// Nouveau constructeur avec niveau
GameEngine::GameEngine(int width, int height, int niveau)
    : labyrinthe(width, height), joueur(1, 1), gameOver(false),
      score(0), niveauActuel(niveau), victoire(false) {
    labyrinthe.generer();
}

void GameEngine::update() {
    if (joueur.isGameOver()) {  // Vérifie si le joueur a trop de collisions
        gameOver = true;
        return;
    }

    if (!victoire) {
        auto sortie = labyrinthe.getSortie();
        if (joueur.getX() == sortie.first && joueur.getY() == sortie.second) {
            victoire = true;
            score += 100 * niveauActuel;
        }
    }
}

void GameEngine::render() {
    system("clear");

    if (victoire) {
        std::cout << "\n\n";
        std::cout << "    ╔════════════════════════════╗\n";
        std::cout << "        FÉLICITATIONS !           \n";
        std::cout << "        Vous avez réussi          \n";
        std::cout << "    ╠════════════════════════════╣\n";
        std::cout << "        Score: " << std::setw(10) << score << "       \n";
        std::cout << "        Niveau: " << std::setw(8) << niveauActuel << "       \n";
        std::cout << "    ╚════════════════════════════╝\n\n";
        std::cout << "    ► [N]iveau suivant\n";
        std::cout << "    ► [Q]uitter\n\n";
        std::cout << "  Sélection: _\b";
        return;
    }
    else if (gameOver && joueur.isGameOver()) {
        std::cout << "\n\n";
        std::cout << "    ╔════════════════════════════╗\n";
        std::cout << "             GAME OVER!           \n";
        std::cout << "       Trop de collisions         \n";
        std::cout << "    ╠════════════════════════════╣\n";
        std::cout << "        Score: " << std::setw(10) << score << "      \n";
        std::cout << "        Niveau: " << std::setw(8) << niveauActuel << "       \n";
        std::cout << "    ╚════════════════════════════╝\n\n";
        std::cout << "    ► [R]ecommencer\n";
        std::cout << "    ► [Q]uitter\n\n";
        std::cout << "  Sélection: ";
        fflush(stdout);
        return;
    }

    // Récupère les positions
    const int joueurX = joueur.getX();
    const int joueurY = joueur.getY();
    const auto sortie = labyrinthe.getSortie();
    const bool collisionRecent = (joueur.getCollisionsCount() > 0 && joueur.getCollisionsCount() % 5 != 0);

    // Affichage du labyrinthe
    for (int y = 0; y < labyrinthe.getHauteur(); ++y) {
        for (int x = 0; x < labyrinthe.getLargeur(); ++x) {
            if (joueurX == x && joueurY == y) {
                std::cout << (collisionRecent ? "\033[31mP\033[0m" : "\033[32mP\033[0m");
            }
            else if (x == sortie.first && y == sortie.second) {
                std::cout << "\033[33mS\033[0m";
            }
            else if (labyrinthe.estMur(x, y)) {
                std::cout << "\033[34m#\033[0m";
            }
            else {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    // Affichage des informations
    std::cout << "Contrôles: ZQSD/Flèches | X: Quitter\n"
              << "Niveau: " << niveauActuel
              << " | Score: " << score
              << " | Collisions: " << joueur.getCollisionsCount() << "/5\n";

    if (joueur.getCollisionsCount() >= 3) {
        std::cout << "\033[31mAttention! Collisions: "
                  << joueur.getCollisionsCount() << "/5\033[0m\n";
    }
}

void GameEngine::initKeyboard() {
    tcgetattr(STDIN_FILENO, &oldTermios);
    struct termios newTermios = oldTermios;
    newTermios.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL);
    newTermios.c_cc[VMIN] = 0;
    newTermios.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void GameEngine::restoreKeyboard() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
}

bool GameEngine::keyPressed() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

char GameEngine::getKey() {
    char ch;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}

void GameEngine::handleInput() {
    if (!keyPressed()) return;
    char input = tolower(getKey());

    if (gameOver && joueur.isGameOver()) {
        switch(input) {
            case 'r':
                resetGame();
                break;
            case 'q':
                std::cout << "\nMerci d'avoir joué !\n";
                std::this_thread::sleep_for(std::chrono::seconds(1)); // Pause avant de quitter
                exit(0);
            default:
                return; // Ignore les autres touches
        }
        return;
    }

    // Gestion des mouvements normaux
    if (input == '\033') { // Flèches directionnelles
        if (!keyPressed()) return;
        getKey(); // Ignore le '['
        switch(getKey()) {
            case 'A': joueur.deplacer(0, -1, labyrinthe); break; // Haut
            case 'B': joueur.deplacer(0, 1, labyrinthe); break;  // Bas
            case 'D': joueur.deplacer(-1, 0, labyrinthe); break; // Gauche
            case 'C': joueur.deplacer(1, 0, labyrinthe); break;  // Droite
        }
    } else { // Touches ZQSD
        switch(tolower(input)) {
            case 'z': joueur.deplacer(0, -1, labyrinthe); break;
            case 'q': joueur.deplacer(-1, 0, labyrinthe); break;
            case 's': joueur.deplacer(0, 1, labyrinthe); break;
            case 'd': joueur.deplacer(1, 0, labyrinthe); break;
            case 'x': gameOver = true; break;
        }
    }
}

void GameEngine::resetGame() {
    gameOver = false;
    victoire = false;
    labyrinthe = Labyrinthe(labyrinthe.getLargeur(), labyrinthe.getHauteur());
    labyrinthe.generer();
    joueur = Joueur(1, 1);
    score = 0;
    niveauActuel = 1;  // Réinitialise aussi le niveau si nécessaire
    joueur.resetCollisions();  // Si ta classe Joueur a cette méthode
}

void GameEngine::run() {
    initKeyboard();
    atexit(restoreKeyboard);

    // Fréquence de rafraîchissement (60 FPS)
    constexpr std::chrono::milliseconds frameDuration(16);
    auto nextFrame = std::chrono::steady_clock::now();

    while (!gameOver) {
        update();
        render();
        handleInput();

        // Contrôle précis du framerate
        nextFrame += frameDuration;
        std::this_thread::sleep_until(nextFrame);
    }
    restoreKeyboard();
}