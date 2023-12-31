#ifndef CSV_PARSER
#define CSV_PARSER

#include <iostream>
#include <fstream>
#include "exceptions.h"

template <typename... Types>
class CsvParser {
public:
    explicit CsvParser(std::ifstream *input_, const size_t skipLinesNumber_ = 0, const char rowDelimeter_ = '\n',
              const char columnDelimeter_ = ';', const char screeningSymbol_ = '"')
              : input(input_), skipLinesNumber(skipLinesNumber_), rowDelimeter(rowDelimeter_),
              columnDelimeter(columnDelimeter_), screeningSymbol(screeningSymbol_) {

        skipLines();

    }

    class CsvIterator {
    public:
        CsvIterator() {

        }
    private:
        std::ifstream *input;
    };

    int print();

private:
    std::ifstream *input;
    size_t skipLinesNumber;
    char rowDelimeter;
    char columnDelimeter;
    char screeningSymbol;

    size_t getFileSize();
    int skipLines();
};

#endif
