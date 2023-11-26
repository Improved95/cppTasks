#ifndef SOUND_PROCESSOR
#define SOUND_PROCESSOR

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cxxopts.hpp>
using std::ifstream;
using std::fstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::exception;

class CoutMessages {
public:
    void coutConfigExample();
    void coutErrorAndHelp(string message);
    void coutError(string message);
};

class SoundProcessorExceptions {

};

class ParsersExceptions : public SoundProcessorExceptions {
public:
    int cxxoptsParsingExceptionHandling(cxxopts::ParseResult &result, int argc, char *argv[], cxxopts::Options options);
};

class ConvertsExceptions : public SoundProcessorExceptions {
public:

};

class ParseConsoleArguments {
public:
    int parseArgumentsAndInitialConvert(int argc, char **argv);
};

class SoundProcessor {
public:
    int convertWithConsoleArguments(int argc, char *argv[]);
};

#endif
