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
    EnterParametersFromConsole enterParameters;
    enterParameters.initialFieldParameters(this->field);

    BlockOfCells blockOfCells = BlockOfCells();
    BlockOfCells *root = blockOfCells.constructorOfStruct(&blockOfCells, this->field.getRows(), this->field.getColums(), 3, 0);
    this->field.setCellsList(root);

    this->field.setSurvivalRule("23");
    this->field.setBirthRules("3");

    ChangeField changeFieldStatus;
    changeFieldStatus.pulseFieldFill(field);

    runningStandartGame();
}

void Life::initialField(ifstream &inputData) {
    InputDataParser dataParser;

    /*если файл не прошел проверку на корректность,
     * то игра будет запущена в стандартном режиме с произвольным заполнением.*/
    if (!dataParser.inputDataParsing(this->field, inputData)) {
        initialField();
        return;
    }

    runningStandartGame();
}

void Life::initialField(ifstream &inputData, size_t ticks, ofstream &outputData) {

}
