#include "Life.h"

void Life::initialGame() {

}

void Life::initialGameWithConsoleParameters(int argc, char **argv) {
    if (argc == 1) {
        gameWithoutInitialData();
    } else {
        ParserConsoleParametersAndInitialGame parser;
        parser.parseAndInitial(argc, argv, this);
    }
}
