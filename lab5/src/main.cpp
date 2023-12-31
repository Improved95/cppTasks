#include "csvParser.h"

int main() {
    int r;
    std::ifstream input;
    input.open("test.csv");

    CsvParser parser(&input, 0, '\n', ';', '\"');
    r = parser.parse();

    input.close();
    return r;
}