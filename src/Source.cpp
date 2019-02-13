

#include "SnakeGame.h"


int main(int argc, char *argv[]) {

    SnakeGame sk(30, 30, "Nano Snake", {0, 0, 0});
    sk.mainloop();
    return 0;
}