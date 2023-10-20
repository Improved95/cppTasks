#include "Life.h"
using std::cin;

void Life::gameWithoutInitialData(GameMessages messages) {
    Field field;
    size_t a, b;
    messages.coutUserEnterRowsOrColumn(1);
    cin >> a;
    field.setRows(a);

    messages.coutUserEnterRowsOrColumn(2);
    cin >> b;
    field.setColums(b);


}

void Life::gameWithInitialData(GameMessages messages, char **argv) {

}

void Life::offlineGame(GameMessages messages, char **argv) {

}

void Life::gameMode(size_t argc, char **argv) {
    GameMessages messages;
    switch (argc) {
        case 1:
            // игра без начальных данных
            gameWithoutInitialData(messages);
            break;
        case 2:
            // игра со считыванием по файлу
            gameWithInitialData(messages, argv);
            break;
        case 4:
            // оффлайн режим
            offlineGame(messages, argv);
            break;
        default:
            messages.incorrectData();
            gameWithoutInitialData(messages);
    }
}

void Life::initialGame(size_t argc, char **argv) {
    gameMode(argc, argv);
}



