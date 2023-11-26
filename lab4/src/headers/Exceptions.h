#ifndef EXCEPTION
#define EXCEPTION

#include "cxxopts.hpp"
#include "string"
#include <vector>
using std::vector;
using std::string;
using std::exception;

class SoundProcessorExceptions {
protected:
    int returnErrorValue = 0;
    void showMessageError(string message);
};

class ArgumentsExceptions : public SoundProcessorExceptions {
public:
    ArgumentsExceptions() {
        this->returnErrorValue = 1;
    }
    int cxxoptsParsingExceptionHandling(cxxopts::ParseResult &result, int argc, char *argv[], cxxopts::Options options);
    int mutuallyExclusiveArgHandling(vector<size_t> &argvs);
    int inputFileFormatIncorrectHandling(string &string);
};

class FilesExceptions : public SoundProcessorExceptions {

};

class ConvertsExceptions : public SoundProcessorExceptions {
public:

};

#endif
