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
using std::cin;

class Life;

class FileParser {
    void inputFileParser();
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

    void randomFieldInitial();
};

class Life {
private:
    string gameName;

    void initilizedDataFromConsole();
    void initilizedDataFromFile(ifstream &inputData);
    void offlineGame(ifstream &inputData, size_t ticks, ofstream &outputData);

public:
    void initialGame();
    void initialGame(ifstream &inputData);
    void initialGame(ifstream &inputData, size_t ticks, ofstream &outputData);

    void initialGameWithConsoleParameters(int argc, char **argv);

    friend ParserConsoleParametersAndInitialGame;
};

#endif
