template<class T>
void CircularBuffer<T>::eraseWhenBeginPosLessEndPos(const size_t first, const size_t last) {
    for (size_t i = 0; i < (capacity - last); i++) {
        swapElementInVector(beginBufferInMem[(beginPosInBuf + first + i) % capacity], beginBufferInMem[(beginPosInBuf + last + i) % capacity]);
    }
    size -= (last - first);
    endPosInBuf = (beginPosInBuf + size) % capacity;
}

template<class T>
void CircularBuffer<T>::eraseWhenBeginPosMoreEndPos(const size_t first, const size_t last) {
    size_t quantReplaceEl = (capacity - beginPosInBuf) + endPosInBuf - (last - first);
    for (size_t i = 0; i < quantReplaceEl; i++) {
        swapElementInVector(beginBufferInMem[(beginPosInBuf + first + i) % capacity], beginBufferInMem[(beginPosInBuf + last + i) % capacity]);
    }
    size -= (last - first);
    endPosInBuf = (beginPosInBuf + size) % capacity;
}

template<class T>
void CircularBuffer<T>::erase(const size_t first, const size_t last) {
    if (size == capacity) {
        indexDecrement(beginPosInBuf, capacity);
    }
    indexDecrement(endPosInBuf, capacity);
    if (first < last && last <= capacity) {
        if (beginPosInBuf <= endPosInBuf) {
            eraseWhenBeginPosLessEndPos(first, last);
        } else {
            eraseWhenBeginPosMoreEndPos(first, last);
        }
    }
}