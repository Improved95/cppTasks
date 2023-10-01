#include "CircularBuffer.h"
using std::cout;
using std::endl;
using std::string;

int main() {
    CircularBuffer<int> cb1(7);
    for (int i = 0; i < 8; i++) {
        cb1.push_back(i);
    }

    cb1.erase(1, 3);

    cout << "" << endl;
    return 0;
}
