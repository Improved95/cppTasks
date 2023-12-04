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

    virtual const string & ex_what() throw() { return msg; };
    int getErrorCode() const { return this->code; }

protected:
    int code;
    string msg;
};

class ArgumentException : public SoundProcessorException {
public:
    ArgumentException(const cxxopts::Options *options_)
            : SoundProcessorException("default_message") {
        this->code = 1;
        this->options = options_;
    }

    ArgumentException(const string &msg_, const cxxopts::Options *options_)
        : ArgumentException(options_) {
        this->msg = msg_;
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
    zeroArgumentException(const cxxopts::Options *options_)
        : ArgumentException(options_) {
        this->msg = "Too few arguments entered.";
    }
};

class MutuallyArgException : public ArgumentException {
public:
    MutuallyArgException(const string &msg_, const cxxopts::Options *options_)
        : ArgumentException(msg_, options_) {
    }
};

class ArgumentIsEntered : public ArgumentException {
public:
    ArgumentIsEntered(const string &optionName, const cxxopts::Options *options_)
        : ArgumentException(options_) {
        this->msg = "You didn't enter '" + optionName + "'.";
    }
};

class FileNameException : public ArgumentException {
public:
    FileNameException(const cxxopts::Options *options_)
        : ArgumentException("default_message", options_) {
        this->code = 2;
    }

    FileNameException(const string &fileName, const cxxopts::Options *options_)
        : FileNameException(options_) {
        this->msg = "Incorrect filename of '" + fileName + "'.";
    }
};

class FilesParserException : public SoundProcessorException {
public:
    FilesParserException() : SoundProcessorException("default_message") {
        this->code = 3;
    }
    FilesParserException(const string &msg_)
        : FilesParserException() {
        this->msg = msg_;
        this->code = 3;
    }

    virtual const string & ex_what() throw() override {
        return this->msg;
    }
};

class FileNotOpenException : public FilesParserException {
public:
    FileNotOpenException(const string &fileName)
        : FilesParserException() {
        this->msg = "File '" + fileName + "' couldn't open.";
        this->code = 4;
    }
};

class noExistConverterException : public FilesParserException {
public:
    noExistConverterException(const string &converterName)
        : FilesParserException() {
        this->msg = "Converter '" + converterName + "' doesn't exist.";
    }
};

class IncorrectParametersFormatException : public FilesParserException {
public:
    IncorrectParametersFormatException(const string &parameters)
        : FilesParserException() {
        this->msg = "Incorrect format parameters in '" + parameters + "'.";
    }
};

class IncorrectConvertersParametersException :public FilesParserException {
public:
    IncorrectConvertersParametersException(const string &parameters, const string &decs)
        : FilesParserException() {
        this->msg = "Incorrect format parameters in '" + parameters + "' in '" + decs + "'.";
    }
};

#endif
