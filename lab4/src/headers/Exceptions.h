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

    virtual const char * what() throw() { return msg; };
    virtual string sp_what() throw() = 0;

    int getErrorCode() { return this->code; }

protected:
    int code;
    const char *msg;
};

class ArgumentException : public SoundProcessorException {
public:
    ArgumentException(const char * msg_, const cxxopts::Options *options_) : SoundProcessorException(msg_) {
        this->code = 1;
        this->options = options_;
    }

    virtual string sp_what() throw() override {
        string message;
        message.assign(this->msg);
        message += ((string)"\nHelp list:\n" + this->options->help());
        return message;
    }

protected:
    const cxxopts::Options *options;
};

class zeroArgumentException : public ArgumentException {
public:
    zeroArgumentException(const char * msg_, const cxxopts::Options *options_)
        : ArgumentException(msg_, options_) {}
};

class MutuallyArgException : public ArgumentException {
public:
    MutuallyArgException(const char * msg_, const cxxopts::Options *options_)
        : ArgumentException(msg_, options_) {}
};

class ArgumentIsEntered : public ArgumentException {
public:
    ArgumentIsEntered(const char * msg_, const cxxopts::Options *options_)
        : ArgumentException(msg_, options_) {}
};

class FileNameException : public ArgumentException {
public:
    FileNameException(const char * msg_, const cxxopts::Options *options_)
        : ArgumentException(msg_, options_) {
        this->code = 2;
    }
};

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
