#include "Life.h"

bool ExceptionHandling::strtollIsCorrect(size_t &value, const string &input, const char *message) {
    try {
        value = std::stoll(input);
        if (value == 0ULL) {
            throw exception();
        }
    } catch (const exception &ex) {
        cout << message << endl;
        return false;
    }
    return true;
}
