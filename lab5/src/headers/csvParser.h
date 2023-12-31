#ifndef CSV_PARSER
#define CSV_PARSER

#include <iostream>
#include "exceptions.h"

template <typename... Types>
class CsvParser {
public:
    explicit CsvParser(std::istream &input_, const size_t skipLinesNumber_ = 0, const char rowDelimeter_ = '\n',
              const char columnDelimeter_ = ';', const char screeningSymbol_ = '"')
              : input(input_), rowDelimeter(rowDelimeter_),
              columnDelimeter(columnDelimeter_), screeningSymbol(screeningSymbol_) {

        skipLines(skipLinesNumber_);
    }

    class Iterator {
    public:
        Iterator(const CsvParser &parser_, const size_t currentLineNumber_) :
                parser(parser_), currentLineNumber(currentLineNumber_) {
            (*this)++;
        }

        Iterator & operator ++ () {
            return (*this);
        }
        bool operator != (const Iterator &temp) const {
            return true;
        }
        std::tuple<Types...> & operator * () {
            return this->currentTuple;
        }

    private:
        CsvParser<Types ...> parser;
        size_t currentLineNumber = 0;
        std::tuple<Types ...> currentTuple;

        friend CsvParser<Types ...>;
    };

    Iterator & begin() {
        return Iterator();
    }
    Iterator & end() {
        return Iterator();
    }

private:
    std::istream &input;
    char rowDelimeter;
    char columnDelimeter;
    char screeningSymbol;

    int skipLines(const size_t skipLinesNumber) {
        std::string line;
        for (size_t i = 0; i < skipLinesNumber; i++) {
            if (!getline(this->input, line, this->rowDelimeter)) {
                throw std::out_of_range("You are out of file.");
            }
        }
        return 0;
    }
};

#endif
