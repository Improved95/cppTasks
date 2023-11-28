#ifndef EXCEPTION
#define EXCEPTION

#include <iostream>
#include "cxxopts.hpp"
#include <string>
#include <vector>
using std::vector;
using std::string;
using std::exception;

class SoundProcessorException : public exception {
public:
    SoundProcessorException(const char * msg_) {
        this->msg = msg_;
        this->code = 0;
    }

    virtual const char * what() throw() {
        return msg;
    };
    int getErrorCode() { return this->code; }

protected:
    int code;
    const char *msg;
};

class ArgumentException : public SoundProcessorException {
public:
    ArgumentException(const char * msg_, cxxopts::Options *options_) : SoundProcessorException(msg_) {
        setOptions(options_);
        this->code = 1;
    }
    static void setOptions(cxxopts::Options *options_) { consoleOptions = options_; }

private:
    static cxxopts::Options *consoleOptions;
};

/*
class FileNameException : public SoundProcessorExceptions {

};
*/


/*
class ArgumentsExceptions : public SoundProcessorExceptions {
protected:
    cxxopts::Options options;
public:
    ArgumentsExceptions(const cxxopts::Options &options_) {
        this->options = std::move(options_);
        this->returnErrorValue = 1;
    }
    int checkCxxoptsParsing(cxxopts::ParseResult &result, int argc, char *argv[]);
    int checkMutuallyExclusiveArg(vector<size_t> &argvs);
    int checkZeroArguments(int argc);
    int checkRequiredArgument(string option, cxxopts::ParseResult &result);
};

class FileNameExceptions : public ArgumentsExceptions {
public:
    FileNameExceptions(const cxxopts::Options &options_) : ArgumentsExceptions(options_) {}
    int checkInputFileFormat(string &fileName, string pattern);
};

class FileNameWithDiffExtentionsExceptions : public FileNameExceptions {
private:
    const string supportFormats[1]  = {"wav"};
    const string mainPattern = "[A-Za-z0-9]+[.]";
public:
    FileNameWithDiffExtentionsExceptions(const cxxopts::Options &options_) : FileNameExceptions(options_) {}

    int checkTxtFileName(string &fileName);
    int checkInputFileWithDiffFormat(string &fileName);
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
*/

#endif
