#ifndef CIRCULAR_BUFFER
#define CIRCULAR_BUFFER

#include "head.h"
using std::vector;

template<class T>
class CircularBuffer {
private:
    size_t bufferSize;

public:
    vector<T> bufferVector; // переименовать, когдас танет понятно на что: на начало буфера или на что-то еще
    CircularBuffer(size_t bufferSize); // конструктор создания
    vector<T> getBufferVector();
};

template <class T>
CircularBuffer<T>::CircularBuffer(size_t bufferSize) {
    this->bufferSize = bufferSize;
    this->bufferVector = vector<int>(bufferSize);
}

template <class T>
vector<T> CircularBuffer<T>::getBufferVector() {
    return this->bufferVector;
}

#endif
