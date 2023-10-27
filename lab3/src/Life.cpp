#include "Life.h"

void Life::initialFieldWithConsoleParameters(int argc, char **argv) {
    if (argc == 1) {
        initialField();
    } else {
        ParserConsoleParametersAndInitialGame parser;
        parser.parseAndInitial(argc, argv, this);
    }
}

void Life::initilizedDataFromConsole() {
    ExceptionHandling exceptionHandling;
    size_t rows, columns;
    string input;

    cout << "Enter field name: ";
    cin >> input;
    this->field.setFieldName(input);

    cout << "Enter quantity rows: ";
    do {
        cin >> input;
    } while (exceptionHandling.strtoullCheck(rows, input, "Incorrect input rows. You need enter unsigned integer value."));
    this->field.setRows(rows);

    cout << "Enter quantity columns: ";
    do {
        cin >> input;
    } while (exceptionHandling.strtoullCheck(columns, input, "Incorrect input columns. You need enter unsigned integer value."));
    this->field.setColums(columns);
}

bool Life::initilizedDataFromFile(ifstream &inputData) {
    InputDataParser dataParser;
    if (dataParser.inputDataParsing(this->field, inputData)) {
        return true;
    }
    return false;
}

void Life::initialField() {
    Field fieldObj;
    this->field = fieldObj;
    initilizedDataFromConsole();
    runningStandartGame();
}

void Life::initialField(ifstream &inputData) {
    Field fieldObj;
    this->field = fieldObj;
    if (initilizedDataFromFile(inputData)) {
        runningStandartGame();
    }
}

void Life::initialField(ifstream &inputData, size_t ticks, ofstream &outputData) {
    Field fieldObj;
    this->field = fieldObj;
//    initilizedDataFromFile(inputData);
//    runningOfflineGame();
}
