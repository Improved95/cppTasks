#include <iostream>
#include <cctype>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

bool cmp(pair<string, int> a, pair<string, int> b) {
    return a.second > b.second;
}

vector<pair<string, int>> mapSort(map<string, int> map) {
    vector<pair<string, int> > mapVector;
    for (auto it : map) {
        mapVector.push_back(it);
    }

    sort(mapVector.begin(), mapVector.end(), cmp);
    return mapVector;
}

void createOutput(vector<pair<string, int>> mapVector, ofstream& fileOut) {
    size_t wordsQuantity = 0;
    for(auto& it: mapVector) {
        wordsQuantity += it.second;
    }
    for(auto& it: mapVector) {
        fileOut << it.first << ";" << it.second << ";" << (it.second * 100) / wordsQuantity << endl;
    }
}

bool isAlphaNumeric(char c) {
    return isalnum(static_cast<unsigned char>(c)) != 0;
}

map<string, int> readFile(ifstream& fileIn) {
//    while (getline(fileIn, word, ' ')) {
//        if (table.find(word) == table.end()) {
//            table[word] = 1;
//        } else {
//            table[word] += 1;
//        }
//    }

//    char character;
//    while(fileIn.get(character)) {
//        if (('A' <= character and character <= 'Z') or ('a' <= character and character <= 'z') or ('0' <= character and character <= '9')) {
//            word += character;
//        } else {
//            if (table.find(word) == table.end()) {
//                table[word] = 1;
//            } else {
//                table[word] += 1;
//            }
//            word = "";
//        }
//    }

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

int main(int argc, char* argv[]) {
//    ifstream fileIn(argv[1]);
//    if (argc < 2) return -1;
    ifstream fileIn("in.txt");
    ofstream fileOut("out.csv");
    if ((!fileIn) or (!fileOut)) return -1;

    map<string, int> table = readFile(fileIn);
    vector<pair<string, int>> mapVector = mapSort(table);
    createOutput(mapVector, fileOut);

    fileIn.close();
    return 0;
}