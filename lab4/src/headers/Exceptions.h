#ifndef EXCEPTION
#define EXCEPTION

#include <iostream>
#include "cxxopts.hpp"
#include "Messages.h"
using std::string;
using std::exception;
using std::to_string;

class SoundProcessorException : public exception {
public:
    SoundProcessorException() {
        this->code = 0;
        this->msg = "error happend";
    }

    virtual const string & ex_what() throw() { return msg; };
    int getErrorCode() const { return this->code; }

protected:
    int code;
    string msg;
};

class ArgumentException : public SoundProcessorException {
public:
    ArgumentException(const cxxopts::Options *options_) {
        this->code = 1;
        this->options = options_;
    }

    ArgumentException(const string &msg_, const cxxopts::Options *options_)
        : ArgumentException(options_) {
        this->msg = msg_ + ("\nHelp list:\n" + this->options->help());;
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
        : ArgumentException(options_) {
        this->code = 2;
    }

    FileNameException(const string &fileName, const cxxopts::Options *options_)
        : FileNameException(options_) {
        this->msg = "Incorrect filename of '" + fileName + "'.";
    }
};

class FilesParserException : public SoundProcessorException {
public:
    FilesParserException() {
        this->code = 3;
    }
    FilesParserException(const string &msg_) : FilesParserException() {
        this->msg = msg_;
        this->code = 3;
    }
};

class FileNotOpenException : public FilesParserException {
public:
    FileNotOpenException(const string &fileName) {
        this->msg = "File '" + fileName + "' couldn't open.";
        this->code = 4;
    }
};

class noExistConverterException : public FilesParserException {
public:
    noExistConverterException(const string &converterName) {
        this->msg = "Converter '" + converterName + "' doesn't exist.";
    }
};

class IncorrectParametersFormatException : public FilesParserException {
public:
    IncorrectParametersFormatException(const string &parameters) {
        this->msg = "Incorrect format parameters in '" + parameters + "'.";
        this->code = 7;
    }
    IncorrectParametersFormatException(const string &parameters, const string &what) {
        this->msg = "Incorrect format parameters in '" + parameters + "'" + what + ".";
        this->code = 7;
    }
};

class NotEnoughInputsException : public SoundProcessorException {
public:
    NotEnoughInputsException(const size_t msg_) {
        this->msg = "Not enought inputs. You didn't enter '" +
                to_string(msg_ + 1) + "' input.";
        this->code = 5;
    }
};

class FilesFormatExceptions : public FilesParserException {
public:
    FilesFormatExceptions(const string &fileName) {
        this->msg = "Incorrect format in '" + fileName + "' file.";
    }
};

#endif
