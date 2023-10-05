template<class T>
void CircularBuffer<T>::rotateWhenBeginPosLessEndPos(const size_t newBegin) {
    T *pel = new T[newBegin];
    for (size_t i = 0; i < newBegin; i++) {
        pel[i] = beginBufferInMem[beginPosInBuf + i];
    }
    for (size_t i = 0; i < endPosInBuf - beginPosInBuf - 1; i++) {
        swapElement(beginBufferInMem[i], beginBufferInMem[beginPosInBuf + newBegin + i]);
    }
    for (size_t i = 0; i < newBegin; i++) {
        beginBufferInMem[endPosInBuf - beginPosInBuf - 1 + i] = pel[i];
    }
    delete[] pel;
    beginPosInBuf = endPosInBuf - beginPosInBuf - 1;
    endPosInBuf = (beginPosInBuf + size) % capacity + 1;
}

template <class T>
void CircularBuffer<T>::andBeginPosPlusNewBeginLessCapacity(const size_t newBegin) {
    T *pel = new T[beginPosInBuf + newBegin];
    for (size_t i = 0; i < beginPosInBuf + newBegin; i++) {
        pel[i] = beginBufferInMem[i];
    }
    for (size_t i = 0; i < capacity - (beginPosInBuf + newBegin); i++) {
        swapElement(beginBufferInMem[i], beginBufferInMem[beginPosInBuf + newBegin + i]);
    }
    for (size_t i = 0; i < beginPosInBuf + newBegin; i++) {
        beginBufferInMem[capacity - (beginPosInBuf + newBegin) + i] = pel[i];
    }
    delete[] pel;
    beginPosInBuf =
}

template <class T>
void CircularBuffer<T>::andBeginPosPlusNewBeginMoreCapacity(const size_t newBegin) {
    T *pel = new T[(beginPosInBuf + newBegin) % capacity];
    for (size_t i = 0; i < (beginPosInBuf + newBegin) % capacity; i++) {
        pel[i] = beginBufferInMem[i];
    }
    for (size_t i = 0; i < capacity - ((beginPosInBuf + newBegin) % capacity); i++) {
        swapElement(beginBufferInMem[i], beginBufferInMem[(beginPosInBuf + newBegin) % capacity + i]);
    }
    for (size_t i = 0; i < (beginPosInBuf + newBegin) % capacity; i++) {
        beginBufferInMem[capacity - ((beginPosInBuf + newBegin) % capacity )+ i] = pel[i];
    }
    delete[] pel;

}

template<class T>
void CircularBuffer<T>::rotateWhenBeginPosMoreEndPos(const size_t newBegin) {
    if (beginPosInBuf + newBegin < capacity) {
        andBeginPosPlusNewBeginLessCapacity(newBegin);
    } else {
        andBeginPosPlusNewBeginMoreCapacity(newBegin);
    }
}

template<class T>
void CircularBuffer<T>::rotate(const size_t newBegin) {
    if (newBegin < size) {
        if (size == capacity) {
            indexDecrement(beginPosInBuf, capacity);
        }
        indexDecrement(endPosInBuf, capacity);

        if (beginPosInBuf < endPosInBuf) {
            rotateWhenBeginPosLessEndPos(newBegin);
        } else {
            rotateWhenBeginPosMoreEndPos(newBegin);
        }
    }
}

// доделать последний случай + дописать изменение позиций в предпоследнем