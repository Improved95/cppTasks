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

/*in most methods working with indexes, there are a lot of checks for this:
when the buffer is completely full and has started to be overwritten, the end pointer points to the element that
wants to be overwritten, this very element is the last recorded (if I understood the buffer correctly)
and the begin pointer should point to it, but since it is assumed that the next step is its if they overwrite it, then
the end pointer points to it, and everything that works through the begin pointer breaks without these checks
-----
index increment/decrement is needed for the ring to work, it would be possible through %, but it does not work with negative
ones, it will not work if the () % capacity in parentheses is greater than size_t, but this is unlikely to happen*/

#include <iostream>
#include <vector>
#include <cmath>
using std::vector;
using std::cout;
using std::endl;

namespace circularBuffer {

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

    void swapElementInVector(T &a, T &b);

public:
    CircularBuffer();
    explicit CircularBuffer(size_t capacity);
    explicit CircularBuffer(size_t capacity, const T &elem);
    CircularBuffer(const CircularBuffer<T> &cb);
    void swap(CircularBuffer & cb);

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

    bool operator==(const CircularBuffer<T> &cb);
    bool operator!=(const CircularBuffer<T> &cb);
    CircularBuffer & operator=(const CircularBuffer<T> &cb) {
        this->beginBufferInMem = cb.beginBufferInMem;
        this->capacity = cb.capacity;
        this->size = cb.size;
        this->beginPosInBuf = cb.beginPosInBuf;
        this->endPosInBuf = cb.endPosInBuf;
        return *this;
    }

    bool is_linearized() const;
    bool empty() const;
    bool full() const;
    size_t reserve() const;

    void set_capacity(const size_t new_capacity);
    void resize(const size_t newSize);
    void resize(const size_t newSize, const T &item);
};

/*class constructor*/
/*You can create a class object without passing parameters to the constructor or pass the buffer size or pass the size and specify which values to fill the buffer with*/
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
CircularBuffer<T>::CircularBuffer(size_t capacity, const T &elem):CircularBuffer(capacity) {
    this->capacity = capacity;
    this->size = capacity;
    for (size_t i = 0; i < capacity; i++) {
        this->beginBufferInMem[i] = elem;
    }
}

/*copy constructor*/
/*creates a copy of the passed object*/
/*accepts a reference object reference*/
template<class T>
CircularBuffer<T>::CircularBuffer(const CircularBuffer &cb) {
    this->beginBufferInMem = cb.beginBufferInMem;
    this->capacity = cb.capacity;
    this->size = cb.size;
    this->beginPosInBuf = cb.beginPosInBuf;
    this->endPosInBuf = cb.endPosInBuf;
}

/*swap objects*/
template<class T2>
void swapObjectField(T2 &a, T2 &b) {
    T2 c = a;
    a = b;
    b = c;
}

