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
        if (size == newCapacity) {
            endPosInBuf = 0;
            beginPosInBuf = 1;
        }
    } else {
        const size_t diffCap = capacity - newCapacity;
        if (diffCap < (beginPosInBuf - endPosInBuf)) {
            beginBufferInMem.erase(beginBufferInMem.begin() + beginPosInBuf - diffCap, beginBufferInMem.begin() + beginPosInBuf);
            beginPosInBuf -= diffCap;
            size = (capacity - diffCap) > size ? size : newCapacity;
        } else {
            if (beginPosInBuf > diffCap) {
                endPosInBuf = endPosInBuf - diffCap + (beginPosInBuf - endPosInBuf) - 1;
                for (size_t i = 0; i < (capacity - beginPosInBuf); i++) {
                    swapElement(beginBufferInMem[endPosInBuf + 1 + i], beginBufferInMem[beginPosInBuf + i]);
                }
                beginBufferInMem.resize(newCapacity);
                indexIncrement(endPosInBuf, newCapacity); // возвращаем в состояние записи
                beginPosInBuf = endPosInBuf + 1;
                size = (capacity - diffCap) > size ? size : newCapacity;
                //
            } else {
                endPosInBuf = beginPosInBuf + newCapacity - 1;
                for (size_t i = 0; i < (endPosInBuf - beginPosInBuf) + 1; i++) {
                    swapElement(beginBufferInMem[i], beginBufferInMem[beginPosInBuf + i]);
                }
                beginPosInBuf = 1;
                endPosInBuf = 0;
                size = (capacity - diffCap) > size ? size : newCapacity;
                beginBufferInMem.resize(newCapacity);
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
        if (size == capacity) {
            indexIncrement(beginPosInBuf, capacity);
        }
        indexIncrement(endPosInBuf, capacity);
    } else {
        set_capacityWhenNewCapacityLessOldCapacity(newCapacity);
    }
    capacity = newCapacity;
}