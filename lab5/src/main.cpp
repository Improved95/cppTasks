#include "tuplePrint.h"

int main() {
    std::tuple tp { 10, 21, "hello", 90.5};
    std::cout << tp << '\n';

    return 0;
}