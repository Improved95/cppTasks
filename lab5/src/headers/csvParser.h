#ifndef CSV_PARSER
#define CSV_PARSER

#include <iostream>
#include <sstream>
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


    std::tuple<Types...> ParseLine(std::string &stringLine) {
        std::stringstream streamLine(stringLine);
//        return { ( ParseField<Types>(), ... ) };
//        return std::make_tuple<Types...>(1, "hello");
        return std::make_tuple<Types...>((ParseField<Types>(), ...));
    }

    template<typename FieldType>
    FieldType ParseField() {

    }

    class Iterator {
    public:
        Iterator(CsvParser &parser_, size_t currentLineNumber_) :
            parser(parser_), currentLineNumber(currentLineNumber_) {
            ++(*this);
        }

        Iterator & operator ++ () {
            std::string line;
            std::getline(this->parser.input, line);
            this->currentTuple = parser.ParseLine(line);
            return *this;
        }
        bool operator != (const Iterator &temp) {
            return true;
        }
        std::tuple<Types...> & operator * () {
            return this->currentTuple;
        }

    private:
        std::tuple<Types ...> currentTuple;
        CsvParser<Types ...> &parser;
        size_t currentLineNumber = 0;
    };

    Iterator begin() {
        return Iterator(*this, 0);
    }
    Iterator end() {
        return Iterator(*this, linesNumber);
    }

private:
    std::istream &input;
    char rowDelimeter;
    char columnDelimeter;
    char screeningSymbol;
    size_t linesNumber = 0;

    int skipLines(const size_t skipLinesNumber) {
        std::string line;
        for (size_t i = 0; i < skipLinesNumber; i++) {
            if (!getline(this->input, line, this->rowDelimeter)) {
                throw std::out_of_range("You are out of file.");
            }
            linesNumber++;
        }
        return 0;
    }
};

#endif
