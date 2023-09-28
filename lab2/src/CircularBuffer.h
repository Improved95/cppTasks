#ifndef CIRCULAR_BUFFER
#define CIRCULAR_BUFFER

#include "head.h"
using std::vector;
using std::cout;
using std::endl;
using std::exception;

template<class T>
class CircularBuffer {
private:
    vector<T> beginBufferInMem;
    size_t capacity;
    size_t beginPosInBuf;
    size_t endPosInBuf;
    size_t quantWriteElem;

public:
    CircularBuffer();
    explicit CircularBuffer(size_t capacity);
    explicit CircularBuffer(size_t capacity, T elem);

    void push_back(const T &item);
    void push_front(const T &item);
    void pop_back();
    void pop_front();

     /*полностью переделать методы*/
     //Доступ по индексу. Не проверяют правильность индекса
    T & operator[](size_t i);
    const T & operator[](size_t i) const;

    //Доступ по индексу. Методы бросают исключение в случае неверного индекса
    T & at(size_t i);
    const T & at(size_t i) const;

    //Ссылка на первый элемент
    T & front();
    const T & front() const;
    //Ссылка на последний элемент.
    T & back();
    const T & back() const;
};

// всевозможные конструкторы класса
template<class T>
CircularBuffer<T>::CircularBuffer() {
    this->beginPosInBuf = 0;
    this->endPosInBuf = 0;
    this->capacity = 0;
    this->quantWriteElem = 0;
    this->beginBufferInMem = vector<T>(capacity);
}

template<class T>
CircularBuffer<T>::CircularBuffer(size_t capacity):CircularBuffer() {
    this->capacity = capacity;
    this->beginBufferInMem = vector<T>(capacity);
}

template<class T>
CircularBuffer<T>::CircularBuffer(size_t capacity, T elem):CircularBuffer(capacity) {
    for (size_t i = 0; i < capacity; i++) {
        this->beginBufferInMem[i] = elem;
    }
}

template<class T>
void CircularBuffer<T>::push_back(const T &item) {
    beginBufferInMem[endPosInBuf] = item;
    endPosInBuf++;
    if (endPosInBuf >= capacity) {
        endPosInBuf = 0;
    }
    if (endPosInBuf == beginPosInBuf) {
        beginPosInBuf++;
        if (beginPosInBuf >= capacity) {
            beginPosInBuf = 0;
        }
    }
}

template<class T>
void CircularBuffer<T>::push_front(const T &item) {
    beginBufferInMem[beginPosInBuf] = item;
    if (beginPosInBuf <= 0) {
        beginPosInBuf = capacity - 1;
    } else {
        beginPosInBuf--;
    }

    if (beginPosInBuf == endPosInBuf) {
        if (endPosInBuf <= 0) {
            endPosInBuf = capacity - 1;
        } else {
            endPosInBuf--;
        }
    }
}

/*полностью переделать все эти методы*/
//Доступ по индексу. Не проверяют правильность индекса
template<class T>
T & CircularBuffer<T>::operator[](size_t i) {
    return beginBufferInMem[i % capacity];
}

template<class T>
const T & CircularBuffer<T>::operator[](size_t i) const {
    return beginBufferInMem[i % capacity];
}

//Доступ по индексу. Методы бросают исключение в случае неверного индекса.
template<class T>
T & CircularBuffer<T>::at(size_t i) {
    try {
        return beginBufferInMem.at(i);
    } catch(const exception & ex) {
        cout << ex.what()  << endl;
    }
    return beginBufferInMem[0];
}

template<class T>
const T & CircularBuffer<T>::at(size_t i) const {
    try {
        return beginBufferInMem.at(i);
    } catch(const exception & ex) {
        cout << ex.what() << endl;
    }
    return beginBufferInMem[0];
}

//Ссылка на первый элемент
template<class T>
T & CircularBuffer<T>::front() {
    return beginBufferInMem[0];
}

template<class T>
const T & CircularBuffer<T>::front() const {
    return beginBufferInMem[0];
}

//Ссылка на последний элемент.
template<class T>
T & CircularBuffer<T>::back() {
    return beginBufferInMem[capacity - 1];
}

template<class T>
const T & CircularBuffer<T>::back() const {
    return beginBufferInMem[capacity - 1];
}

#endif
