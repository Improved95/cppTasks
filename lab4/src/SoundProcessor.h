#include <iostream>
#include "Converter.h"
using std::ifstream;
using std::cout;
using std::endl;
using std::string;

class CoutMessages {
public:
    void coutHelp();
    void coutErrorAndHelp(string message);
};

class ParseConsoleParameters {
public:
    int parseParametersAndInitialConvert(int argc, char **argv);
};

class SoundProcessor {
public:
    int convertWithConsoleParameters(int argc, char *argv[]);
};
