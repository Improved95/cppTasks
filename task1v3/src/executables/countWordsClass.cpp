#include "../headers/head.h"
#include "../headers/CountWordsClass.h"
using namespace std;

bool cmp(pair<string, int>& a, pair<string, int>& b) {
    return a.second > b.second;
}

bool isAlphaNumeric(char c) {
    return isalnum(static_cast<unsigned char>(c)) != 0;
}

vector<pair<string, int>> CountWordsClass::mapSort() {
    vector<pair<string, int>> mapVector;
    for (auto& it : table) {
        mapVector.push_back(it);
    }

    sort(mapVector.begin(), mapVector.end(), cmp);
    return mapVector;
}

void CountWordsClass::createOutput(ostream& fileOut, vector<pair<string, int>> mapVector) {
    size_t wordsQuantity = 0;
    for (auto& it : mapVector) {
        wordsQuantity += it.second;
    }
    for (auto& it : mapVector) {
        fileOut << it.first << ";" << it.second << ";" << (it.second * 100.00) / wordsQuantity << "\n";
    }
}

map<string, int> CountWordsClass::readFile(istream& fileIn) {
    string word;
    char character;
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

void CountWordsClass::countingWordsFromFile(istream& fileIn, ostream& fileOut) {
        table = readFile(fileIn);
        vector<pair<string, int>> mapVector = mapSort();
        createOutput(fileOut, mapVector);
}

void CountWordsClass::clearTable() {
    table.clear();
}