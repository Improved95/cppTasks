#include "Life.h"

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
