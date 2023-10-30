#ifndef LIFE_H
#define LIFE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::exception;
using std::getline;
using std::vector;
using std::set;
using std::istringstream;

class Life;
class Field;
class Cell;

class ExceptionHandling {
public:
    bool strtollIsCorrect(long long &rows, const string &input, const char *message);
};

class InputDataParser {
private:
    void coutInputExample();
    bool formatLifeDeathRuleIsCorrect(Field &field, string input);
    bool isStrokeWithFieldName(Field &field, ifstream &inputData);
    bool isStrokeWithDeathSurvRules(Field &field, ifstream &inputData);
    bool checkInputCells(Field &field, string &inputData, vector<Cell> &cellsVector);
    bool fileV106Parser(Field &field, ifstream &inputData, vector<Cell> &cellsVector);
public:
    bool inputDataParsing(Field &field, ifstream &inputData, vector<Cell> &cellsVector);
};

// ./life.exe (console parameters)
class ParserConsoleParameters {
public:
    void parseAndInitial(int argc, char **argv, Life *gameObject);
};

// when user enter in console some data
class EnterParametersFromConsole {
public:
    void initialFieldSize(Field &field);
    void initialFieldParameters(Field &field);
};

class ChangeFieldStatus {
public:
    void statusChange();
    void randomFieldFill();
    void fromFileFieldFill(Field &field, vector<Cell> &cellsVector);
};

class StandartGame {

};

class OfflineGame {

};

class BlockOfCells {
private:
    BlockOfCells *left;
    BlockOfCells *right;
    set<BlockOfCells> cellsArray;

public:
    BlockOfCells(const size_t rows, const size_t columns);
    ~BlockOfCells();

    void addCell(const Cell &cell);
};

class Cell {
private:
    long long x;
    long long y;

public:
    Cell(const long long xPos, const long long yPos) {
        this->x = xPos;
        this->y = yPos;
    }
    long long getX() const { return this->x; }
    long long getY() const { return this->y; }
};

class Field {
private:
    string fieldName;
    size_t rows;
    size_t colums;
    string birthRule;
    string survivalRule;
    BlockOfCells *cellsList;

public:
    Field() {
        cellsList = nullptr;
    }

    void setFieldName(const string valueFieldName) { this->fieldName = valueFieldName; }
    void setRows(const size_t valueRows) { this->rows = valueRows; }
    void setColums(const size_t valueColums) { this->colums = valueColums; }
    void setBirthRules(const string valueBirthRule) { this->birthRule = valueBirthRule; }
    void setSurvivalRule(const string valueSurvivalRule) { this->survivalRule = valueSurvivalRule; }
    void setCellsList(BlockOfCells *valueCellsList) { this->cellsList = valueCellsList; }

    string getFieldName() { return this->fieldName; }
    size_t getRows() { return this->rows; }
    size_t getColums() { return this->colums; }
    string getBirthRule() { return this->birthRule; }
    string getSurvivalRule() { return this->survivalRule; }
    BlockOfCells * getCellsList() { return cellsList; }

    friend ChangeFieldStatus;
};

class Life {
private:
    Field field;

public:
    Life() {
        Field fieldObj;
        this->field = fieldObj;
    }
    void initialFieldWithConsoleParameters(int argc, char **argv);
    void initialField();
    void initialField(ifstream &inputData);
    void initialField(ifstream &inputData, size_t ticks, ofstream &outputData);
    void runningStandartGame();
    void runningOfflineGame();

    friend ParserConsoleParameters;
};

#endif
