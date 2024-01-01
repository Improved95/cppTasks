#ifndef CSV_PARSER
#define CSV_PARSER

#include <iostream>
#include <sstream>
#include <typeinfo>
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

    template<std::size_t ...Is>
    std::tuple<Types...> ParseLine(std::string &stringLine, std::index_sequence<Is...>) {
        std::stringstream streamLine(stringLine);

        return std::make_tuple(ParseField<Types, Is>()...);
//        return std::make_tuple<Types...>(1, "fsd");
    }

    template<typename FieldType, size_t I>
    FieldType ParseField() {
        if constexpr (typeid(FieldType) == typeid(int)) {
            return 5;
        } else {
            return "hello";
        }

//        FieldType A;
//        return A;
    }

    class Iterator {
    public:
        Iterator(CsvParser &parser_, size_t currentLineNumber_, const int isEnd) :
            parser(parser_), currentLineNumber(currentLineNumber_) {
            if (!isEnd) { ++(*this); } //if you can take end element, then happens nothing
        }

        void operator ++() {
            std::string line;
            if (std::getline(this->parser.input, line, this->parser.rowDelimeter)) {
                this->currentTuple = parser.ParseLine(line, std::index_sequence_for<Types...>{});
                this->parser.linesNumber++;
            }
            currentLineNumber++;
        }
        bool operator !=(const Iterator &temp) {
            return (this->currentLineNumber == this->parser.linesNumber);
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
        return Iterator(*this, 0, 0);
    }
    //iterator end don't work specially
    Iterator end() {
        return Iterator(*this, linesNumber, 1);
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
