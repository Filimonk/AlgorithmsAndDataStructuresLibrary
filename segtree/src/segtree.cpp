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
segtree<T>::segtree (size_t sizeOfArray, T(*interactionFunc)(T, T), const T& extremeValue) :
                                                                     sizeOfArray_{sizeOfArray},
                                                                     sizeOfBottomLayer{initSizeOfBottomLayer()},
                                                                     tree{new T[2 * sizeOfBottomLayer - 1]} {
    setInteractionFunc(interactionFunc);
    setExtremeValue(extremeValue);
    
    clear();
}

template<class T>
segtree<T>::segtree(size_t sizeOfArray, T(*interactionFunc)(T, T)) :
                                                                     sizeOfArray_{sizeOfArray},
                                                                     sizeOfBottomLayer{initSizeOfBottomLayer()},
                                                                     tree{new T[2 * sizeOfBottomLayer - 1]} {
    setInteractionFunc(interactionFunc);
    setExtremeValue();
    
    clear();
}

template<class T>
segtree<T>::segtree (size_t sizeOfArray, void (*interactionFunc)(T&, T&, T&), const T& extremeValue) :
                                                                     sizeOfArray_{sizeOfArray},
                                                                     sizeOfBottomLayer{initSizeOfBottomLayer()},
                                                                     tree{new T[2 * sizeOfBottomLayer - 1]} {
    setInteractionFunc(interactionFunc);
    setExtremeValue(extremeValue);
    
    clear();
}

template<class T>
segtree<T>::~segtree() {
    delete[] tree;
}


template<class T>
void segtree<T>::setInteractionFunc(T(*interactionFunc)(T, T)) {
    interactionFuncWithCopies = interactionFunc;
    interactionFuncType = interactionFuncTypes::Copies;
}

template<class T>
void segtree<T>::setInteractionFunc(void (*interactionFunc)(T&, T&, T&)) {
    interactionFuncWithRefers = interactionFunc;
    interactionFuncType = interactionFuncTypes::Refers;
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
    if (interactionFuncWithCopies == minOfSubsegment<int>) {
        extremeValue_ = -((1 << (sizeof(int) * 8 - 1)) + 1);
    }
    else if (interactionFuncWithCopies == maxOfSubsegment<int>) {
        extremeValue_ = (1 << (sizeof(int) * 8 - 1));
    }
    else if (interactionFuncWithCopies == sumOfSubsegment<int>) {
        extremeValue_ = 0;
    }
    else {
        throw "This function has no default extreme value";
    }
}

