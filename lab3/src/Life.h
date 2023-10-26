#ifndef LIFE_H
#define LIFE_H

#include <iostream>
#include <string>
#include <fstream>
using std::string;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::exception;

class Life;

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
};

class Field {
private:
    size_t rows;
    size_t colums;
    string birth;
    string survival;
    Cell *cellArrays;

public:
    void statusChange();

    void setRows(const size_t valueRows) { this->rows = valueRows; }
    void setColums(const size_t valueColums) { this->colums = valueColums; }
};

class Life {
private:
    string gameName;

    void gameWithoutInitialData();
    void gameWithInitialData(ifstream &inputData);
    void offlineGame(ifstream &inputData, size_t ticks, ofstream &outputData);

public:
    void initialGame();
    void initialGameWithConsoleParameters(int argc, char **argv);

    friend ParserConsoleParametersAndInitialGame;
};

#endif
