#ifndef EXCEPTION
#define EXCEPTION

#include <iostream>
#include "cxxopts.hpp"
#include <string>
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
private:
    cxxopts::Options options;
public:
    ArgumentsExceptions(const cxxopts::Options &options_) {
        this->options = std::move(options_);
        this->returnErrorValue = 1;
    }
    int cxxoptsParsingExceptionHandling(cxxopts::ParseResult &result, int argc, char *argv[]);
    int mutuallyExclusiveArgHandling(vector<size_t> &argvs);
    int zeroArgumentExceptionHandling(int argc);
    int requiredArgumentNonExistHandling(string option, cxxopts::ParseResult &result);
};

class FileNameExceptions : public ArgumentsExceptions {
public:
    FileNameExceptions(const cxxopts::Options &options_) : ArgumentsExceptions(options_) {

    }

    int inputFileFormatIncorrectHandling(string &fileName, string pattern);
};

class FilesExceptions : public SoundProcessorExceptions {
    FilesExceptions() {
        this->returnErrorValue = 2;
    }
};

class ConvertsExceptions : public SoundProcessorExceptions {
public:
    ConvertsExceptions() {
        this->returnErrorValue = 3;
    }
};

#endif