template<>
void segtree<long long>::setExtremeValue() {
    if (interactionFuncWithCopies == minOfSubsegment<long long>) {
        extremeValue_ = -((1LL << (sizeof(long long) * 8 - 1)) + 1LL);
    }
    else if (interactionFuncWithCopies == maxOfSubsegment<long long>) {
        extremeValue_ = (1LL << (sizeof(long long) * 8 - 1));
    }
    else if (interactionFuncWithCopies == sumOfSubsegment<long long>) {
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
void segtree<T>::refresh(T(*interactionFunc)(T, T), const T& extremeValue) {
    setInteractionFunc(interactionFunc);
    setExtremeValue(extremeValue);
    
    clear();
}

template<class T>
void segtree<T>::refresh(T(*interactionFunc)(T, T)) {
    setInteractionFunc(interactionFunc);
    setExtremeValue();
    
    clear();
}

template<class T>
void segtree<T>::refresh(void (*interactionFunc)(T&, T&, T&), const T& extremeValue) {
    setInteractionFunc(interactionFunc);
    setExtremeValue(extremeValue);
    
    clear();
}

template<class T>
void segtree<T>::refresh(void (*interactionFunc)(T&, T&, T&)) {
    setInteractionFunc(interactionFunc);
    setExtremeValue();
    
    clear();
}


template<class T>
void segtree<T>::setWithCopies(size_t x, size_t lx, size_t rx, const size_t& index, const T& value) {
    if (lx > index || rx <= index) {
        return;
    }
    
    if (rx - lx == 1) {
        tree[x] = value;
        return;
    }
    
    size_t m = (lx + rx) / 2;
    setWithCopies(2 * x + 1, lx, m, index, value);
    setWithCopies(2 * x + 2, m, rx, index, value);

    tree[x] = interactionFuncWithCopies(tree[2 * x + 1], tree[2 * x + 2]); // поймать исключение
}

template<class T>
void segtree<T>::setWithRefers(size_t x, size_t lx, size_t rx, const size_t& index, const T& value) {
    if (lx > index || rx <= index) {
        return;
    }
    
    if (rx - lx == 1) {
        tree[x] = value;
        return;
    }
    
    size_t m = (lx + rx) / 2;
    setWithRefers(2 * x + 1, lx, m, index, value);
    setWithRefers(2 * x + 2, m, rx, index, value);

    interactionFuncWithRefers(tree[x], tree[2 * x + 1], tree[2 * x + 2]); // поймать исключение
}

template<class T>
void segtree<T>::set(const size_t& index, const T& value) {
    if (index >= sizeOfArray_) {
        throw "Tree out of range";
    }
    
    switch (interactionFuncType) {
        case interactionFuncTypes::Copies:
            setWithCopies(0, 0, sizeOfBottomLayer, index, value);
            break;
        case interactionFuncTypes::Refers:
            setWithRefers(0, 0, sizeOfBottomLayer, index, value);
            break;
    }
}

template<class T>
T segtree<T>::getWithCopies(size_t x, size_t lx, size_t rx, const size_t& l, const size_t& r) const {
    if (l <= lx && rx <= r) {
        return tree[x];
    }
    
    if (rx <= l || r <= lx) {
        return extremeValue_;
    }
    
    size_t m = (lx + rx) / 2;
    T leftVal  = getWithCopies(2 * x + 1, lx, m, l, r);
    T rightVal = getWithCopies(2 * x + 2, m, rx, l, r);

    return interactionFuncWithCopies(leftVal, rightVal); // поймать исключение
}

template<class T>
T segtree<T>::get(const size_t& l, const size_t& r) const {
    if (interactionFuncType == interactionFuncTypes::Refers) {
        throw "Incorrect request format";
    }
    
    if (r > sizeOfArray_) {
        throw "Tree out of range";
    }
    else if (l > r) {
        throw "Incorrect format of segment boundaries";
    }
    
    if (r >= sizeOfArray_) {
        return getWithCopies(0, 0, sizeOfBottomLayer, l, sizeOfBottomLayer);
    }
    else {
        return getWithCopies(0, 0, sizeOfBottomLayer, l, r);
    }
}

template<class T>
void segtree<T>::getWithRefers(T& returnValue, size_t x, size_t lx, size_t rx, const size_t& l, const size_t& r) const {
    if (l <= lx && rx <= r) {
        interactionFuncWithRefers(returnValue, returnValue, tree[x]); // поймать исключение
        return;
    }
    
    if (rx <= l || r <= lx) {
        return;
    }
    
    size_t m = (lx + rx) / 2;
    getWithRefers(returnValue, 2 * x + 1, lx, m, l, r);
    getWithRefers(returnValue, 2 * x + 2, m, rx, l, r);
}

template<class T>
void segtree<T>::get(T& returnValue, const size_t& l, const size_t& r) const {
    if (interactionFuncType == interactionFuncTypes::Copies) {
        throw "Incorrect request format";
    }
    
    if (r > sizeOfArray_) {
        throw "Tree out of range";
    }
    else if (l > r) {
        throw "Incorrect format of segment boundaries";
    }
    
    returnValue = extremeValue_;
    
    if (r >= sizeOfArray_) {
        getWithRefers(returnValue, 0, 0, sizeOfBottomLayer, l, sizeOfBottomLayer);
    }
    else {
        getWithRefers(returnValue, 0, 0, sizeOfBottomLayer, l, r);
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
T minOfSubsegment(T leftChild, T rightChild) {
    return (leftChild < rightChild? leftChild: rightChild); // надо будет ловить исключения на не соответствие типов (тут на оператор <)
}

template<class T>
T maxOfSubsegment(T leftChild, T rightChild) {
    return (leftChild > rightChild? leftChild: rightChild); // надо будет ловить исключения на не соответствие типов (тут на оператор <)
}

template<class T>
T sumOfSubsegment(T leftChild, T rightChild) {
    return (leftChild + rightChild); // надо будет ловить исключения на не соответствие типов (тут на оператор +)
}



} // namespace addstd
