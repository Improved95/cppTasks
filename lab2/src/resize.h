template<class T>
void CircularBuffer<T>::resize(const size_t newSize) {
    if (newSize < size) {
        for (size_t i = 0; i < size - newSize; i++) {
            pop_back();
        }
    }
}

template<class T>
void CircularBuffer<T>::resize(const size_t newSize, const T &item) {
    if (newSize > size) {
        const size_t oldSize = size;
        for (size_t i = 0; i < newSize - oldSize; i++) {
            push_back(item);
        }
    }
}