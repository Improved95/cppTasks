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
using std::stringstream;
using std::pair;

class Life;
class Field;
class Cell;

class ExceptionHandling {
public:
    bool coordinateIsCorrect(size_t &value, const size_t maxValue, const string &input, const char *message);
    bool sttoullIsCorrect(size_t &value, const string &input, const char *message);
};

class InputDataParser {
private:
    void coutInputExample();
    bool formatLifeDeathRuleIsCorrect(Field &field, string input);
    bool isStrokeWithFieldName(Field &field, ifstream &inputData);
    bool isStrokeWithDeathSurvRules(Field &field, ifstream &inputData);
    bool checkInputCells(Field &field, ifstream &input);
    bool fileV106Parser(Field &field, ifstream &inputData);
public:
    bool inputDataParsing(Field &field, ifstream &inputData);
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
    pair<int, string> parseInGameInput(stringstream &input);
};

class BlockOfCells {
private:
    BlockOfCells *left;
    BlockOfCells *right;
    set<Cell> *cellsList;

public:
    BlockOfCells();
    ~BlockOfCells();
    BlockOfCells(const BlockOfCells &tree);
    void copyConstructor(const BlockOfCells *example, BlockOfCells *node);

    void operator=(const BlockOfCells &blockOfCells) {
        this->left = blockOfCells.left;
        this->right = blockOfCells.right;
        this->cellsList = blockOfCells.cellsList;
    }

    BlockOfCells * getLeftNode() const { return left; }
    BlockOfCells * getRightNode() const { return right; }
    set<Cell> * getCellsList() const { return cellsList; }

    BlockOfCells * constructorOfStruct(BlockOfCells *node, const size_t rows, const size_t columns, const size_t blockSize, const int mode);
    void addCell(const Cell &cell, const size_t rows, const size_t columns, const int mode);
    bool cellIsExist(const Cell &cell, const size_t rows, const size_t columns, const int mode) const;
    bool cellIsExistByCoordinate(const size_t posX, const size_t posY, const size_t rows, const size_t columns, const int mode) const;
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
    friend bool operator<(const Cell &a, const Cell &b) {
//        return (a.x < b.x || (a.x == b.x && a.y <= b.y));
        return (a.y > b.y || (a.y == b.y && a.x <= b.x));
    }
    friend bool operator==(const Cell &a, const Cell &b) {
        return (a.x == b.x && a.y == b.y);
    }

    size_t getX() const { return this->x; }
    size_t getY() const { return this->y; }
};

class OfflineGame {

};

class StandartGame {
private:
    void coutHelp();
    void writeFieldInFile(Field &field, string &filePath);
    void calculateNIterations(Field &field, size_t ticks);

public:
    void run(Field &field);
};

class ChangeField {
private:
    void bypassingExistCells(BlockOfCells *original, const BlockOfCells *copyRoot, const Field &field);
    void recursionCalcField(BlockOfCells *original, const BlockOfCells *copy, const BlockOfCells *copyRoot, const Field &field);
    size_t countNeighborsForCell(const Cell &cell, const BlockOfCells *copyRoot, const Field &field) const;
    size_t getRealCoord(long long coord, const size_t maxCoord) const;
public:
    void calculateFieldByRules(Field &field);
//    void randomFieldFill();
//    void pulseFieldFill(Field &field);
};


class Field {
private:
    string fieldName;
    size_t rows;
    size_t columns;
    string birthRule;
    string survivalRule;
    BlockOfCells cellsTree;

    void recursionDraw(BlockOfCells &node, size_t &i, size_t &j);

public:
    Field() {
        this->columns = 7;
        this->rows = 7;
    }
    void operator=(const Field &field) {
        this->fieldName = field.fieldName;
        this->rows = field.rows;
        this->columns = field.columns;
        this->birthRule = field.birthRule;
        this->survivalRule = field.survivalRule;
        this->cellsTree = field.cellsTree;
    }

    void setFieldName(const string valueFieldName) { this->fieldName = valueFieldName; }
    void setRows(const size_t valueRows) { this->rows = valueRows; }
    void setColumns(const size_t valueColumns) { this->columns = valueColumns; }
    void setBirthRules(const string valueBirthRule) { this->birthRule = valueBirthRule; }
    void setSurvivalRule(const string valueSurvivalRule) { this->survivalRule = valueSurvivalRule; }
    void setCellsList(const BlockOfCells &valueCellsList) { this->cellsTree = valueCellsList; }

    string getFieldName() const { return this->fieldName; }
    size_t getRows() const { return this->rows; }
    size_t getColums() const { return this->columns; }
    string getBirthRule() const { return this->birthRule; }
    string getSurvivalRule() const { return this->survivalRule; }
    BlockOfCells & getCellsList() { return cellsTree; }

    void drawField();

    friend ChangeField;
};

class Life {
private:
    Field field;

public:
    Life() {
//        Field fieldObj;
        this->field = *(new Field());
    }
    void initialFieldWithConsoleParameters(int argc, char **argv);
    void initialField();
    void initialField(ifstream &inputData);
    void initialField(ifstream &inputData, size_t ticks, ofstream &outputData);
};

#endif
