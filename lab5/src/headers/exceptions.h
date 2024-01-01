#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <iostream>

class CsvParserExceptions : public std::exception {
public:
    CsvParserExceptions() {
        this->errorCode = 1;
        this->msg = "The error happened.";
    }

    void exWhat() {
        std::cerr << this->msg << std::endl;
    }
    int getCode() {
        return this->errorCode;
    }

protected:
    int errorCode;
    std::string msg;
};

class OutOfRangeFile : public CsvParserExceptions {
public:
    OutOfRangeFile() {
        this->errorCode = 2;
        this->msg = "You are out of file.";
    }
};

class IncorrectDataFormat : public CsvParserExceptions {
public:
    IncorrectDataFormat(const std::string &msg_) {
        this->errorCode = 3;
        this->msg = msg_;
    }
};

#endif
