#ifndef SOUND_PROCESSOR
#define SOUND_PROCESSOR

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::ifstream;
using std::fstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class OpenFilesSmartPointers {
private:
    fstream *ptr;
public:
    OpenFilesSmartPointers(fstream *ptr_) {
        this->ptr = ptr_;
    }
    ~OpenFilesSmartPointers() {
        (*this->ptr).close();
    }
    //разыменование
};

class CoutMessages {
public:
    void coutHelp();
    void coutErrorAndHelp(string message);
    void coutError(string message);
};

class ParseConsoleArguments {
private:
    int parseConfigFileArg(char **argv, vector<OpenFilesSmartPointers> &openedFilesVector);
    int parseWavFilesArg(int argc, char **argv, vector<OpenFilesSmartPointers> &filesVector);
public:
    int parseArgumentsAndInitialConvert(int argc, char **argv);
};

class SoundProcessor {
public:
    int convertWithConsoleArguments(int argc, char *argv[]);
};

#endif
