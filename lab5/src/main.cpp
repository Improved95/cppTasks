#include "csvParser.h"

int main() {
    int r;
    std::ifstream input;
    input.open("test.csv");

    CsvParser<int, std::string, std::string, std::string, std::string> parser(&input, 0);

    r = parser.print();

    input.close();
    return r;
}
