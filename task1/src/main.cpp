#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
//    ifstream fileIn(argv[1]);
//    if (argc < 2) return -1;
    ifstream fileIn("in.txt");
    if (!fileIn) return -1;
    string word;
    fileIn.getLine(word, 1500, ' ');

    fileIn.close();
    return 0;
}