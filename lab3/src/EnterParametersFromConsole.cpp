#include "Life.h"
#include <limits.h>
#include <sstream>
using std::cout;
using std::endl;
using std::cin;
using std::getline;

bool EnterParametersFromConsole::rulesIsCorrect(string &input, string message) {
    if (input.size() > 9) {
        return false;
    }
    for (char s : input) {
        if (!isdigit(s)) {
            cout << message << endl;
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

    do {
        cout << "Enter birth rule:";
        cin >> input;
    } while (!rulesIsCorrect(input, "Incorrect birth rule. You need enter a sequences of different digits from the set {0...8}"));
    field.setBirthRules(input);

    do {
        cout << "Enter survival rule:";
        cin >> input;
    } while (!rulesIsCorrect(input, "Incorrect survival rule. You need enter a sequences of different digits from the set {0...8}"));
    field.setSurvivalRule(input);

    initialFieldSize(field);
}

void EnterParametersFromConsole::initialFieldSize(Field &field) {
    ExceptionHandling exceptionHandling;
    size_t rows, columns;
    string input;

    do {
        cout << "Enter quantity rows:";
        cin >> input;
    } while (!exceptionHandling.sttoullIsCorrect(rows, input, "Incorrect input rows. You need enter unsigned integer value."));
    field.setRows(rows);

    do {
        cout << "Enter quantity columns:";
        cin >> input;
    } while (!exceptionHandling.sttoullIsCorrect(columns, input, "Incorrect input columns. You need enter unsigned integer value."));
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
