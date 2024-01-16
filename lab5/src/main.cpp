#include <fstream>
#include "tuplePrint.h"
#include "csvParser.h"

int main() {
    int r = 0;
    std::ifstream input;
    input.open("test.csv");
    if (!input.is_open()) { return -1; }

    CsvParser<std::string, int> parser(input, 0, '\n', ',', '"');

    try {
        for (auto &el: parser) {
            std::cout << el << std::endl;
        }
    } catch (CsvParserExceptions &ex) {
        ex.exWhat();
        r = ex.getCode();
    }

    input.close();
    return r;
}
