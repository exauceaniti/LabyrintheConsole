#include "Utils.h"
#include <unistd.h>      // Pour STDIN_FILENO
#include <termios.h>     // Pour termios, tcgetattr, tcsetattr
#include <sys/ioctl.h>   // Pour ioctl

static struct termios original;

void Keyboard::init() {
    tcgetattr(STDIN_FILENO, &original);
    struct termios raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void Keyboard::restore() {
    tcsetattr(STDIN_FILENO, TCSANOW, &original);
}

bool Keyboard::keyPressed() {
    int bytes;
    ioctl(STDIN_FILENO, FIONREAD, &bytes);
    return bytes > 0;
}

char Keyboard::getChar() {
    char ch = 0;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}