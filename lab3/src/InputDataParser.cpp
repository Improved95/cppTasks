#include "Life.h"
using std::getline;

void coutInputExample() {
    cout << "Incorrect format file." << endl;
    cout << "Example input format:" << endl;
    cout << "#Life 1.06\n#Base\n#R B3/S23\n0 -1\n1 0\n-1 1\n0 1\n1 1" << endl;
}

bool InputDataParser::formatLifeDeathRuleIsCorrect(Field field, string input) {
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

bool InputDataParser::checkinputCells(Field &field, ifstream &inputData) {
    string input;
    getline(inputData, input, ' ');



    Cell cell(1, 2);
    field.getCellsArrat().push_back(cell);

    return true;
}

bool InputDataParser::inputDataParsing(Field &field, ifstream &inputData) {
    char character;
    string input;
    bool isFieldNameSet = false;
    bool isLifeDeathRuleSet = false;

    getline(inputData, input, ' ');
    if (input != "#Life") {
        cout << "Incorrect format file" << endl;
        coutInputExample();
        return false;
    }
    getline(inputData, input, '\n');
    if (input != "1.06") {
        coutInputExample();
        return false;
    }
    while (inputData.get(character)) {
        if (character == '#') {
            getline(inputData, input);
            if (input.substr(0, 2) == "R ") {
                if (isLifeDeathRuleSet) {
                    coutInputExample();
                    return false;
                } else {
                    formatLifeDeathRuleIsCorrect(field, input);
                    isLifeDeathRuleSet = true;
                }
            } else {
                if (isFieldNameSet) {
                    coutInputExample();
                    return false;
                } else {
                    field.setFieldName(input);
                    isFieldNameSet = true;
                }
            }
        } else {
            if (!checkinputCells(field, inputData)) {
                coutInputExample();
                return false;
            }
        }
    }

    return true;
}
