#include "Life.h"

bool ExceptionHandling::strtoullCheck(size_t &rows, const string &input, const char *message) {
    try {
        rows = std::stoull(input);
        if (rows == 0ULL) {
            throw exception();
        }
    } catch (const exception &ex) {
        cout << message << endl;
        return true;
    }
    return false;
}
