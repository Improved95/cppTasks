#include "CircularBuffer.h"

int main() {
    CircularBuffer<int> cb1(7);
    for (int i = 0; i < 8; i++) {
        cb1.push_back(i);
    }
    cb1.pop_back();
    cb1.pop_back();

    cb1.insert(2, 20);

    cout << "" << endl;

    return 0;
}
