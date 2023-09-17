#ifndef COUNTWORDSCLASS_H
#define COUNTWORDSCLASS_H

#include "head.h"
using namespace std;

class CountWordsClass {
private:
    map<string, int> table;

    map<string, int> readFile(istream& fileIn);
    void createOutput(ostream& fileOut, vector<pair<string, int>>);

public:
    vector<pair<string, int>> mapSort();
    void countingWordsFromFile(istream& fileIn, ostream& fileOut);
    void clearTable();
};

#endif //COUNTWORDSCLASS_H
