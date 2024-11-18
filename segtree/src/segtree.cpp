namespace addstd { // algorithms and data structures templates definition 



template<class T>
size_t segtree<T>::initSizeOfBottomLayer() {
    size_t sizeOfBottomLayer_local{1};
    
    while (sizeOfBottomLayer_local != 0 && sizeOfBottomLayer_local < sizeOfArray_) {
        sizeOfBottomLayer_local <<= 1;
    }
    
    if (sizeOfBottomLayer_local == 0) {
        throw "Maximum allowed array length exceeded";
    }
    
    return sizeOfBottomLayer_local;
}

template<class T>
segtree<T>::segtree(size_t sizeOfArray, T(*interactionFunc)(T&, T&), const T& extremeValue) :
                                                                        sizeOfArray_{sizeOfArray},
                                                                        sizeOfBottomLayer{initSizeOfBottomLayer()},
                                                                        tree{new T[2 * sizeOfBottomLayer - 1]} {
    setInteractionFunc(interactionFunc);
    setExtremeValue(extremeValue);
    
    clear();
}

template<class T>
segtree<T>::segtree(size_t sizeOfArray, T(*interactionFunc)(T&, T&)) :
                                                                        sizeOfArray_{sizeOfArray},
                                                                        sizeOfBottomLayer{initSizeOfBottomLayer()},
                                                                        tree{new T[2 * sizeOfBottomLayer - 1]} {
    setInteractionFunc(interactionFunc);
    setExtremeValue();
    
    clear();
}

template<class T>
segtree<T>::~segtree() {
    delete[] tree;
}


template<class T>
void segtree<T>::setInteractionFunc(T(*interactionFunc)(T&, T&)) {
    interactionFunc_ = interactionFunc;
}

template<class T>
void segtree<T>::setExtremeValue(const T& extremeValue) {
    extremeValue_ = extremeValue;
}

template<class T>
void segtree<T>::setExtremeValue() {
    throw "This function has no default extreme value for this type";
}

template<>
void segtree<int>::setExtremeValue() {
    if (interactionFunc_ == minOfSubsegment<int>) {
        extremeValue_ = -((1 << (sizeof(int) * 8 - 1)) + 1);
    }
    else if (interactionFunc_ == maxOfSubsegment<int>) {
        extremeValue_ = (1 << (sizeof(int) * 8 - 1));
    }
    else if (interactionFunc_ == sumOfSubsegment<int>) {
        extremeValue_ = 0;
    }
    else {
        throw "This function has no default extreme value";
    }
}

template<>
void segtree<long long>::setExtremeValue() {
    if (interactionFunc_ == minOfSubsegment<long long>) {
        extremeValue_ = -((1LL << (sizeof(long long) * 8 - 1)) + 1LL);
    }
    else if (interactionFunc_ == maxOfSubsegment<long long>) {
        extremeValue_ = (1LL << (sizeof(long long) * 8 - 1));
    }
    else if (interactionFunc_ == sumOfSubsegment<long long>) {
        extremeValue_ = 0LL;
    }
    else {
        throw "This function has no default extreme value";
    }
}

template<class T>
void segtree<T>::clear() {
    for (size_t i = 0; i < 2 * sizeOfBottomLayer - 1; ++i) {
        tree[i] = extremeValue_;
    }
}

template<class T>
void segtree<T>::refresh(T(*interactionFunc)(T&, T&), const T& extremeValue) {
    setInteractionFunc(interactionFunc);
    setExtremeValue(extremeValue);
    
    clear();
}

template<class T>
void segtree<T>::refresh(T(*interactionFunc)(T&, T&)) {
    setInteractionFunc(interactionFunc);
    setExtremeValue();
    
    clear();
}


template<class T>
void segtree<T>::set(size_t x, size_t lx, size_t rx, const size_t& index, const T& value) {
    if (lx > index || rx <= index) {
        return;
    }
    
    if (rx - lx == 1) {
        tree[x] = value;
        return;
    }
    
    size_t m = (lx + rx) / 2;
    set(2 * x + 1, lx, m, index, value);
    set(2 * x + 2, m, rx, index, value);

    tree[x] = interactionFunc_(tree[2 * x + 1], tree[2 * x + 2]); // поймать исключение
}

template<class T>
void segtree<T>::set(const size_t& index, const T& value) {
    if (index >= sizeOfArray_) {
        throw "Tree out of range";
    }
    
    set(0, 0, sizeOfBottomLayer, index, value);
}

template<class T>
T segtree<T>::get(size_t x, size_t lx, size_t rx, const size_t& l, const size_t& r) const {
    if (l <= lx && rx <= r) {
        return tree[x];
    }
    
    if (rx <= l || r <= lx) {
        return extremeValue_;
    }
    
    size_t m = (lx + rx) / 2;
    T leftVal  = get(2 * x + 1, lx, m, l, r);
    T rightVal = get(2 * x + 2, m, rx, l, r);

    return interactionFunc_(leftVal, rightVal); // поймать исключение
}

template<class T>
T segtree<T>::get(const size_t& l, const size_t& r) const {
    if (l < 0 || r > sizeOfArray_) {
        throw "Tree out of range";
    }
    else if (l > r) {
        throw "Incorrect format of segment boundaries";
    }
    
    if (r == sizeOfArray_) {
        return get(0, 0, sizeOfBottomLayer, l, sizeOfBottomLayer);
    }
    else {
        return get(0, 0, sizeOfBottomLayer, l, r);
    }
}


template<class T>
void segtree<T>::getTree() const {
    std::cout << "Bottom layer length: " << sizeOfBottomLayer <<  std::endl;
    std::cout << "Tree length: " << 2 * sizeOfBottomLayer - 1 << std:: endl; 
    std::cout << "Tree:" << std::endl;

    for (size_t i = 0; i < 2 * sizeOfBottomLayer - 1; ++i) {
        std::cout << tree[i] << " ";
    }
    
    std::cout << std::endl;
}


template<class T>
T minOfSubsegment(T& leftChild, T& rightChild) {
    return (leftChild < rightChild? leftChild: rightChild); // надо будет ловить исключения на не соответствие типов (тут на оператор <)
}

template<class T>
T maxOfSubsegment(T& leftChild, T& rightChild) {
    return (leftChild > rightChild? leftChild: rightChild); // надо будет ловить исключения на не соответствие типов (тут на оператор <)
}

template<class T>
T sumOfSubsegment(T& leftChild, T& rightChild) {
    return (leftChild + rightChild); // надо будет ловить исключения на не соответствие типов (тут на оператор +)
}



} // namespace addstd
