#include "Life.h"

//void ChangeFieldStatus::randomFieldFill() {
//
//}

void ChangeField::pulseFieldFill(Field &field) {
    const size_t X = 0;
    const size_t Y = 0;

    vector<Cell> cells;
    for (size_t j = 0; j < 2; j++) {
        for (size_t i = 0; i < 3; i++) {
            Cell cell(i + 2 + X, Y + 5 * j);
            field.cellsList->addCell(cell, field.getRows(), field.getColums(), 0);
        }
        for (size_t i = 0; i < 3; i++) {
            Cell cell(i + 8 + X, Y + 5 * j);
            field.cellsList->addCell(cell, field.getRows(), field.getColums(), 0);
        }
    }
}

void Field::recursionDraw(BlockOfCells *node, size_t &i, size_t &j) {
    if ((*node).getLeftNode() != nullptr) {
        cout << (*node).getLeftNode() << endl;
        recursionDraw((*node).getLeftNode(), i, j);
        cout << (*node).getLeftNode() << endl;
    }
    if ((*node).getRightNode() != nullptr) {
        recursionDraw((*node).getRightNode(), i, j);
    }

//    set<Cell>::iterator it = node->getCellsTree()->begin();
    for (; i < rows; i++) {
        for (; j < columns; j++) {
//            if (it == node->getCellsTree()->end()) {
//                return;
//            }
//            if ((*it).getX() == i && (*it).getY() == j) {
//                cout << "1";
//                it++;
//            } else {
//                cout << "0";
//            }
        }
        j = 0;
        cout << "\n";
    }
}

void Field::drawField() {
    size_t i = 0, j = 0;
    recursionDraw(this->cellsList, i, j);

    for (; i < rows; i++) {
        for (; j < columns; j++) {
            cout << "0";
        }
        j = 0;
        cout << "\n";
    }
}

void Life::runningStandartGame() {
    this->field.drawField();
}

void Life::runningOfflineGame() {

}
