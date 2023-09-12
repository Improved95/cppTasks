#include <iostream>
#include <fstream>
#include <cctype>
#include <map>
#include <vector>
#include <algorithm>
#include "countWordsClass.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) return -1;
    ifstream fileIn(argv[1]);
    ofstream fileOut(argv[2]);
    if ((!fileIn.is_open()) || (!fileOut.is_open())) return -1;

    map<string, int> table = readFile(fileIn);
    vector<pair<string, int>> mapVector = mapSort(table);
    createOutput(mapVector, fileOut);

    fileIn.close();
    fileOut.close();
    return 0;
}