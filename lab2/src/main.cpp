#include "CircularBuffer.h"

int main() {
    CircularBuffer<int> cb1(8);
    for (int i = 0; i < 5; i++) {
        cb1.push_back(i + 1);
    }

    CircularBuffer<int> cb2(4);
    for (int i = 0; i < 5; i++) {
        cb2.push_back(i + 1);
    }

    CircularBuffer<int> cb3(cb2);

    cb3.swap(cb1);
    cout << "" << endl;

    return 0;
}
