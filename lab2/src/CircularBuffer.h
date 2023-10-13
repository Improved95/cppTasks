#ifndef CIRCULAR_BUFFER
#define CIRCULAR_BUFFER

/*в большинстве методов работающими с индексами очень много проверок для этого:
когда буфер полностью заполнился и начал перезаписываться, указатель end указывает на элемент, который
хочет перезаписать, этот самый элемент - последний записанный (если я правильно понял работу буфера)
и на него должен указывать указатель begin, но так как предполагается что следующим шагом его перезапишут, то
на него указывет указатель end, а все, что работает через указатель begin ломается без этих проверок
-----
index increment/decrement нужны чтобы работало кольцо, можно было бы через % но оно не работает с отрицательными
не сработает, если в () % capacity в скобках будет больше чем size_t, но такое врядли произойдет
 */

#include <iostream>
#include <vector>
#include <cmath>
using std::vector;
using std::cout;
using std::endl;

template<class T>
class CircularBuffer {
private:
    vector<T> beginBufferInMem;
    size_t capacity;
    size_t beginPosInBuf;
    size_t endPosInBuf;
    size_t size;

    void eraseWhenBeginPosLessEndPos(const size_t first, const size_t last);
    void eraseWhenBeginPosMoreEndPos(const size_t first, const size_t last);

    void rotateWhenBeginPosLessEndPos(const size_t newBegin);
    void rotateWhenBeginPosMoreEndPos(const size_t newBegin);
    void andBeginPosPlusNewBeginLessCapacity(const size_t newBegin);
    void andBeginPosPlusNewBeginMoreCapacity(const size_t newBegin);

    void set_capacityWhenNewCapacityLessOldCapacity(const size_t newCapacity);

    void swapElement(T &a, T &b);

public:
    CircularBuffer();
    explicit CircularBuffer(size_t capacity);
    explicit CircularBuffer(size_t capacity, T &elem);

    vector<T> getBeginBufferInMem() const{ return beginBufferInMem; }
    size_t getCapacity() const { return capacity; }
    size_t getBeginPosInBuf() const { return beginPosInBuf; }
    size_t getEndPosInBuf() const { return endPosInBuf; }
    size_t getSize() const { return size; }

    void push_back(const T &item);
    void push_front(const T &item);
    void pop_back();
    void pop_front();
    void insert(const size_t pos, const T &item);
    void erase(const size_t first, const size_t last);
    void rotate(const size_t newBegin);
    T * linearize();
    void clear();

    T & operator[](const size_t i);
    const T & operator[](const size_t i) const;
    T & at(const size_t i);
    const T & at(const size_t i) const;

    T & front();
    const T & front() const;
    T & back();
    const T & back() const;

    bool operator==(const CircularBuffer<T> &a);
    bool operator!=(const CircularBuffer<T> &a);
    CircularBuffer & operator=(const CircularBuffer & cb);

    bool is_linearized() const;
    bool empty() const;
    bool full() const;
    size_t reserve() const;

    void set_capacity(const size_t new_capacity);
    void resize(const size_t newSize);
    void resize(const size_t newSize, const T &item);
    void swap(CircularBuffer & cb);
};

// всевозможные конструкторы класса
template<class T>
CircularBuffer<T>::CircularBuffer() {
    this->beginPosInBuf = 0;
    this->endPosInBuf = 0;
    this->capacity = 0;
    this->size = 0;
    this->beginBufferInMem = vector<T>(capacity);
}

template<class T>
CircularBuffer<T>::CircularBuffer(size_t capacity):CircularBuffer() {
    this->capacity = capacity;
    this->beginBufferInMem = vector<T>(capacity);
}

template<class T>
CircularBuffer<T>::CircularBuffer(size_t capacity, T &elem):CircularBuffer(capacity) {
    for (size_t i = 0; i < capacity; i++) {
        this->beginBufferInMem[i] = elem;
    }
}

// index increment-decrement
void indexIncrement(size_t &index, const size_t capacity) {
    if (index == capacity - 1) {
        index = 0;
    } else {
        index++;
    }
}
void indexDecrement(size_t &index, const size_t capacity) {
    if (index == 0) {
        index = capacity - 1;
    } else {
        index--;
    }
}

//swapElement
template<class T>
void CircularBuffer<T>::swapElement(T &a, T &b) {
    T c = a;
    a = b;
    b = c;
}

// push
template<class T>
void CircularBuffer<T>::push_back(const T &item) {
    beginBufferInMem[endPosInBuf] = item;
    indexIncrement(endPosInBuf, capacity);
    if (endPosInBuf == beginPosInBuf) {
        indexIncrement(beginPosInBuf, capacity);
    }
    if (size < capacity) {
        size++;
    }
}
template<class T>
void CircularBuffer<T>::push_front(const T &item) {
    indexDecrement(beginPosInBuf, capacity);
    beginBufferInMem[beginPosInBuf] = item;
    if (beginPosInBuf == endPosInBuf) {
        indexDecrement(endPosInBuf, capacity);
    }
    if (size < capacity) {
        size++;
    }
}

//pop
template<class T>
void CircularBuffer<T>::pop_back() {
    if (endPosInBuf != beginPosInBuf) {
        indexDecrement(endPosInBuf, capacity);
        if (size == capacity) {
            indexDecrement(beginPosInBuf, capacity);
        }
    }
    if (size > 0) {
        size--;
    }
}
template<class T>
void CircularBuffer<T>::pop_front() {
    if (size != capacity) {
        if (endPosInBuf != beginPosInBuf) {
            indexIncrement(beginPosInBuf, capacity);
        }
    }
    if (size > 0) {
        size--;
    }
}

//Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной
#include "insert.h"

//Удаляет элементы из буфера в интервале [first, last)
#include "erase.h"

//Доступ по индексу. Не проверяют правильность индекса
template<class T>
T & CircularBuffer<T>::operator[](const size_t i) {
    if (size == capacity) {
        return beginBufferInMem[(beginPosInBuf - 1 + i) % capacity];
    }
    return beginBufferInMem[(beginPosInBuf + i) % capacity];
}

template<class T>
const T & CircularBuffer<T>::operator[](const size_t i) const {
    if (size == capacity) {
        return beginBufferInMem[(beginPosInBuf - 1 + i) % capacity];
    }
    return beginBufferInMem[(beginPosInBuf + i) % capacity];
}

//Доступ по индексу. Методы бросают исключение в случае неверного индекса.
template<class T>
T & CircularBuffer<T>::at(const size_t i) {
    try {
        if (i >= size) {
            throw "incorrect index";
        }
        if (size == capacity) {
            return beginBufferInMem[(beginPosInBuf - 1 + i) % capacity];
        }
        return beginBufferInMem[(beginPosInBuf + i) % capacity];
    } catch(const char *ex) {
        cout << ex << endl;
    }
    return beginBufferInMem[0];
}

template<class T>
const T & CircularBuffer<T>::at(const size_t i) const {
    try {
        if (i >= size) {
            throw "incorrect index";
        }
        if (size == capacity) {
            return beginBufferInMem[(beginPosInBuf - 1 + i) % capacity];
        }
        return beginBufferInMem[(beginPosInBuf + i) % capacity];
    } catch(const char *ex) {
        cout << ex << endl;
    }
    return beginBufferInMem[0];
}

//Ссылка на первый элемент
template<class T>
T & CircularBuffer<T>::front() {
    if (size == capacity) {
        if (beginPosInBuf == 0) {
            return beginBufferInMem[capacity - 1];
        }
        return beginBufferInMem[beginPosInBuf - 1];
    }
    return beginBufferInMem[beginPosInBuf];
}

template<class T>
const T & CircularBuffer<T>::front() const {
    if (size == capacity) {
        if (beginPosInBuf == 0) {
            return beginBufferInMem[capacity - 1];
        }
        return beginBufferInMem[beginPosInBuf - 1];
    }
    return beginBufferInMem[beginPosInBuf];
}

//Ссылка на последний элемент
template<class T>
T & CircularBuffer<T>::back() {
    if (size > 0) {
        if (endPosInBuf == 0) {
            return beginBufferInMem[capacity - 1];
        }
        return beginBufferInMem[endPosInBuf - 1];
    }
    return beginBufferInMem[endPosInBuf];
}

template<class T>
const T & CircularBuffer<T>::back() const {
    if (size > 0) {
        if (endPosInBuf == 0) {
            return beginBufferInMem[capacity - 1];
        }
        return beginBufferInMem[endPosInBuf - 1];
    }
    return beginBufferInMem[endPosInBuf];
}

//Очищает буфер
// если в векторе будет что-то связанное с динамической памятью, то пользователю ее придется самому очищать
template<class T>
void CircularBuffer<T>::clear() {
    beginBufferInMem.resize(0);
    beginPosInBuf = 0;
    endPosInBuf = 0;
    size = 0;
    beginBufferInMem.resize(capacity);
}

//оператор ==
// не сработает, если в векторе будут непростые объекты, структуры или классы, для каждого такого объекта
// нужно переписывать сравнение
template<class T>
bool CircularBuffer<T>::operator==(const CircularBuffer<T> &a) {
    return (this->beginBufferInMem == a.getBeginBufferInMem() && this->capacity == a.getCapacity() && \
    this->beginPosInBuf == a.getBeginPosInBuf() && this->endPosInBuf == a.endPosInBuf && \
    this->size == a.getSize());
}

//оператор !=
// не сработает, если в векторе будут непростые объекты, структуры или классы, для каждого такого объекта
// нужно переписывать сравнение
template<class T>
bool CircularBuffer<T>::operator!=(const CircularBuffer<T> &a) {
    return !(this->beginBufferInMem == a.getBeginBufferInMem() && this->capacity == a.getCapacity() && \
    this->beginPosInBuf == a.getBeginPosInBuf() && this->endPosInBuf == a.endPosInBuf && \
    this->size == a.getSize());
}

//Линеаризация
#include "linearized.h"

//Проверяет, является ли буфер линеаризованным
template <class T>
bool CircularBuffer<T>::is_linearized() const {
    return (&beginBufferInMem[beginPosInBuf] == &(*beginBufferInMem.begin()));
}

//Сдвигает буфер так, что по нулевому индексу окажется элемент с индексом new_begin
#include "rotate.h"

//проверка на пустоту
template<class T>
bool CircularBuffer<T>::empty() const {
    return size == 0;
}

//проверка на заполнение
template<class T>
bool CircularBuffer<T>::full() const {
    return size == capacity;
}

//колво свободных ячеек
template<class T>
size_t CircularBuffer<T>::reserve() const {
    return capacity - size;
}

//Изменяет размер буфера.
#include "setCapacity.h"

//В случае расширения, новые элементы заполняются элементом item.
#include "resize.h"

#endif