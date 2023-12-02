#ifndef EXCEPTION
#define EXCEPTION

#include <iostream>
#include "cxxopts.hpp"
#include "Messages.h"
using std::string;
using std::exception;

class SoundProcessorException : public exception {
public:
    SoundProcessorException(const string &msg_) {
        this->msg = msg_;
        this->code = 0;
    }

    virtual const char * what() throw() { return msg.c_str(); };
    virtual const string & ex_what() throw() { return msg; };

    const int getErrorCode() const { return this->code; }

protected:
    int code;
    string msg;
};

class ArgumentException : public SoundProcessorException {
public:
    ArgumentException(const string &msg_, const cxxopts::Options *options_)
        : SoundProcessorException(msg_) {
        this->code = 1;
        this->options = options_;
    }

    virtual const string & ex_what() throw() override {
        this->msg += ("\nHelp list:\n" + this->options->help());
        return this->msg;
    }

protected:
    const cxxopts::Options *options;
};

class zeroArgumentException : public ArgumentException {
public:
    zeroArgumentException(const string &msg_, const cxxopts::Options *options_)
        : ArgumentException(msg_, options_) {}
};

class MutuallyArgException : public ArgumentException {
public:
    MutuallyArgException(const string &msg_, const cxxopts::Options *options_)
        : ArgumentException(msg_, options_) {}
};

class ArgumentIsEntered : public ArgumentException {
public:
    ArgumentIsEntered(const string &msg_, const cxxopts::Options *options_)
        : ArgumentException(msg_, options_) {}
};

class FileNameException : public ArgumentException {
public:
    FileNameException(const string &msg_, const cxxopts::Options *options_)
        : ArgumentException(msg_, options_) {
        this->code = 2;
    }
};

class FilesParserException : public SoundProcessorException {
public:
    FilesParserException(const string &msg_)
            : SoundProcessorException(msg_) {
        this->code = 3;
    }

    virtual const string & ex_what() throw() override {
        return this->msg;
    }
};

class FileNotOpenException : public FilesParserException {
public:
    FileNotOpenException(const string &msg_) : FilesParserException(msg_) {
        this->code = 4;
    }
};

class noExistConverterException : public FilesParserException {
public:
    noExistConverterException(const string &msg_) : FilesParserException(msg_) {}
};

class IncorrectParametersFormatException : public FilesParserException {
public:
    IncorrectParametersFormatException(const string &msg_) : FilesParserException(msg_) {}
};

#endif
