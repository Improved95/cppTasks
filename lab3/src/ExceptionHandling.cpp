#include "Life.h"

/*�������� ������ ��� ������ ���������� ���������� �����, ��, ������������� ����� ������
 * �������������, �� ��� ����� �������� �����������, ��, ������������� � �����*/
bool ExceptionHandling::coordinateIsCorrect(size_t &value, const size_t maxValue, const string &input, const char *message) {
    size_t numCharsConverted = 0;
    bool reverseCoordinate = false;
    string newInput = input;

    // ��������� ������������� �����
    size_t newInputSize = newInput.size();
    if (input[0] == '-') {
        newInput = input.substr(1, input.size());
        newInputSize = newInput.size();
        reverseCoordinate = true;
    }

    try {
        value = std::stoull(newInput, &numCharsConverted);
        value = value % maxValue;
        if (reverseCoordinate) {
            value = maxValue - value;
        }
        if (numCharsConverted != newInputSize) {
            throw exception();
        }
    } catch (const exception &ex) {
        cout << message << endl;
        return false;
    }
    return true;
}
