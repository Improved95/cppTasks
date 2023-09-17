#ifndef COUNTWORDSCLASS_H
#define COUNTWORDSCLASS_H

#include "head.h"
using namespace std;

class CountWordsClass {
private:
    map<string, int> table;

    map<string, int> readFile(istream& fileIn);
    vector<pair<string, int>> mapSort();
    void createOutput(ostream& fileOut, vector<pair<string, int>>);

public:
    void countingWordsFromFile(istream& fileIn, ostream& fileOut);
};

#endif //COUNTWORDSCLASS_H
