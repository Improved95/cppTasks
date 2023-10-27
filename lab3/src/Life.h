#ifndef LIFE_H
#define LIFE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using std::string;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::exception;
using std::cin;
using std::vector;

class Life;
class Field;

class InputDataParser {
private:
    void coutInputExample();
    bool formatLifeDeathRuleIsCorrect(Field &field, string input);
    bool isStrokeWithFieldName(Field &field, ifstream &inputData);
    bool isStrokeWithDeathSurvRules(Field &field, ifstream &inputData);
    bool checkInputCells(Field &field, ifstream &inputData);
public:
    bool inputDataParsing(Field &field, ifstream &inputData);
};

class ExceptionHandling {
public:
    bool strtoullCheck(size_t &rows, const string &input, const char *message);
};

class ParserConsoleParametersAndInitialGame {
public:
    void parseAndInitial(int argc, char **argv, Life *gameObject);
};

class Cell {
private:
    size_t x;
    size_t y;

public:
    Cell(const size_t xPos, const size_t yPos) {
        this->x = xPos;
        this->y = yPos;
    }
};

class Field {
private:
    string fieldName;
    size_t rows;
    size_t colums;
    string birthRule;
    string survivalRule;
    vector<Cell> cellsArray;

public:
    void statusChange();
    void setFieldName(const string valueFieldName) { this->fieldName = valueFieldName; }
    void setRows(const size_t valueRows) { this->rows = valueRows; }
    void setColums(const size_t valueColums) { this->colums = valueColums; }
    void setBirthRules(const string valueBirthRule) { this->birthRule = valueBirthRule; }
    void setSurvivalRule(const string valueSurvivalRule) { this->survivalRule = valueSurvivalRule; }
    vector<Cell> & getCellsArray() { return cellsArray; }

    void randomFieldInitial();
};

class Life {
private:
    Field field;

    void initilizedDataFromConsole();
    bool initilizedDataFromFile(ifstream &inputData);

public:
    void initialFieldWithConsoleParameters(int argc, char **argv);
    void initialField();
    void initialField(ifstream &inputData);
    void initialField(ifstream &inputData, size_t ticks, ofstream &outputData);
    void runningStandartGame();
    void runningOfflineGame();

    friend ParserConsoleParametersAndInitialGame;
};

#endif
