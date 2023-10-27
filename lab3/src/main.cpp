#include "Life.h"

int main(int argc, char **argv) {
    ifstream fileIn;
    fileIn.open("base.life");
    if (!fileIn.is_open()) return 1;

    Life life1;
//    life1.initialFieldWithConsoleParameters(argc, argv);
//    life1.runningStandartGame();
    life1.initialField(fileIn);

    fileIn.close();
    return 0;
}

/* нужно доделать считываение клеток
 * нужно переделать метод проверки stoull, чтобы он возвращал значение, а истину или ложность через параметры
 * нужно спросить у препода про то, что я в парсере задаю параметры, хотя парсер нужен не для этого
 * тоже самое про запуск игры из метода parseAndInitial, он нужен чтобы проверить консоль, а не для запуска...*/