#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int main(int argc, char* argv[]) {
//    ifstream fileIn(argv[1]);
//    if (argc < 2) return -1;
    ifstream fileIn("in.txt");
    if (!fileIn) return -1;

    string word;
    map<string, int> table;
    while (getline(fileIn, word, ' ')) {
        if () {

        } else {

        }
    }

    fileIn.close();
    return 0;
}