#include "Life.h"

int main(int argc, char **argv) {
    Life life1;
    life1.initialFieldWithConsoleParameters(argc, argv);
    life1.runningStandartGame();
    return 0;
}