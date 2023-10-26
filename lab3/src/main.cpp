#include "Life.h"

int main(int argc, char **argv) {
    ifstream fileIn;
    fileIn.open("base.life");

    Life life1;
//    life1.initialFieldWithConsoleParameters(argc, argv);
//    life1.runningStandartGame();
    life1.initialField(fileIn);

    fileIn.close();
    return 0;
}