#ifndef CIRCULAR_BUFFER
#define CIRCULAR_BUFFER

/*в большинстве методов работающими с индексами очень много проверок для этого:
когда буфер полностью заполнился и начал перезаписываться, указатель end указывает на элемент, который
хочет перезаписать, этот самый элемент - последний записанный (если я правильно понял работу буфера)
и на него должен указывать указатель begin, но так как предполагается что следующим шагом его перезапишут, то
на него указывет указатель end, а все, что работает через указатель begin ломается без этих проверок
-----
ну и с самими индексами много проблем, потому что они должны идти по кругу*/

#include "head.h"
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
    size_t quantWriteEl;

    void eraseWhenBeginPosLessEndPos(const size_t first, const size_t last);
    void eraseWhenBeginPosMoreEndPos(const size_t first, const size_t last);
    void swap(T &a, T &b);

public:
    CircularBuffer();
    explicit CircularBuffer(size_t capacity);
    explicit CircularBuffer(size_t capacity, T elem);

    void push_back(const T &item);
    void push_front(const T &item);
    void pop_back();
    void pop_front();
    void insert(const size_t pos, const T &item);
    void erase(const size_t first, const size_t last);
    void clear();

    T & operator[](const size_t i);
    const T & operator[](const size_t i) const;
    T & at(const size_t i);
    const T & at(const size_t i) const;

    T & front();
    const T & front() const;
    T & back();
    const T & back() const;
};

// всевозможные конструкторы класса
template<class T>
CircularBuffer<T>::CircularBuffer() {
    this->beginPosInBuf = 0;
    this->endPosInBuf = 0;
    this->capacity = 0;
    this->quantWriteEl = 0;
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

// push
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
    if (quantWriteEl < capacity) {
        quantWriteEl++;
    }
}

template<class T>
void CircularBuffer<T>::push_front(const T &item) {
    if (beginPosInBuf <= 0) {
        beginPosInBuf = capacity - 1;
    } else {
        beginPosInBuf--;
    }
    beginBufferInMem[beginPosInBuf] = item;

    if (beginPosInBuf == endPosInBuf) {
        if (endPosInBuf <= 0) {
            endPosInBuf = capacity - 1;
        } else {
            endPosInBuf--;
        }
    }
    if (quantWriteEl < capacity) {
        quantWriteEl++;
    }
}

//pop
template<class T>
void CircularBuffer<T>::pop_back() {
    if (endPosInBuf != beginPosInBuf) {
        if (endPosInBuf == 0) {
            endPosInBuf = capacity - 1;
            beginBufferInMem[endPosInBuf] = 0;
        } else {
            beginBufferInMem[endPosInBuf - 1] = 0;
            endPosInBuf--;
        }
    } else {
        beginBufferInMem[endPosInBuf] = 0;
    }
    if (quantWriteEl == capacity) {
        if (beginPosInBuf == 0) {
            beginPosInBuf = capacity - 1;
        } else {
            beginPosInBuf--;
        }
    }

    if (quantWriteEl > 0) {
        quantWriteEl--;
    }
}

template<class T>
void CircularBuffer<T>::pop_front() {
    if (endPosInBuf != beginPosInBuf) {
        if (quantWriteEl == capacity) {
            if (beginPosInBuf == 0) {
                beginBufferInMem[capacity - 1] = 0;
            } else {
                beginBufferInMem[beginPosInBuf - 1] = 0;
            }
        } else {
            beginBufferInMem[beginPosInBuf] = 0;
            beginPosInBuf++;
            if (beginPosInBuf == capacity) {
                beginPosInBuf = 0;
            }
        }
    } else {
        beginBufferInMem[beginPosInBuf] = 0;
    }

    if (quantWriteEl > 0) {
        quantWriteEl--;
    }
}

//Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной
template<class T>
void CircularBuffer<T>::insert(const size_t pos, const T &item) {
    if (pos < quantWriteEl) {
        beginBufferInMem[(beginPosInBuf + pos) % capacity] = item;
    }
}

//Удаляет элементы из буфера в интервале [first, last)
template<class T>
void CircularBuffer<T>::swap(T &a, T &b) {
    T c = a;
    a = b;
    b = c;
}

template<class T>
void CircularBuffer<T>::eraseWhenBeginPosLessEndPos(const size_t first, const size_t last) {
    for (size_t i = 0; i < (last - first); i++) {
        beginBufferInMem[last - 1 - i] = 0;
    }
    for (size_t i = 0; i < (endPosInBuf - last); i++) {
        swap(beginBufferInMem[first + i], beginBufferInMem[last + i]);
    }
    endPosInBuf = first + (endPosInBuf - last);
    quantWriteEl -= (last - first);
}

template<class T>
void CircularBuffer<T>::eraseWhenBeginPosMoreEndPos(const size_t first, const size_t last) {
    for (size_t i = 0; i < (last - first); i++) {
        beginBufferInMem[(beginPosInBuf ) % capacity] = 0;
    }
}

template<class T>
void CircularBuffer<T>::erase(const size_t first, const size_t last) {
    if (first < last && last <= capacity) {
        if (beginPosInBuf <= endPosInBuf) {
            eraseWhenBeginPosLessEndPos(first, last);
        } else {
            eraseWhenBeginPosMoreEndPos(first, last);
        }
    }
}

//Доступ по индексу. Не проверяют правильность индекса
template<class T>
T & CircularBuffer<T>::operator[](const size_t i) {
    return beginBufferInMem[i % capacity];
}

template<class T>
const T & CircularBuffer<T>::operator[](const size_t i) const {
    return beginBufferInMem[i % capacity];
}

//Доступ по индексу. Методы бросают исключение в случае неверного индекса.
template<class T>
T & CircularBuffer<T>::at(const size_t i) {
    try {
        if ((i > capacity - 1) || (beginPosInBuf < endPosInBuf && (i < beginPosInBuf || i > endPosInBuf)) \
        || (beginPosInBuf > endPosInBuf && (i >= endPosInBuf && i < beginPosInBuf))){
            throw "incorrect index";
        }
        return beginBufferInMem[i];
    } catch(const char *ex) {
        cout << ex << endl;
    }
    return beginBufferInMem[0];
}

template<class T>
const T & CircularBuffer<T>::at(const size_t i) const {
    try {
        if ((i > capacity - 1) || (beginPosInBuf < endPosInBuf && (i < beginPosInBuf || i > endPosInBuf)) \
        || (beginPosInBuf > endPosInBuf && (i >= endPosInBuf && i < beginPosInBuf))){
            throw "incorrect index";
        }
        return beginBufferInMem[i];
    } catch(const char *ex) {
        cout << ex << endl;
    }
    return beginBufferInMem[0];
}

//Ссылка на первый элемент
template<class T>
T & CircularBuffer<T>::front() {
    if (quantWriteEl == capacity) {
        if (beginPosInBuf == 0) {
            return beginBufferInMem[capacity - 1];
        }
        return beginBufferInMem[beginPosInBuf - 1];
    }
    return beginBufferInMem[beginPosInBuf];
}

template<class T>
const T & CircularBuffer<T>::front() const {
    if (quantWriteEl == capacity) {
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
    if (endPosInBuf == 0) {
        return beginBufferInMem[capacity - 1];
    }
    return beginBufferInMem[endPosInBuf - 1];

}

template<class T>
const T & CircularBuffer<T>::back() const {
    if (endPosInBuf == 0) {
        return beginBufferInMem[capacity - 1];
    }
    return beginBufferInMem[endPosInBuf - 1];
}



#endif
