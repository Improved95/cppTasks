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
              const char columnDelimeter_ = ';', const char quoteSymbol_ = '"')
              : input(input_), rowDelimeter(rowDelimeter_),
              columnDelimeter(columnDelimeter_), quoteSymbol(quoteSymbol_) {
        skipLines(skipLinesNumber_);
    }

    class Iterator {
    public:
        Iterator(CsvParser &parser_, size_t currentLineNumber_, const int isEnd) :
            parser(parser_), currentLineNumber(currentLineNumber_) {
            if (!isEnd) { ++(*this); } //if you can take end element, then happens nothing
        }

        void operator ++() {
            std::string line;
            if (getline(this->parser.input, line, this->parser.rowDelimeter)) {
                this->currentTuple = parser.ParseLine(line, std::index_sequence_for<Types...>{});
                this->parser.linesNumber++;
            }
            currentLineNumber++;
        }
        bool operator !=(const Iterator &) {
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

    template<std::size_t ...Is>
    std::tuple<Types...> ParseLine(std::string &stringLine, std::index_sequence<Is...>) {
        std::stringstream streamLine(stringLine);
        return std::make_tuple(ParseField<Types>(streamLine, Is)...);
    }

    template<typename FieldType>
    FieldType ParseField(std::stringstream &streamLine, const size_t columnNumber) {
        std::string stringField;
        getline(streamLine, stringField, this->columnDelimeter);
        if (stringField[0] == this->quoteSymbol) {
            if (stringField[stringField.size() - 1] == this->quoteSymbol) {
                stringField = stringField.substr(1, stringField.size() - 2);
            } else {
                throw IncorrectDataFormat("Incorrect format of data in " + std::to_string(this->linesNumber + 1) +
                    " row, " + std::to_string(columnNumber) + " column.");
            }
        }

        if constexpr (std::is_same_v<FieldType, int>) {
            size_t converterCharsNumber;
            long long value = std::stoll(stringField, &converterCharsNumber);
            if (converterCharsNumber != stringField.size()) {
                throw IncorrectDataFormat("Incorrect format of data in " + std::to_string(this->linesNumber) +
                                            " row, " + std::to_string(columnNumber) + " column.");
            }
            return value;
        } else {
            return stringField;
        }
    }

private:
    std::istream &input;
    char rowDelimeter;
    char columnDelimeter;
    char quoteSymbol;
    size_t linesNumber = 0;

    int skipLines(const size_t skipLinesNumber) {
        std::string line;
        for (size_t i = 0; i < skipLinesNumber; i++) {
            if (!getline(this->input, line, this->rowDelimeter)) {
                throw OutOfRangeFile();
            }
            linesNumber++;
        }
        return 0;
    }
};

#endif
