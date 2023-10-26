#include "Life.h"

void Life::initialGameWithConsoleParameters(int argc, char **argv) {
    if (argc == 1) {
        initilizedDataFromConsole();
    } else {
        ParserConsoleParametersAndInitialGame parser;
        parser.parseAndInitial(argc, argv, this);
    }
}

void Life::initilizedDataFromConsole() {
    Field field;
    ExceptionHandling exceptionHandling;
    size_t rows, columns;
    string input;

    cout << "Enter field name: ";
    cin >> this->gameName;

    cout << "Enter quantity rows: ";
    do {
        cin >> input;
    } while (exceptionHandling.strtoullCheck(rows, input, "Incorrect input rows. You need enter unsigned integer value."));
    field.setRows(rows);

    cout << "Enter quantity columns: ";
    do {
        cin >> input;
    } while (exceptionHandling.strtoullCheck(columns, input, "Incorrect input columns. You need enter unsigned integer value."));
    field.setColums(columns);
}

void Life::initilizedDataFromFile(ifstream &inputData) {

}

void Life::initialGame() {

}

void Life::initialGame(ifstream &inputData) {

}

void Life::initialGame(ifstream &inputData, size_t ticks, ofstream &outputData) {

}

void Field::randomFieldInitial() {

}