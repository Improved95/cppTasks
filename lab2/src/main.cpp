#include "CircularBuffer.h"

int main() {
    CircularBuffer<int> cb1(7);
    for (int i = 0; i < 9; i++) {
        cb1.push_back(i);
    }
    cb1.pop_back();

//    cb1.rotate(2);

    cout << "" << endl;

    return 0;
}
