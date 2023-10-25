#include "Life.h"
using std::cin;



void Life::gameWithoutInitialData() {
    Field field;
    size_t a, b;
    cin >> a;
    field.setRows(a);

    cin >> b;
    field.setColums(b);


}

void Life::gameWithInitialData(char **argv) {

}

void Life::offlineGame(char **argv) {

}

void Life::initialGame() {

}

void Life::initialGameWithConsoleParameters(int argc, char **argv) {
    switch(argc) {
        case 1:
            // игра без начальных данных
            gameWithoutInitialData();
            break;
        case 2:
            // игра со считыванием по файлу
            gameWithInitialData(argv);
            break;
        case 4:
            // оффлайн режим

            break;
        default:
            //ошибка
            break;
    }
}
