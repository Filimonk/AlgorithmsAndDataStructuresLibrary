#ifndef DO_NOT_INCLUDE_SYS_LIBS

    #include <iostream> // убрать, когда переделаю getTree()
    #include <sys/types.h>
    #include <stdexcept>

#endif

#ifndef SEGTREE
#define SEGTREE

namespace addstd { // algorithms and data structures templates definition 



template<class T>
T minOfSubsegment(T, T); // надо будет ловить исключения на не соответствие типов

template<class T>
T maxOfSubsegment(T, T); // надо будет ловить исключения на не соответствие типов

template<class T>
T sumOfSubsegment(T, T); // надо будет ловить исключения на не соответствие типов

template<class T>
class segtree {
public:

    //segtree(size_t, /*ссылка на ф-ию взаимодействия*/, T/*initialization value*/); //для не стандартных типов данных
    //segtree(size_t, /*ссылка на ф-ию взаимодействия*/);
                     // дерево по умолчанию (сум) для стандартных 
                     // типов (?bool, ?char, ?short, int, ?float, long long, ?double,
                     // ?long double, ?unsigned char & short, unsigned int & long long, pair <..., ...>, set <...>, ?map <...>,
                     // ?unordered set & map, ??string, ?vector, ?int[], ?char[], ??long long[], ...)
                     // 
                     // имеет возможность давать ссылки на
                     // стандартные ф-ии взаимодействия (макс, сум, ...)
    
    segtree(size_t, T(*)(T, T), const T&); 
    segtree(size_t, T(*)(T, T) = sumOfSubsegment); 
    segtree(size_t, void (*)(T&, T&, T&), const T&); 
    
    segtree() = delete;
    ~segtree();
    
    segtree(const segtree&) = delete;
    segtree& operator=(const segtree&) = delete;
    
    //добавить класс итераторов
    //void read(); // вводить с переданного потока
    //build == read
    //iterator<t> begin();
    //методы поиска первого, последнего (k-го элемента)
    
    void clear();
    void refresh(T(*)(T, T), const T&);
    void refresh(T(*)(T, T));
    void refresh(void (*)(T&, T&, T&), const T&);
    void refresh(void (*)(T&, T&, T&));
    //refresh() == clear()
    
    void setWithCopies(size_t, size_t, size_t, const size_t&, const T&); // поймать исключение
    void setWithRefers(size_t, size_t, size_t, const size_t&, const T&); // поймать исключение
    void set(const size_t&, const T&); 
    T getWithCopies(size_t, size_t, size_t, const size_t&, const size_t&) const; // поймать исключение
    T get(const size_t&, const size_t&) const; // переделать на возврат итератора
    void getWithRefers(T&, size_t, size_t, size_t, const size_t&, const size_t&) const; // поймать исключение
    void get(T&, const size_t&, const size_t&) const; // переделать на возврат итератора
    
    // debuging
    void getTree() const; // переименовать в wright и выводить в переданный поток
    
private:
    const size_t sizeOfArray_;
    const size_t sizeOfBottomLayer;
    T* const tree;
    T(*interactionFuncWithCopies)(T, T);
    void (*interactionFuncWithRefers)(T&, T&, T&);
    T extremeValue_;
    //T* beginOfLastLayer; // а может это должен быть итератор
    
    size_t initSizeOfBottomLayer();
    void setExtremeValue(const T&); // возможно, стоит добавить ловлю исключений
    void setExtremeValue(); // нужно добавить типов
    void setInteractionFunc(T(*)(T, T)); // возможно, стоит добавить ловлю исключений
    void setInteractionFunc(void (*)(T&, T&, T&)); // возможно, стоит добавить ловлю исключений
    
    enum class interactionFuncTypes {Copies, Refers};
    interactionFuncTypes interactionFuncType;
};



} // namespace addstd


#include <../src/segtree.cpp>

#endif // SEGTREE
