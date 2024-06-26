#include "Life.h"
#include <vector>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
using std::cin;
using std::vector;

void ChangeField::pulseFieldFill(Field &field) {
    const size_t X = 2;
    const size_t Y = 2;

    vector<size_t> patternX = {2, 3, 4, 8, 9, 10, 2, 3, 4, 8, 9, 10, 2, 3, 4, 8, 9, 10, 2, 3, 4, 8, 9, 10, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 12, 12, 12, 12, 12, 12};
    vector<size_t> patternY = {0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 12, 12, 12, 12, 12, 12, 2, 3, 4, 8, 9, 10, 2, 3, 4, 8, 9, 10, 2, 3, 4, 8, 9, 10, 2, 3, 4, 8, 9, 10};
    for (size_t i = 0; i < patternX.size(); i++) {
        field.cellsTree.addCell(Cell(X + patternX[i], Y + patternY[i]), field.rows, field.columns, 0);
    }

}

/*���� ��������, ����� �� ���-�� �������� � ������� ��� ��� ����*/
void Field::drawField() {
    system("clear");
    cout << "University name: " << fieldName << endl;
    size_t i = rows, j = 0;
    set<Cell> allCellsList;
    this->cellsTree.getAllCells(allCellsList);
    auto it = allCellsList.begin();
    for (; i > 0; i--) {
        for (; j < columns; j++) {
            if (i == it->getY() + 1 && j == it->getX()) {
                cout << "#";
                it++;
            } else {
                cout << "_";
            }
        }
        j = 0;
        cout << "\n";
        if (it == allCellsList.end()) {
            break;
        }
    }
    for (; i > 1; i--) {
        for (; j < columns; j++) {
            cout << "_";
        }
        j = 0;
        cout << "\n";
    }
}

void Field::drawField(ofstream &fileOut) {
    fileOut << "#Life 1.06" << endl;
    fileOut << "#" << this->fieldName << endl;
    fileOut << "#R B" << this->birthRule << "/S" << this->survivalRule << endl;
    set<Cell> allCellsList;
    this->cellsTree.getAllCells(allCellsList);
    for (Cell cell : allCellsList) {
        fileOut << cell.getX() << " " << cell.getY() << endl;
    }
}

void StandartGame::coutHelp() {
    cout << "You can input this comand:" << endl;
    cout << "1) help - output the available commands;" << endl;
    cout << "2) tick<n - calculate n iterations and display them on the screen;" << endl;
    cout << "3) dump<filePath - save field in file;" << endl;
    cout << "4) exit - stop game." << endl;
}

pair<int, string> StandartGame::cinFromConsole() {
    EnterParametersFromConsole checkInput;
    string input;
    stringstream streamInput;

    cout << "Enter command:";
    cin >> input;
    if (cin.fail()) {
        cout << "work" << endl;
    }
    streamInput << input;
    return checkInput.parseInGameInput(streamInput);
}

void StandartGame::calculateNIterations(Field &field, size_t ticks) {
    ChangeField changeField;
    for (size_t i = 0; i < ticks; i++) {
        changeField.calculateFieldByRules(field);
    }
}

void StandartGame::writeFieldInFile(Field &field, string &input) {
    ofstream fileOut;
    fileOut.open(input);
    if (!fileOut.is_open()) {
        cout << "Could not open the file" << endl;
        return;
    }
    field.drawField(fileOut);
    fileOut.close();
}

void StandartGame::run(Field &field) {
    system("clear");
    cout << "Game started in Standart mode." << endl;
    coutHelp();
    ExceptionHandling exceptionHandling;

    size_t ticks = 0;
    bool runningGame = true;
    while (runningGame) {
        pair<int, string> input = cinFromConsole();
        switch(input.first) {
            case 0:
                calculateNIterations(field, ticks);
                field.drawField();
            case 1:
                coutHelp();
                break;
            case 2:
                if (!exceptionHandling.sttoullIsCorrect(ticks, input.second, "Incorrect n")) {
                    break;
                }
                calculateNIterations(field, ticks);
                field.drawField();
                break;
            case 3:
                writeFieldInFile(field, input.second);
                break;
            case 4:
                return;
        }
    }
}

void OfflineGame::run(Field &field, size_t ticks, ofstream &outputData) {
    ChangeField changeField;
    for (size_t i = 0; i < ticks; i++) {
        changeField.calculateFieldByRules(field);
    }
    field.drawField(outputData);
}
