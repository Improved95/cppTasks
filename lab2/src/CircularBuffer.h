#ifndef CIRCULAR_BUFFER
#define CIRCULAR_BUFFER

#include "head.h"
using std::vector;
using namespace std;

template<class T>
class CircularBuffer {
private:
    vector<T> bufferVector; // переименовать, когда станет понятно на что: на начало буфера или на что-то еще
    size_t capacity;
    size_t positionInBuffer;

public:
    CircularBuffer();
    explicit CircularBuffer(size_t capacity);
    explicit CircularBuffer(size_t capacity, T elem);

    //Доступ по индексу. Не проверяют правильность индекса
    T & operator[](size_t i);
    const T & operator[](size_t i) const;

    //Доступ по индексу. Методы бросают исключение в случае неверного индекса
    T & at(size_t i);
    const T & at(size_t i) const;
};

// всевозможные конструкторы класса
template<class T>
CircularBuffer<T>::CircularBuffer() {
    this->positionInBuffer = 0;
    this->capacity = 0;
    this->bufferVector = vector<T>(this->capacity);
}

template<class T>
CircularBuffer<T>::CircularBuffer(size_t capacity):CircularBuffer() {
    this->capacity = capacity;
    this->bufferVector = vector<T>(this->capacity);
}

template<class T>
CircularBuffer<T>::CircularBuffer(size_t capacity, T elem):CircularBuffer(capacity) {
    for (size_t i = 0; i < this->capacity; i++) {
        this->bufferVector[i] = elem;
    }
}

//Доступ по индексу. Не проверяют правильность индекса
template<class T>
T & CircularBuffer<T>::operator[](size_t i) {
    if (i > this->capacity || i < 0) {
        return this->bufferVector[0];
    }
    return this->bufferVector[i];
}

template<class T>
const T & CircularBuffer<T>::operator[](size_t i) const {
    if (i > this->capacity || i < 0) {
        return this->bufferVector[0];
    }
    return this->bufferVector[i];
}

//Доступ по индексу. Методы бросают исключение в случае неверного индекса.
template<class T>
T & CircularBuffer<T>::at(size_t i) {

}

#endif
