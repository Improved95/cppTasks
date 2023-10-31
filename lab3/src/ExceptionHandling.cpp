#include "Life.h"

/*выдает модуль числа*/
bool ExceptionHandling::strtoullIsCorrect(size_t &value, const string &input, const char *message) {
    size_t numCharsConverted = 0;
    string newInput = input;

    // обработка отрицательных чисел
    size_t newInputSize = newInput.size();
    if (input[0] == '-') {
        newInput = input.substr(1, input.size());
        newInputSize = newInput.size();

    }

    try {
        value = std::stoull(newInput, &numCharsConverted);
        if (numCharsConverted != newInputSize) {
            throw exception();
        }
    } catch (const exception &ex) {
        cout << message << endl;
        return false;
    }
    return true;
}
