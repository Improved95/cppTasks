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

public:
    CircularBuffer();
    explicit CircularBuffer(size_t capacity);
    explicit CircularBuffer(size_t capacity, T elem);

    T & operator[](int i);
    T & operator[](int i) const;
};

// всевозможные конструкторы класса
template<class T>
CircularBuffer<T>::CircularBuffer() {
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
T & CircularBuffer<T>::operator[](int i) {
    return this->bufferVector[i];
}

template<class T>
T & CircularBuffer<T>::operator[](int i) const {
    return this->bufferVector[i % this->capacity];
}

//Доступ по индексу. Методы бросают исключение в случае неверного индекса.


#endif
