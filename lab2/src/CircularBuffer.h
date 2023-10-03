#ifndef CIRCULAR_BUFFER
#define CIRCULAR_BUFFER

/*в большинстве методов работающими с индексами очень много проверок для этого:
когда буфер полностью заполнился и начал перезаписываться, указатель end указывает на элемент, который
хочет перезаписать, этот самый элемент - последний записанный (если я правильно понял работу буфера)
и на него должен указывать указатель begin, но так как предполагается что следующим шагом его перезапишут, то
на него указывет указатель end, а все, что работает через указатель begin ломается без этих проверок
-----
index increment/decrement нужны чтобы работало кольцо, можно было бы через % но оно не работает с отрицательными
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
    void swapElement(T &a, T &b);

public:
    CircularBuffer();
    explicit CircularBuffer(size_t capacity);
    explicit CircularBuffer(size_t capacity, T elem);

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
    bool is_linearized() const;
    void rotate(const size_t newBegin);
    bool empty() const;
    bool full() const;
    size_t reserve() const;
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
CircularBuffer<T>::CircularBuffer(size_t capacity, T elem):CircularBuffer(capacity) {
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
    if (endPosInBuf != beginPosInBuf) {
        indexIncrement(beginPosInBuf, capacity);
    }
    if (size > 0) {
        size--;
    }
}

//Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной
template<class T>
void CircularBuffer<T>::insert(const size_t pos, const T &item) {
    size_t insertPosition = (beginPosInBuf + pos) % capacity;
    if (pos < size) {
        if (size == capacity) {
            indexDecrement(beginPosInBuf, capacity);
        }
        indexDecrement(endPosInBuf, capacity);
        if (beginPosInBuf < endPosInBuf) {
            for (size_t i = 0; i < (endPosInBuf - (beginPosInBuf + pos) + 1); i++) {
                swapElement(beginBufferInMem[(endPosInBuf - i) % capacity], beginBufferInMem[(endPosInBuf - i + 1) % capacity]);
            }
            if (size == capacity - 1) {
                indexIncrement(beginPosInBuf, capacity);
            }
        } else {
            T elem = beginBufferInMem[(beginPosInBuf + pos) % capacity];
            for (size_t i = 0; i < (capacity - pos + endPosInBuf + 1); i++) {
                swapElement(elem, beginBufferInMem[(beginPosInBuf + pos + i + 1) % capacity]);
            }
            if (size == capacity) {
                indexIncrement(beginPosInBuf, capacity);
                indexIncrement(beginPosInBuf, capacity);
            }
        }
        beginBufferInMem[insertPosition] = item;
        indexIncrement(endPosInBuf, capacity);
        indexIncrement(endPosInBuf, capacity);
        if (size < capacity) {
            size++;
        }
    }
}

//Удаляет элементы из буфера в интервале [first, last)
template<class T>
void CircularBuffer<T>::eraseWhenBeginPosLessEndPos(const size_t first, const size_t last) {
    for (size_t i = 0; i < (endPosInBuf - last); i++) {
        swapElement(beginBufferInMem[first + i], beginBufferInMem[last + i]); //swapElement, потому что не свап лень писать
    }
    endPosInBuf = first + (endPosInBuf - last);
    size -= (last - first);
}

template<class T>
void CircularBuffer<T>::eraseWhenBeginPosMoreEndPos(const size_t first, const size_t last) {
    if (size == capacity) {
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
        swapElement(beginBufferInMem[(beginPosInBuf + first + i) % capacity], beginBufferInMem[(beginPosInBuf + last + i) % capacity]);
    }
    endPosInBuf = (beginPosInBuf + first + quantReplaceEl) % capacity;
    size -= (last - first);
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
    if (size == capacity) {
        return beginBufferInMem[(beginPosInBuf - 1) % capacity];
    }
    return beginBufferInMem[beginPosInBuf];
}

template<class T>
const T & CircularBuffer<T>::front() const {
    if (size == capacity) {
        return beginBufferInMem[(beginPosInBuf - 1) % capacity];
    }
    return beginBufferInMem[beginPosInBuf];
}

//Ссылка на последний элемент
template<class T>
T & CircularBuffer<T>::back() {
    return beginBufferInMem[(endPosInBuf - 1) % capacity];
}

template<class T>
const T & CircularBuffer<T>::back() const {
    return beginBufferInMem[(endPosInBuf - 1) % capacity];
}

//Очищает буфер
// если в векторе будет что-то связанное и динамической памятью, то пользователю ее придется самому очищать
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
// есть способ сделать перемещение очень быстро и без доп памяти, но я его не знаю
template<class T>
T * CircularBuffer<T>::linearize() {
    if (beginPosInBuf != 0) {
        if (beginPosInBuf < endPosInBuf) {
            for (size_t i = 0; i < endPosInBuf - beginPosInBuf - 1; i++) {
                swapElement(beginBufferInMem[i], beginBufferInMem[beginPosInBuf + i]);
            }
            endPosInBuf -= beginPosInBuf;
            beginPosInBuf = 0;
        } else {
            indexDecrement(endPosInBuf, capacity);
            if (size == capacity) {
                indexDecrement(beginPosInBuf, capacity);
            }
            if (beginPosInBuf != 0) {
                T *pel = new T[endPosInBuf + 1];
                for (size_t i = 0; i < endPosInBuf + 1; i++) {
                    pel[i] = beginBufferInMem[i];
                }
                for (size_t i = 0; i < capacity - beginPosInBuf; i++) {
                    swapElement(beginBufferInMem[i], beginBufferInMem[beginPosInBuf + i]);
                }
                for (size_t i = 0; i < endPosInBuf + 1; i++) {
                    beginBufferInMem[capacity - beginPosInBuf + i] = pel[i];
                }
                delete[] pel;
                endPosInBuf = size % capacity;
                if (size == capacity) {
                    beginPosInBuf = 1;
                } else {
                    beginPosInBuf = 0;
                }
            }
        }
    }
    return &beginBufferInMem[0];
}

//Проверяет, является ли буфер линеаризованным
template <class T>
bool CircularBuffer<T>::is_linearized() const {
    return (&beginBufferInMem[beginPosInBuf] == &(*beginBufferInMem.begin()));
}

//Сдвигает буфер так, что по нулевому индексу окажется элемент с индексом new_begin
template<class T>
void CircularBuffer<T>::rotate(const size_t newBegin) {
    if (newBegin < size) {
        if (size == capacity) {
            indexDecrement(beginPosInBuf, capacity);
        }
        indexDecrement(endPosInBuf, capacity);

        T *pel = new T[(beginPosInBuf + newBegin) % capacity];
        for (size_t i = 0; i < (beginPosInBuf + newBegin + 1) % capacity; i++) {
            pel[i] = beginBufferInMem[i];
        }


        endPosInBuf = size % capacity;
        if (size == capacity) {
            beginPosInBuf = 1;
        } else {
            beginPosInBuf = 0;
        }
    }
}

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

#endif

// проверить еще раз линеаризацию
// я точно не ебу, но что то точно не работает

/*
  осталось немного:
  void rotate(int new_begin);
  -----------------------------------------------------------------
  void set_capacity(int new_capacity);
  //Изменяет размер буфера.
  //В случае расширения, новые элементы заполняются элементом item.
  void resize(int new_size, const value_type & item = value_type());
  //Оператор присваивания.
  CircularBuffer & operator=(const CircularBuffer & cb);
  //Обменивает содержимое буфера с буфером cb.
  void swap(CircularBuffer & cb);
 */
