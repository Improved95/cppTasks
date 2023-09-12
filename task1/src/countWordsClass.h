#ifndef TASK1_COUNTWORDSCLASS_H
#define TASK1_COUNTWORDSCLASS_H

#include <iostream>
#include <map>
using namespace std;

class countWordsClass {
    bool cmp(pair<string, int>& a, pair<string, int>& b);
    vector<pair<string, int>> mapSort(map<string, int>& map);
    void createOutput(vector<pair<string, int>>& mapVector, ofstream& fileOut);
    bool isAlphaNumeric(char c);
    map<string, int> readFile(ifstream& fileIn);


};

#endif //TASK1_COUNTWORDSCLASS_H
