#include "Life.h"
using std::cin;

void Life::gameWithoutInitialData() {
    Field field;
    size_t a, b;
    cin >> a;
    field.setRows(a);

    cin >> b;
    field.setColums(b);
    // to be continue...
}

void Life::gameWithInitialData(char **argv) {
    ifstream fileIn;
    ConsoleArgumentChecker checker;
    if (checker.checkInput(argv, fileIn) == 0) {

    } else {
        gameWithoutInitialData();
    }
}

void Life::offlineGame(char **argv) {

}