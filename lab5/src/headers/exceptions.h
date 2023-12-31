#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <iostream>
using std::cout;

class CsvParserExceptions : public std::exception {
public:
    CsvParserExceptions() {
        this->code = 1;
        this->msg = "The error happened.";
    }

    int getErrorCode() { return this->code; }

protected:
    int code;
    std::string msg;

    void exWhat() {
        std::cerr << this->msg << std::endl;
    }
};

class OutOfRangeOfFile : CsvParserExceptions {
    OutOfRangeOfFile() {
        this->code = 2;
    }
};

#endif
