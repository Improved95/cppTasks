#include "../headers/head.h"
#include "../headers/countWordsClass.h"
using namespace std;

countWordsClass::countWordsClass() {}

bool cmp(pair<string, int>& a, pair<string, int>& b) {
    return a.second > b.second;
}

bool isAlphaNumeric(char c) {
    return isalnum(static_cast<unsigned char>(c)) != 0;
}

vector<pair<string, int>> countWordsClass::mapSort(map<string, int>& map) {
    vector<pair<string, int> > mapVector;
    for (auto& it : map) {
        mapVector.push_back(it);
    }

    sort(mapVector.begin(), mapVector.end(), cmp);
    return mapVector;
}

void countWordsClass::createOutput(vector<pair<string, int>>& mapVector, fstream& fileOut) {
    size_t wordsQuantity = 0;
    for (auto& it : mapVector) {
        wordsQuantity += it.second;
    }
    for (auto& it : mapVector) {
        fileOut << it.first << ";" << it.second << ";" << (it.second * 100.00) / wordsQuantity << "\n";
    }
}

map<string, int> countWordsClass::readFile(fstream& fileIn) {
    string word;
    char character;
    map<string, int> table;
    while(fileIn.get(character)) {
        if (isAlphaNumeric(character)) {
            word += character;
        } else if (!word.empty()) {
            if (table.find(word) == table.end()) {
                table[word] = 1;
            } else {
                table[word] += 1;
            }
            word.clear();
        }
    }

    if (!word.empty()) {
        if (table.find(word) == table.end()) {
            table[word] = 1;
        } else {
            table[word] += 1;
        }
        word.clear();
    }

    return table;
}
