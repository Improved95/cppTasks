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