#include "Life.h"
using std::cin;

void Life::gameWithoutInitialData() {
    Field field;
    ExceptionHandling exceptionHandling;
    size_t rows, columns;
    string input;

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

void Life::gameWithInitialData(ifstream &inputData) {

}

void Life::offlineGame(ifstream &inputData, size_t ticks, ofstream &outputData) {

}