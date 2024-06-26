#include "../headers/head.h"
#include "../headers/CountWordsClass.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) return -1;
    fstream fileIn, fileOut;
    fileIn.open(argv[1], fstream::in);
    fileOut.open(argv[2], fstream::out);
    if ((!fileIn.is_open()) || (!fileOut.is_open())) return -1;

    CountWordsClass countWords;
    countWords.countingWordsFromFile(fileIn, fileOut);

    fileIn.close();
    fileOut.close();
    return 0;
}