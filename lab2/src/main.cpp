#include "CircularBuffer.h"
using std::cout;
using std::endl;
using std::string;

int main() {
    CircularBuffer<int> cb1(7);
    CircularBuffer<int> cb2(7);
    for (int i = 0; i < 8; i++) {
        cb1.push_back(i);
        cb2.push_back(i);
    }

    if (cb1 == cb2) {
        cout << "good" << endl;
    }

    cout << "" << endl;
    return 0;
}
