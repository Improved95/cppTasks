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
    long long rows, columns;
    string input;

    cout << "Enter quantity rows:";
    do {
        cin >> input;
    } while (!exceptionHandling.strtollIsCorrect(rows, input, "Incorrect input rows. You need enter unsigned integer value."));
    field.setRows(rows);

    cout << "Enter quantity columns:";
    do {
        cin >> input;
    } while (!exceptionHandling.strtollIsCorrect(columns, input, "Incorrect input columns. You need enter unsigned integer value."));
    field.setColums(columns);
}
