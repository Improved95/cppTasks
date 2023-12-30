#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <iostream>
using std::string;
using std::exception;

class CsvParserExceptions : public exception {
public:
    CsvParserExceptions() {
        this->code = 1;
        this->msg = "The error happened.";
    }

protected:
    int code;
    string msg;
};

#endif
