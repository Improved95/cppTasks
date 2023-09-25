#ifndef CIRCULAR_BUFFER
#define CIRCULAR_BUFFER

#include "head.h"
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

#endif
