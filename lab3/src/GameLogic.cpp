#include "Life.h"

//void ChangeFieldStatus::randomFieldFill() {
//
//}

//void ChangeField::pulseFieldFill(Field &field) {
//    const size_t X = 0;
//    const size_t Y = 0;
//
//    vector<Cell> cells;
//    for (size_t j = 0; j < 2; j++) {
//        for (size_t i = 0; i < 3; i++) {
//            Cell cell(i + 2 + X, Y + 5 * j);
//            field.cellsList->addCell(cell, field.getRows(), field.getColums(), 0);
//        }
//        for (size_t i = 0; i < 3; i++) {
//            Cell cell(i + 8 + X, Y + 5 * j);
//            field.cellsList->addCell(cell, field.getRows(), field.getColums(), 0);
//        }
//    }
//}

/*void Field::recursionDraw(BlockOfCells &node, size_t &i, size_t &j) {
    if (node.left != nullptr) {
        recursionDraw(*node.left, i, j);
    }
    if (node.right != nullptr) {
        recursionDraw(*node.right, i, j);
    }

    if (node.left == nullptr && node.right == nullptr) {
        set<Cell>::iterator it = node.cellsTree->begin();
        for (; i < rows; i++) {
            for (; j < columns; j++) {
                if (it == node.cellsTree->end()) {
                    return;
                }
                if ((*it).getX() == i && (*it).getY() == j) {
                    cout << "1";
                    it++;
                } else {
                    cout << "_";
                }
            }
            j = 0;
            cout << "\n";
        }
    }
}*/

void Field::recursionDraw(BlockOfCells &node, size_t &i, size_t &j) {
    if (node.right != nullptr) {
        recursionDraw(*node.right, i, j);
    }
    if (node.left != nullptr) {
        recursionDraw(*node.left, i, j);
    }

    if (node.left == nullptr && node.right == nullptr) {
        set<Cell>::iterator it = node.cellsTree->begin();
        for (; i > 0; i--) {
            for (; j < columns; j++) {
                if (it == node.cellsTree->end()) {
                    return;
                }
//                cout << (*it).getX() << " " << (*it).getY() << " " << endl;
                if ((*it).getY() + 1 == i && (*it).getX() == j) {
                    cout << "1";
                    it++;
                } else {
                    cout << "_";
                }
            }
            j = 0;
            cout << "\n";
        }
    }
}

void Field::drawField() {
    size_t i = rows, j = 0;
    recursionDraw(cellsList, i, j);

    for (; i > 0; i--) {
        for (; j < columns; j++) {
            cout << "_";
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
