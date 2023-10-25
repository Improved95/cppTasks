#include "Life.h"

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
