#include "CircularBuffer.h"

int main() {
    CircularBuffer<int> cb1(7);
    for (int i = 0; i < 10; i++) {
        cb1.push_back(i);
    }

//    for (int i = 0; i < 4; i++) {
//        cb1.pop_back();
//    }
    cb1.pop_back();
    cb1.pop_back();
    cb1.pop_back();
    int *pa = cb1.linearize();

    cout << pa << endl;

    cout << "" << endl;
    return 0;
}
