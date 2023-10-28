#include "Life.h"

bool ExceptionHandling::strtollIsCorrect(long long &rows, const string &input, const char *message) {
    try {
        rows = std::stoll(input);
        if (rows == 0ULL) {
            throw exception();
        }
    } catch (const exception &ex) {
        cout << message << endl;
        return false;
    }
    return true;
}
