#include "Life.h"
using std::cout;
using std::endl;

void Life::initialFieldWithConsoleParameters(int argc, char **argv) {
    if (argc == 1) {
        initialField();
    } else {
        ParserConsoleParameters parser;
        parser.parseAndInitial(argc, argv, this);
    }
}

void Life::initialField() {
    cout << "Welcome to Conway's Game of Life!" << endl;
    EnterParametersFromConsole enterParameters;

    enterParameters.initialFieldParameters(this->field);

    BlockOfCells blockOfCells = BlockOfCells();
    BlockOfCells *root = blockOfCells.constructorOfStruct(&blockOfCells, field.getRows(), field.getColums(), 3, 0);
    field.setCellsList(*root);

    ChangeField changeField;
    changeField.pulseFieldFill(this->field);

    StandartGame game;
    game.run(this->field);
}

void Life::initialField(ifstream &inputData) {
    cout << "Welcome to Conway's Game of Life!" << endl;
    InputDataParser dataParser;
    /*если файл не прошел проверку на корректность,
     * то игра будет запущена в стандартном режиме с произвольным заполнением.*/
    if (!dataParser.inputDataParsing(this->field, inputData)) {
        initialField();
        return;
    }

    StandartGame game;
    game.run(this->field);
}

void Life::initialField(ifstream &inputData, size_t ticks, ofstream &outputData) {
    InputDataParser dataParser;
    if (!dataParser.inputDataParsing(this->field, inputData)) {
        initialField();
        return;
    }

    OfflineGame game;
    game.run(this->field, ticks, outputData);
}
