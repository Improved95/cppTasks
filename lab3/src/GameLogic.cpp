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

void Field::recursionDraw(BlockOfCells &node, size_t &i, size_t &j) {
    if (node.getLeftNode() != nullptr) {
        recursionDraw(*(node.getLeftNode()), i, j);
    }
    if (node.getRightNode() != nullptr) {
        recursionDraw(*(node.getRightNode()), i, j);
    }

    if (node.getLeftNode() == nullptr && node.getRightNode() == nullptr) {
        set<Cell>::iterator it = node.getCellsList()->begin();
        for (; i > 0; i--) {
            for (; j < columns; j++) {
                if (it == node.getCellsList()->end()) {
                    return;
                }
                if ((*it).getY() + 1 == i && (*it).getX() == j) {
                    cout << (char)254;
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
    cout << "University name: " << fieldName << endl;
    size_t i = rows, j = 0;
    recursionDraw(cellsTree, i, j);
    for (; i > 0; i--) {
        for (; j < columns; j++) {
            cout << "_";
        }
        j = 0;
        cout << "\n";
    }
}

void StandartGame::coutHelp() {
    cout << "You can input this comand:" << endl;
    cout << "1) help - output the available commands;" << endl;
    cout << "2) tick<n> - calculate n iterations and display them on the screen;" << endl;
    cout << "3) dump<filePath> - save field in file;" << endl;
    cout << "4) exit - stop game." << endl;
}

pair<int, string> StandartGame::cinFromConsole() {
    EnterParametersFromConsole checkInput;
    string input;
    stringstream streamInput;

    cout << "Enter command:";
    cin >> input;
    streamInput << input;
    return checkInput.parseInGameInput(streamInput);
}

void StandartGame::calculateNIterations(Field &field, size_t ticks) {
    ChangeField changeField;
    for (size_t i = 0; i < ticks; i++) {
        changeField.calculateFieldByRules(field);
    }
}

//void StandartGame::writeFieldInFile(Field &field, string &filePath) {
//
//}

void generate(Field &field, int x, int y) {
    Cell c1(x, y);
    Cell c2(x + 1, y);
    Cell c3(x + 2, y);
    Cell c4(x + 2, y + 1);
    Cell c5(x + 1, y + 2);
    field.getCellsList().addCell(c1, field.getRows(), field.getColums(), 0);
    field.getCellsList().addCell(c2, field.getRows(), field.getColums(), 0);
    field.getCellsList().addCell(c3, field.getRows(), field.getColums(), 0);
    field.getCellsList().addCell(c4, field.getRows(), field.getColums(), 0);
    field.getCellsList().addCell(c5, field.getRows(), field.getColums(), 0);
}

void clearTree(BlockOfCells *bl) {
    if (bl->getLeftNode() == nullptr && bl->getRightNode() == nullptr) {
        bl->getCellsList()->clear();
        return;
    }
    clearTree(bl->getLeftNode());
    clearTree(bl->getRightNode());
}

void StandartGame::run(Field &field) {
    generate(field, 4, 0);
//    for (int i = 0 ; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            generate(field, j, i);
            field.drawField();
            clearTree(&field.getCellsList());
//        }
//    }
//    calculateNIterations(field, 1);
//    field.drawField();

//    cout << "Game started in Standart mode." << endl;
//    coutHelp();
//    ExceptionHandling exceptionHandling;
//
//    size_t ticks = 0;
//    bool runningGame = true;
//    while (runningGame) {
//        pair<int, string> input = cinFromConsole();
//        switch(input.first) {
//            case 1:
//                coutHelp();
//                break;
//            case 2:
//                if (!exceptionHandling.sttoullIsCorrect(ticks, input.second, "Incorrect n")) {
//                    break;
//                }
//                calculateNIterations(field, ticks);
//                field.drawField();
//                break;
//            case 3:
//                writeFieldInFile(field, input.second);
//                break;
//            case 4:
//                return;
//        }
//    }
}
