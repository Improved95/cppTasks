#include "CircularBuffer.h"
using std::cout;
using std::endl;
using std::string;

int main() {
    CircularBuffer<int> cb1(5);

    for (size_t i = 0; i < 7; i++) {
        cb1.push_back(i);
    }

    for (size_t i = 0; i < 5; i++) {
        cout << cb1[i] << " ";
    }

    for (size_t i = 0; i < 5; i++) {
        cb1.pop_front();
    }

    cout << "\n";
    for (size_t i = 0; i < 5; i++) {
        cout << cb1[i] << " ";
    }

    return 0;
}
