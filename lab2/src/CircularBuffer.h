#ifndef CIRCULAR_BUFFER
#define CIRCULAR_BUFFER

#include "head.h"
using std::string;
using std::vector;

template<typename T>
class CircularBuffer {
private:
    size_t bufferSize;
    vector<T> bufferVector;

public:
    CircularBuffer(size_t bufferSize) {
        this->bufferSize = bufferSize;
        this->bufferVector = vector<T>(bufferSize);
    }

    vector<T> getBufferVector() {
        return this->bufferVector;
    }
};

#endif
