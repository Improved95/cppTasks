#include "Life.h"

void Life::initialFieldWithConsoleParameters(int argc, char **argv) {
    if (argc == 1) {
        initialField();
    } else {
        ParserConsoleParameters parser;
        parser.parseAndInitial(argc, argv, this);
    }
}

void Life::initialField() {
//    EnterParametersFromConsole enterParameters;

//    Field fieldObj;
//    this->field = fieldObj;
//    enterParameters.initialFieldParameters(this->field);
//
//    BlockOfCells cellsList;
//    this->field.getCellsList() = cellsList;
//
//    ChangeFieldStatus changeFieldStatus;
//    changeFieldStatus.randomFieldFill();

    runningStandartGame();
}

void Life::initialField(ifstream &inputData) {
    InputDataParser dataParser;
    EnterParametersFromConsole enterParameters;

    Field fieldObj;
    this->field = fieldObj;

    vector<Cell> cellsVector;
    // если файл не прошел проверку на корректность, то игра будет запущена в стандартном режиме с произвольным заполнением.
    if (!dataParser.inputDataParsing(this->field, inputData, cellsVector)) {
        this->field.~Field(); /*(проверить подобные места, где я присваиваю классы полям, но такое вроде только здесь)*/
        initialField();
        return;
    }
    enterParameters.initialFieldSize(this->field);

    BlockOfCells cellsList(this->field.getRows(), this->field.getColums());
    this->field.setCellsList(&cellsList);

    ChangeFieldStatus changeFieldStatus;
    changeFieldStatus.fromFileFieldFill(this->field, cellsVector);
    cellsVector.~vector();

    runningStandartGame();
}

void Life::initialField(ifstream &inputData, size_t ticks, ofstream &outputData) {

}

// написать деструктор для field, там у меня указатель на структуру с клетками, для нее нужно тоже написать деструктор