#include "Life.h"
#include <limits.h>

bool EnterParametersFromConsole::rulesIsCorrect(string &input) {
    if (input.size() > 9) {
        return false;
    }
    for (char s : input) {
        if (!isdigit(s)) {
            return false;
        }
    }
    return true;
}

void EnterParametersFromConsole::initialFieldParameters(Field &field) {
    string input;

    cout << "Enter field name:";
    cin >> input;
    field.setFieldName(input);

    cout << "Enter birth rule: ";
    do {
        cin >> input;
    } while (!rulesIsCorrect(input));

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
    field.setColumns(columns);
}

pair<int, string> EnterParametersFromConsole::parseInGameInput(stringstream &input) {
    string mode;
    pair<int, string> output;
    getline(input, mode , '<');
    if (mode == "help") {
        output.first = 1;
    } else if (mode == "tick") {
        output.first = 2;
        getline(input, mode);
        output.second = mode.substr(0, mode.size());
    } else if (mode == "dump") {
        output.first = 3;
        getline(input, mode);
        output.second = mode.substr(0, mode.size());
    } else if (mode == "exit") {
        output.first = 4;
    } else {
        output.first = 1;
        cout << "Incorrect input." << endl;
    }
    return output;
}

