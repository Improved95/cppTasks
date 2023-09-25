#include "head.h"
#include "CircularBuffer.h"

template <class T>
CircularBuffer<T>::CircularBuffer(size_t bufferSize) {
    this->bufferSize = bufferSize;
    this->bufferVector = vector<int>(bufferSize);
}

template <class T>
vector<T> CircularBuffer<T>::getBufferVector() {
    return this->bufferVector;
}