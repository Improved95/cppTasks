#ifndef COUNTWORDSCLASS_H
#define COUNTWORDSCLASS_H

#include "head.h"
using namespace std;

class countWordsClass {
private:
    map<string, int> table;
    vector<pair<string, int>> mapVector;

    map<string, int> readFile(fstream& fileIn);
    vector<pair<string, int>> mapSort();
    void createOutput(fstream& fileOut);

public:
    countWordsClass();
    void callMainFunctions(fstream& fileIn, fstream& fileOut) {
        table = readFile(fileIn);
        mapVector = mapSort();
        createOutput(fileOut);
    };
};

#endif //COUNTWORDSCLASS_H
