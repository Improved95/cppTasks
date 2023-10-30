#include "Life.h"

void ChangeFieldStatus::randomFieldFill() {

}

void ChangeFieldStatus::fromFileFieldFill(Field &field, vector<Cell> &cellsVector) {
    for (size_t i = 0; i < cellsVector.size(); i++) {
        field.cellsList->addCell(cellsVector[i]);
    }
}

void Life::runningStandartGame() {

}

void Life::runningOfflineGame() {

}