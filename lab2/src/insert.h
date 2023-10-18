template<class T>
void CircularBuffer<T>::insert(const size_t pos, const T &item) {
    size_t insertPosition = (beginPosInBuf + pos) % capacity;
    if (pos < capacity) {
        if (size < capacity) {
            indexDecrement(endPosInBuf, capacity);
            size++;
            if (beginPosInBuf < endPosInBuf) {
                for (size_t i = 0; i < (endPosInBuf - (beginPosInBuf + pos) + 1); i++) {
                    swapElementInVector(beginBufferInMem[(endPosInBuf - i) % capacity], beginBufferInMem[(endPosInBuf - i + 1) % capacity]);
                }
            } else {
                if ((beginPosInBuf + pos) % capacity < beginPosInBuf) {
                    T elem = beginBufferInMem[(beginPosInBuf + pos) % capacity];
                    for (size_t i = 0; i < endPosInBuf - ((beginPosInBuf + pos) % capacity) + 1; i++) {
                        swapElementInVector(elem, beginBufferInMem[(beginPosInBuf + pos + i + 1) % capacity]);
                    }
                } else {
                    T elem = beginBufferInMem[beginPosInBuf + pos];
                    for (size_t i = 0; i < (capacity - beginPosInBuf) + endPosInBuf + 1; i++) {
                        swapElementInVector(elem, beginBufferInMem[(beginPosInBuf + 1 + i) % capacity]);
                    }
                }
            }
            if (size == capacity) {
                indexIncrement(beginPosInBuf, capacity);
            }
            indexIncrement(endPosInBuf, capacity);
            indexIncrement(endPosInBuf, capacity);
            beginBufferInMem[insertPosition] = item;
        } else {
            beginBufferInMem[(beginPosInBuf + pos) % capacity] = item;
        }
    }
}