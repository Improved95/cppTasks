#ifndef CIRCULAR_BUFFER
#define CIRCULAR_BUFFER

/*в большинстве методов работающими с индексами очень много проверок для этого:
когда буфер полностью заполнился и начал перезаписываться, указатель end указывает на элемент, который
хочет перезаписать, этот самый элемент - последний записанный (если я правильно понял работу буфера)
и на него должен указывать указатель begin, но так как предполагается что следующим шагом его перезапишут, то
на него указывет указатель end, а все, что работает через указатель begin ломается без этих проверок
-----
ну и с самими индексами много проблем, потому что они должны идти по кругу*/

#include <iostream>
#include <vector>
#include "cmath"
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
    void assignment(T &a);

public:
    CircularBuffer();
    explicit CircularBuffer(size_t capacity);
    explicit CircularBuffer(size_t capacity, T elem);

    vector<T> getBeginBufferInMem() const{ return beginBufferInMem; }
    size_t getCapacity() const { return capacity; }
    size_t getBeginPosInBuf() const { return beginPosInBuf; }
    size_t getEndPosInBuf() const { return endPosInBuf; }
    size_t getQquantWriteEl() const { return quantWriteEl; }

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

    bool operator==(const CircularBuffer<T> &a);
    bool operator!=(const CircularBuffer<T> &a);

    T * linearize();
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

template<class T>
void CircularBuffer<T>::swap(T &a, T &b) {
    T c = a;
    a = b;
    b = c;
}

template<class T>
void CircularBuffer<T>::assignment(T &a) {

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
        } else {
            endPosInBuf--;
        }
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
        beginPosInBuf++;
        if (beginPosInBuf == capacity) {
            beginPosInBuf = 0;
        }
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
void CircularBuffer<T>::eraseWhenBeginPosLessEndPos(const size_t first, const size_t last) {
    for (size_t i = 0; i < (endPosInBuf - last); i++) {
        swap(beginBufferInMem[first + i], beginBufferInMem[last + i]); //swap, потому что не свап лень писать
    }
    endPosInBuf = first + (endPosInBuf - last);
    quantWriteEl -= (last - first);
}

template<class T>
void CircularBuffer<T>::eraseWhenBeginPosMoreEndPos(const size_t first, const size_t last) {
    if (quantWriteEl == capacity) {
        beginPosInBuf--;
    }
    endPosInBuf--;
    // не сработает если (beginPosInBuf + last) больше size, но такое вряд ли произойдет
    size_t quantReplaceEl = 0;
    if ((beginPosInBuf + last) % capacity > beginPosInBuf) {
        quantReplaceEl = (capacity - last) + endPosInBuf;
    } else {
        quantReplaceEl = endPosInBuf - ((beginPosInBuf + last) % capacity) + 1;
    }
    for (size_t i = 0; i < quantReplaceEl; i++) {
        swap(beginBufferInMem[(beginPosInBuf + first + i) % capacity], beginBufferInMem[(beginPosInBuf + last + i) % capacity]);
    }
    endPosInBuf = (beginPosInBuf + first + quantReplaceEl) % capacity;
    quantReplaceEl -= (last - first);
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

//Очищает буфер
// если в векторе будет что-то связанное и динамической памятью, то пользователю ее придется самому очищать
template<class T>
void CircularBuffer<T>::clear() {
    beginBufferInMem.resize(0);
    beginPosInBuf = 0;
    endPosInBuf = 0;
    quantWriteEl = 0;
    beginBufferInMem.resize(capacity);
}

//оператор ==
// не сработает, если в векторе будут непростые объекты, структуры или классы, для каждого такого объекта
// нужно переписывать сравнение
template<class T>
bool CircularBuffer<T>::operator==(const CircularBuffer<T> &a) {
    return (this->beginBufferInMem == a.getBeginBufferInMem() && this->capacity == a.getCapacity() && \
    this->beginPosInBuf == a.getBeginPosInBuf() && this->endPosInBuf == a.endPosInBuf && \
    this->quantWriteEl == a.quantWriteEl);
}

//оператор !=
// не сработает, если в векторе будут непростые объекты, структуры или классы, для каждого такого объекта
// нужно переписывать сравнение
template<class T>
bool CircularBuffer<T>::operator!=(const CircularBuffer<T> &a) {
    return !(this->beginBufferInMem == a.getBeginBufferInMem() && this->capacity == a.getCapacity() && \
    this->beginPosInBuf == a.getBeginPosInBuf() && this->endPosInBuf == a.endPosInBuf && \
    this->quantWriteEl == a.quantWriteEl);
}

//Линеаризация
template<class T>
T * CircularBuffer<T>::linearize() {
    if (beginPosInBuf != 0) {
        if (beginPosInBuf < endPosInBuf) {
            for (size_t i = 0; i < endPosInBuf - beginPosInBuf - 1; i++) {
                // есть способ сделать это перемещение очень быстро, но я его не знаю
                swap(beginBufferInMem[i], beginBufferInMem[beginPosInBuf + i]);
            }
//            beginBufferInMem.erase(beginBufferInMem.begin(), beginBufferInMem.begin() + beginPosInBuf);
            endPosInBuf -= beginPosInBuf;
            beginPosInBuf = 0;
//            beginBufferInMem.resize(capacity);
        } else {
            if (beginPosInBuf - endPosInBuf == 1) {
                endPosInBuf = (endPosInBuf - 1) % capacity;
                beginPosInBuf--;
            }
            if (beginPosInBuf != 0) {
                // есть способ сделать это перемещение очень быстро и без доп памяти, но я его не знаю
                T *pel = new T[endPosInBuf + 1];
                for (size_t i = 0; i < endPosInBuf + 1; i++) {
                    pel[i] = beginBufferInMem[i];
                }
                for (size_t i = 0; i < capacity - beginPosInBuf; i++) {
                    swap(beginBufferInMem[i], beginBufferInMem[beginPosInBuf + i]);
                }
                for (size_t i = 0; i < endPosInBuf + 1; i++) {
                    beginBufferInMem[capacity - beginPosInBuf + i] = pel[i];
                }
                delete[] pel;

            }
        }
    }
    return &beginBufferInMem[0];
}

#endif
