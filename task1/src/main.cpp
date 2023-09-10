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

int createOutput(vector<pair<string, int>> mapVector) {
    ofstream fileOut("out.csv");
    if (!fileOut) return -1;

    size_t wordsQuantity = 0;
    for(auto& it: mapVector) {
        wordsQuantity += it.second;
    }
    for(auto& it: mapVector) {
        fileOut << it.first << ";" << it.second << ";" << (it.second * 100) / wordsQuantity << endl;
    }

    return 0;
}

int main(int argc, char* argv[]) {
//    ifstream fileIn(argv[1]);
//    if (argc < 2) return -1;
    ifstream fileIn;
    fileIn.open("in.txt");
    if (!fileIn) return -1;

    string word;
    map<string, int> table;
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



    vector<pair<string, int>> mapVector = mapSort(table);
    if (createOutput(mapVector) == -1) return -1;

    fileIn.close();
    return 0;
}