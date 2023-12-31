#ifndef CSV_PARSER
#define CSV_PARSER

#include <iostream>
#include <fstream>

class CsvParser {
public:
    CsvParser(std::ifstream *input_, const size_t skipLinesNumber_, const char rowDelimeter_,
              const char columnDelimeter_, const char screeningSymbol_) {
        this->input = input_;
        this->skipLinesNumber = skipLinesNumber_;
        this->rowDelimeter = rowDelimeter_;
        this->columnDelimeter = columnDelimeter_;
        this->screeningSymbol = screeningSymbol_;
    }

    int parse();

private:
    std::ifstream *input;
    size_t skipLinesNumber;
    char rowDelimeter;
    char columnDelimeter;
    char screeningSymbol;


};

#endif