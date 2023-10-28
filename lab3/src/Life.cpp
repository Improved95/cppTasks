#include "Life.h"

void Life::initialFieldWithConsoleParameters(int argc, char **argv) {
    if (argc == 1) {
        initialField();
    } else {
        ParserConsoleParametersAndInitialGame parser;
        parser.parseAndInitial(argc, argv, this);
    }
}

void Life::initialField() {
    EnterParametersFromConsole enterParameters;
    Field fieldObj;
    this->field = fieldObj;

    enterParameters.initialFieldParameters(this->field);
    runningStandartGame();
}

void Life::initialField(ifstream &inputData) {
    InputDataParser dataParser;
    EnterParametersFromConsole enterParameters;
    Field fieldObj;
    this->field = fieldObj;

    vector<Cell> cellsArray;
    if (dataParser.inputDataParsing(this->field, inputData, cellsArray)) {
        enterParameters.initialFieldSize(this->field);


        runningStandartGame();

        return;
    }
    fieldObj.~Field();
    initialField();
}

void Life::initialField(ifstream &inputData, size_t ticks, ofstream &outputData) {

}