/*exchanges data with the passed object*/
/*accepts a reference object reference*/
template<class T>
void CircularBuffer<T>::swap(CircularBuffer & cb) {
    swapObjectField(this->beginBufferInMem, cb.beginBufferInMem);
    swapObjectField(this->capacity, cb.capacity);
    swapObjectField(this->size, cb.size);
    swapObjectField(this->beginPosInBuf, cb.beginPosInBuf);
    swapObjectField(this->endPosInBuf, cb.endPosInBuf);
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

//swapElementInVector
template<class T>
void CircularBuffer<T>::swapElementInVector(T &a, T &b) {
    T c = a;
    a = b;
    b = c;
}

/*push*/
/*adds an element to the end of the buffer, increasing the buffer size by one. Overwrites the beginning of the buffer if it has been reached*/
/*accepts a reference to a new element*/
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

/*adds an element to the beginning of the buffer, increasing the buffer size by one. Overwrites the end of the buffer if it has been reached*/
/*accepts a reference to a new element*/
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

/*pop*/
/*reduces the buffer end pointer by one, does not actually delete the object that the end pointed to, but it cannot be accessed from the buffer*/
/*does not accept anything*/
/*nothing return*/
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

/*increases the buffer start pointer by one, does not actually delete the object that the start pointed to, but it cannot be accessed from the buffer*/
/*does not accept anything*/
/*nothing return*/
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

/*inserts an element by index, the buffer capacity remains unchanged, the buffer size increases if the buffer is not fully filled, otherwise the element pointed to by the index is overwritten with a new element*/
/*accepts the position where the element should be inserted and a reference to the element*/
/*nothing return*/
#include "insert.h"

/*removes elements from the interval [first, last), does not change the buffer capacity*/
/*accepts indexes for the beginning and end of the segment being deleted*/
/*nothing return*/
#include "erase.h"

/*Access by index. Do not check the correctness of the index, not used with constant objects*/
/*takes the index value to be returned*/
/*returns an element by index*/
template<class T>
T & CircularBuffer<T>::operator[](const size_t i) {
    if (size == capacity) {
        return beginBufferInMem[(beginPosInBuf - 1 + i) % capacity];
    }
    return beginBufferInMem[(beginPosInBuf + i) % capacity];
}

/*Access by index. Do not check the correctness of the index, can used with constant objects*/
/*takes the index value to be returned*/
/*returns an element by index*/
template<class T>
const T & CircularBuffer<T>::operator[](const size_t i) const {
    if (size == capacity) {
        return beginBufferInMem[(beginPosInBuf - 1 + i) % capacity];
    }
    return beginBufferInMem[(beginPosInBuf + i) % capacity];
}

/*Access by index. Check the correctness of the index, not used with constant objects. Returns an exception in case of an invalid index*/
/*takes the index value to be returned*/
/*returns an element by index*/
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

/*Access by index. Check the correctness of the index, can used with constant objects. Returns an exception in case of an invalid index*/
/*takes the index value to be returned*/
/*returns an element by index*/
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

/*Returns the element that the beginning of the buffer points to, not used with constant objects*/
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

/*Returns the element that the beginning of the buffer points to, can used with constant objects*/
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

/*Returns the element that the end of the buffer points to, not used with constant objects*/
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

/*Returns the element that the end of the buffer points to, can used with constant objects*/
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

/*clears the buffer, preserving the buffer capacity. If you use an entity using dynamic memory as an object, then you need to clear it yourself before calling the function*/
template<class T>
void CircularBuffer<T>::clear() {
    beginBufferInMem.resize(0);
    beginPosInBuf = 0;
    endPosInBuf = 0;
    size = 0;
    beginBufferInMem.resize(capacity);
}

//operator ==
/*compares two elements returns true if the elements are equal, false if they are not equal.
 * If you use complex data structures as elements for which the standard operator '==' is not defined, then this operator will not work correctly, for such cases you need to redefine the operator "==" for your element type*/
/*takes the object being compared*/
template<class T>
bool CircularBuffer<T>::operator==(const CircularBuffer<T> &cb) {
    return (this->beginBufferInMem == cb.getBeginBufferInMem() && this->capacity == cb.getCapacity() && \
    this->beginPosInBuf == cb.getBeginPosInBuf() && this->endPosInBuf == cb.endPosInBuf && \
    this->size == cb.getSize());
}

//operator !=
/*compares two elements returns true if the elements are not equal, false if they are equal.
 * If you use complex data structures as elements for which the standard operator '!=' is not defined, then this operator will not work correctly, for such cases you need to redefine the operator "==" for your element type*/
/*takes the object being compared*/
template<class T>
bool CircularBuffer<T>::operator!=(const CircularBuffer<T> &cb) {
    return !(this->beginBufferInMem == cb.getBeginBufferInMem() && this->capacity == cb.getCapacity() && \
    this->beginPosInBuf == cb.getBeginPosInBuf() && this->endPosInBuf == cb.endPosInBuf && \
    this->size == cb.getSize());
}


//linearized
/*moves the buffer elements so that at the beginning of the allocated memory there is an element to which the buffer start pointer points*/
#include "linearized.h"

/*Checks whether the buffer is linearized*/
template <class T>
bool CircularBuffer<T>::is_linearized() const {
    return (&beginBufferInMem[beginPosInBuf] == &(*beginBufferInMem.begin()));
}

/*moves the buffer so that an element with the index new_begin appears at the beginning of the allocated memory*/
/*takes the index element, which will begin of the allocated memory*/
#include "rotate.h"

/*checks if the buffer is empty*/
/*return true if buffer is empty, false if buffer not empty*/
template<class T>
bool CircularBuffer<T>::empty() const {
    return size == 0;
}

/*checks if the buffer is full*/
/*return true if buffer is full, false if buffer not full*/
template<class T>
bool CircularBuffer<T>::full() const {
    return size == capacity;
}

/*returns the number of free cells*/
template<class T>
size_t CircularBuffer<T>::reserve() const {
    return capacity - size;
}

/*changes the buffer capacity*/
/*take a "newCapacity"*/
#include "setCapacity.h"

/*changes the buffer size, in case of an increase, it is possible to fill it with new elements*/
/*take a "newSize", and reference on element, if you want increase buffer size*/
#include "resize.h"

}

#endif