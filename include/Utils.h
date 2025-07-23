#ifndef UTILS_H
#define UTILS_H


class Keyboard {
public:
    static void init();
    static void restore();
    static bool keyPressed();
    static char getChar();
};

#endif