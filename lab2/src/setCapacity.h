template<class T>
void CircularBuffer<T>::set_capacityWhenNewCapacityLessOldCapacity(const size_t newCapacity) {
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
        if (diffCap < (beginPosInBuf - endPosInBuf)) {
            beginBufferInMem.erase(beginBufferInMem.begin() + beginPosInBuf - diffCap, beginBufferInMem.begin() + beginPosInBuf);
        } else {
            if (beginPosInBuf - 1 > diffCap) {
                size_t oldEndPos = endPosInBuf;
                endPosInBuf = endPosInBuf - diffCap + (beginPosInBuf - endPosInBuf) - 2;
                for (size_t i = 0; i < capacity - oldEndPos; i++) {
                    swapElement(beginBufferInMem[endPosInBuf + i + 1], beginBufferInMem[oldEndPos + i]);
                }
//                beginPosInBuf = 0;
                beginBufferInMem.resize(newCapacity);
            } else {

            }
        }
    }
}

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
        set_capacityWhenNewCapacityLessOldCapacity(newCapacity);
    }

    capacity = newCapacity;
    if (size == capacity) {
        indexIncrement(beginPosInBuf, capacity);
    }
    indexIncrement(endPosInBuf, capacity);
}