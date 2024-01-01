#include <fstream>
#include "tuplePrint.h"
#include "csvParser.h"

int main() {
    int r = 0;
    std::ifstream input;
    input.open("test.csv");

    CsvParser<int, std::string, std::string, std::string, std::string> parser(input, 0, '\n', ',', '"');

    for (auto &el : parser) {
        std::cout << el << std::endl;
    }

    input.close();
    return r;
}
