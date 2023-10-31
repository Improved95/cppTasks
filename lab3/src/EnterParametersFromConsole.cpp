#include "Life.h"
#include <limits.h>

void EnterParametersFromConsole::initialFieldParameters(Field &field) {
    string input;

    cout << "Enter field name: ";
    cin >> input;
    field.setFieldName(input);

    initialFieldSize(field);
}

void EnterParametersFromConsole::initialFieldSize(Field &field) {
    ExceptionHandling exceptionHandling;
    size_t rows, columns;
    string input;

    cout << "Enter quantity rows:";
    do {
        cin >> input;
    } while (!exceptionHandling.coordinateIsCorrect(rows, ULONG_LONG_MAX, input, "Incorrect input rows. You need enter unsigned integer value."));
    field.setRows(rows);

    cout << "Enter quantity columns:";
    do {
        cin >> input;
    } while (!exceptionHandling.coordinateIsCorrect(columns, ULONG_LONG_MAX, input, "Incorrect input columns. You need enter unsigned integer value."));
    field.setColums(columns);
}
