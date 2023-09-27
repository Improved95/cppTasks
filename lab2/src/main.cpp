#include "CircularBuffer.h"
using std::cout;
using std::endl;
using std::string;

int main() {
    const CircularBuffer<int> cb1(5, 3);

    cout << cb1[4] << endl;

    return 0;
}
