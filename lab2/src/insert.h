template<class T>
void CircularBuffer<T>::insert(const size_t pos, const T &item) {
    size_t insertPosition = (beginPosInBuf + pos) % capacity;
    if (pos < capacity) {
        if (size < capacity) {
            indexDecrement(endPosInBuf, capacity);
            if (beginPosInBuf < endPosInBuf) {
                for (size_t i = 0; i < (endPosInBuf - (beginPosInBuf + pos) + 1); i++) {
                    swapElementInVector(beginBufferInMem[(endPosInBuf - i) % capacity], beginBufferInMem[(endPosInBuf - i + 1) % capacity]);
                }
                if ((size + 1) == capacity) {
                    indexIncrement(beginPosInBuf, capacity);
                }
                indexIncrement(endPosInBuf, capacity);
                indexIncrement(endPosInBuf, capacity);
            } else {
                T elem = beginBufferInMem[(beginPosInBuf + pos) % capacity];
                for (size_t i = 0; i < (capacity - pos + endPosInBuf + 1); i++) {
                    swapElementInVector(elem, beginBufferInMem[(beginPosInBuf + pos + i + 1) % capacity]);
                }
                indexIncrement(beginPosInBuf, capacity);
            }
            beginBufferInMem[insertPosition] = item;
            if (size < capacity) {
                size++;
            }
        } else {
            beginBufferInMem[(beginPosInBuf + pos) % capacity] = item;
        }
    }
}