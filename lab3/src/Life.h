#ifndef LIFE_H
#define LIFE_H

#include <iostream>
#include "GameMessages.h"
using std::string;
using std::cout;
using std::endl;

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

    void gameMode(size_t argc, char **argv);

    void gameWithoutInitialData(GameMessages messages);
    void gameWithInitialData(GameMessages messages, char **argv);
    void offlineGame(GameMessages messages, char **argv);

public:
    void initialGame(size_t argc, char **argv);
    void initialGame();
};

#endif
