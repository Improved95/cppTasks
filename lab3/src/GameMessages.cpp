#include "GameMessages.h"

void GameMessages::coutUserEnterRowsOrColumn(int RowsOrColumn) {
    if (RowsOrColumn == 1) {
        cout << "Enter rows quantity:";
    } else {
        cout << "Enter columns quantity:";
    }
}

void GameMessages::incorrectData() {
    cout << "You enter incorrect data, the game starts without initial data" << endl;
}