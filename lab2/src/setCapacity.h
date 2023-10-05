template<class T>
void CircularBuffer<T>::set_capacity(const size_t newCapacity) {
    if (size == capacity) {
        indexDecrement(beginPosInBuf, capacity);
    }
    indexDecrement(endPosInBuf, capacity);

    if (newCapacity > capacity) {
        if (endPosInBuf >= beginPosInBuf) {
            beginBufferInMem.resize(newCapacity);
        } else {
            beginBufferInMem.resize(newCapacity);
            for (size_t i = 0; i < capacity - beginPosInBuf; i++) {
                swapElement(beginBufferInMem[beginPosInBuf + i], beginBufferInMem[newCapacity - beginPosInBuf + i + 1]);
            }
        }
    } else {
        if (endPosInBuf >= beginPosInBuf) {
            beginBufferInMem.resize(newCapacity);
            if (newCapacity > 0) {
                if (newCapacity - 1 < endPosInBuf) {
                    endPosInBuf -= endPosInBuf - (newCapacity - 1);
                    size -= endPosInBuf - (newCapacity - 1);
                    if (endPosInBuf < beginPosInBuf) {
                        beginPosInBuf = 0;
                    }
                }
            } else {
                beginPosInBuf = 0;
                endPosInBuf = 0;
            }
        } else {
            const size_t diffCap = capacity - newCapacity;
            if (diffCap )
        }
    }

    capacity = newCapacity;
    if (size == capacity) {
        indexIncrement(beginPosInBuf, capacity);
    }
    indexIncrement(endPosInBuf, capacity);
}