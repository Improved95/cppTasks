#include <iostream>
#include <fstream>
#include <string>
#include "Converter.h"
using std::ifstream;
using std::cout;
using std::endl;
using std::string;

class CoutMessages {
public:
    void coutHelp();
    void coutErrorAndHelp(string message);
    void coutError(string message);
};

class ParseConsoleArguments {
private:
    int parseConfigFileName(char *argv[]);
    int parseWavFilesName(int argc, char *argv[]);
public:
    int parseArgumentsAndInitialConvert(int argc, char **argv);
};

class SoundProcessor {
public:
    int convertWithConsoleArguments(int argc, char *argv[]);
};
