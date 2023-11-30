#ifndef EXCEPTION
#define EXCEPTION

#include <iostream>
#include "cxxopts.hpp"
#include "Messages.h"
using std::string;
using std::exception;

class SoundProcessorException : public exception, public Concatenation {
public:
    SoundProcessorException(const char * msg_) {
        this->msg = msg_;
        this->code = 0;
    }

    virtual const char * what() throw() { return msg; };
    virtual string ex_what() throw() = 0;

    const int getErrorCode() const { return this->code; }

protected:
    int code;
    const char *msg;
};

class ArgumentException : public SoundProcessorException {
public:
    ArgumentException(const char * msg_, const cxxopts::Options *options_)
        : SoundProcessorException(msg_) {
        this->code = 1;
        this->options = options_;
    }

    virtual string ex_what() throw() override {
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

class FilesParserException : public SoundProcessorException {
public:
    FilesParserException(const char * msg_)
            : SoundProcessorException(msg_) {
        this->code = 3;
    }

    virtual string ex_what() throw() override {
        string message;
        message.assign(this->msg);
        return message;
    }
};

class FileNotOpenException : public FilesParserException {
public:
    FileNotOpenException(const char * msg_) : FilesParserException(msg_) {
        this->code = 4;
    }
};

class noExistConverterException : public FilesParserException {
public:
    noExistConverterException(const char * msg_) : FilesParserException(msg_) {}
};

#endif
