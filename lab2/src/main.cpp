#include "CircularBuffer.h"

int main() {
    CircularBuffer<int> cb1(7);
    for (int i = 0; i < 11; i++) {
        cb1.push_back(i + 1);
    }

    cb1.rotate(5);

    cout << "" << endl;

    return 0;
}
