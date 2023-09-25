#include "head.h"
//#include "CircularBuffer.h"
using std::vector;

template<class T>
class CircularBuffer {
private:
    size_t bufferSize;
    vector<T> bufferVector; // переименовать, когдас танет понятно на что: на начало буфера или на что-то еще

public:
    CircularBuffer(size_t bufferSize); // конструктор копирование
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