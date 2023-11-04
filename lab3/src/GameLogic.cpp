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
    if (node.getRightNode() != nullptr) {
        recursionDraw(*(node.getRightNode()), i, j);
    }
    if (node.getLeftNode() != nullptr) {
        recursionDraw(*(node.getLeftNode()), i, j);
    }

    if (node.getLeftNode() == nullptr && node.getRightNode() == nullptr) {
        set<Cell>::iterator it = node.getCellsList()->begin();
        for (; i > 0; i--) {
            for (; j < columns; j++) {
                if (it == node.getCellsList()->end()) {
                    return;
                }
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
//    cout << "You can input this comand:" << endl;
//    cout << "1) help - output the available commands;" << endl;
//    cout << "2) tick<n> - calculate n iterations and display them on the screen;" << endl;
//    cout << "3) dump<filePath> - save field in file;" << endl;
//    cout << "4) exit - stop game." << endl;
}

//void StandartGame::writeFieldInFile(Field &field, string &filePath) {
//
//}

void StandartGame::cinFromConsole() {
    EnterParametersFromConsole checkInput;
    string input;
    stringstream streamInput;

    cout << "Enter command:";
    cin >> input;
    streamInput << input;
    pair<int, string> output = checkInput.parseInGameInput(streamInput);
}

void StandartGame::calculateNIterations(Field &field, size_t ticks) {
    ChangeField changeField;
    for (size_t i = 0; i < ticks; i++) {
        changeField.calculateFieldByRules(field);
    }
}

void StandartGame::run(Field &field) {
    ExceptionHandling exceptionHandling;

//    cout << "Game started in Standart mode." << endl;
//    coutHelp();

    size_t ticks = 0;
    string filePath;

//    bool runningGame = true;
    field.drawField();
    cout << endl;
    calculateNIterations(field, 4);
    field.drawField();
//    while (runningGame) {
//        cinFromConsole();
//
//    }

    /*while (runningGame) {
        cout << "Enter command:";
        cin >> input;
        streamInput << input;
        output = checkInput.parseInGameInput(streamInput);
        switch(output.first) {
            case 1:
                coutHelp();
                break;
            case 2:
                if (!exceptionHandling.sttoullIsCorrect(ticks, output.second, "Incorrect n")) {
                    break;
                }
                calculateNIterations(field, ticks);
                field.drawField();
                break;
            case 3:
                writeFieldInFile(field, output.second);
                break;
            case 4:
                return;
        }
        streamInput.clear();
        field.drawField();
    }*/
}
