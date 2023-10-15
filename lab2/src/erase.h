template<class T>
void CircularBuffer<T>::eraseWhenBeginPosLessEndPos(const size_t first, const size_t last) {
    for (size_t i = 0; i < (endPosInBuf - last); i++) {
        swapElementInVector(beginBufferInMem[first + i], beginBufferInMem[last + i]); //swapElement, потому что не свап лень писать
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