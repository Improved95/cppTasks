#include "CircularBuffer.h"

int main() {
    CircularBuffer<int> cb1(7);
    for (int i = 0; i < 8; i++) {
        cb1.push_back(i);
    }



    cout << "" << endl;

    return 0;
}
