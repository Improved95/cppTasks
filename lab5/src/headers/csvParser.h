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

    std::tuple<Types...> & ParseLine(std::string &line) {
        const size_t tupleSize = std::tuple_size<Types...>::value;
        return { ParseField(std::make_index_sequence<tupleSize>{}) };
    }

    template<typename FieldType, std::size_t... Is>
    FieldType ParseField(std::index_sequence<Is...>) {

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
        }
        bool operator != (const Iterator &temp) const {
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
