#ifndef LIFE_MESSAGES_H
#define LIFE_MESSAGES_H

#include <iostream>
using std::cout;
using std::endl;

class GameMessages {
public:
    void coutUserEnterRowsOrColumn(int RowsOrColumn);
    void incorrectData();
};

#endif
