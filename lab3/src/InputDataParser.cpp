#include "Life.h"
void InputDataParser::coutInputExample() {
    cout << "Incorrect format file." << endl;
    cout << "Example input format:" << endl;
    cout << "#Life 1.06\n#Base\n#R B3/S23\n0 -1\n1 0\n-1 1\n0 1\n1 1" << endl;
}

bool InputDataParser::formatLifeDeathRuleIsCorrect(Field &field, string input) {
    input = input.substr(2, input.size());
    if (input[0] != 'B') {
        coutInputExample();
        return false;
    }

    size_t i = 1;
    string value;
    for (; i < input.size() && input[i] != '/'; i++) {
        if (!std::isdigit(input[i])) {
            coutInputExample();
            return false;
        }
        value += input[i];
    }
    field.setBirthRules(value);

    if (input.substr(i, i) != "/S") {
        coutInputExample();
        return false;
    }

    value.clear();
    i += 2;
    for (; i < input.size(); i++) {
        if (!std::isdigit(input[i])) {
            coutInputExample();
            return false;
        }
        value += input[i];
    }
    field.setSurvivalRule(value);

    return true;
}

bool InputDataParser::isStrokeWithFieldName(Field &field, ifstream &inputData) {
    char character;
    string input;

    inputData.get(character);
    if (character == '#') {
        getline(inputData, input);
        field.setFieldName(input);
    } else {
        return false;
    }

    return true;
}

bool InputDataParser::isStrokeWithDeathSurvRules(Field &field, ifstream &inputData) {
    char character;
    string input;

    inputData.get(character);
    if (character == '#') {
        getline(inputData, input);
        if (input.substr(0, 2) == "R ") {
            if (!formatLifeDeathRuleIsCorrect(field, input)) {
                return false;
            }
        }
    } else {
        return false;
    }

    return true;
}

bool InputDataParser::checkInputCells(Field &field, ifstream &inputData) {
    ExceptionHandling exceptionHandling;
    string input;
    size_t a, b;
    while (getline(inputData, input, ' ')) {
        if (!exceptionHandling.coordinateIsCorrect(a, field.getRows(), input, "")) {
            return false;
        }

        getline(inputData, input);
        if (!exceptionHandling.coordinateIsCorrect(b, field.getColums(), input, "")) {
            return false;
        }

        Cell cell(a, b);
        field.getCellsList()->addCell(cell, field.getRows(), field.getColums(), 0);
    }

    return true;
}

bool InputDataParser::fileV106Parser(Field &field, ifstream &inputData) {
    string input;
    if (!isStrokeWithFieldName(field, inputData)) {
        coutInputExample();
        return false;
    }
    if (!isStrokeWithDeathSurvRules(field, inputData)) {
        coutInputExample();
        return false;
    }

    EnterParametersFromConsole enterParameters;
    enterParameters.initialFieldSize(field);

    BlockOfCells *root = new BlockOfCells();
    field.setCellsList(root->constructorOfStruct(root, field.getRows(), field.getColums(), 3, 0));
    if (!checkInputCells(field, inputData)) {
        coutInputExample();
        return false;
    }

    return true;
}

bool InputDataParser::inputDataParsing(Field &field, ifstream &inputData) {
    string input;
    getline(inputData, input, ' ');
    if (input != "#Life") {
        coutInputExample();
        return false;
    }

    getline(inputData, input, '\n');
    if (input == "1.06") {
        if (!fileV106Parser(field, inputData)) {
            return false;
        }
    } else {
        coutInputExample();
        return false;
    }

    return true;
}

