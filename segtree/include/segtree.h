#include <iostream> // убрать

#ifndef SEGTREE
#define SEGTREE

namespace adstd { // algorithms and data structures templates definition 



template<class T>
T minOfSubsegment(const T&, const T&); // надо будет ловить исключения на не соответствие типов

template<class T>
T maxOfSubsegment(const T&, const T&); // надо будет ловить исключения на не соответствие типов

template<class T>
T sumOfSubsegment(const T&, const T&); // надо будет ловить исключения на не соответствие типов


template<class T>
class segtree {
public:
    
    class iterator {
    public:
        void moveLeft();
        void moveRight();
    
    private:
        size_t index{0};
    };

    //segtree(size_t, T/*initialization value*/, /*ссылка на ф-ию взаимодействия*/); //для не стандартных типов данных
    //segtree(size_t, /*ссылка на ф-ию взаимодействия*/);
                     // дерево по умолчанию (мин) для стандартных 
                     // типов (?bool, ?char, ?short, int, ?float, long long, ?double,
                     // ?long double, ?unsigned char & short, unsigned int & long long, pair <..., ...>, set <...>, ?map <...>,
                     // ?unordered set & map, ??string, ?vector, ?int[], ?char[], ??long long[], ...)
                     // 
                     // имеет возможность давать ссылки на
                     // стандартные ф-ии взаимодействия (макс, сум, ...)
    segtree(size_t, const T&, T(*)(const T&, const T&)); 
    segtree(size_t, T(*)(const T&, const T&) = sumOfSubsegment); 
    segtree() = delete;
    ~segtree();
    
    segtree(const segtree&) = delete;
    segtree& operator=(const segtree&) = delete;
    
    //добавить класс итераторов
    //void read(); // вводить с переданного потока
    //build == read
    //iterator<t> begin();
    
    void clear();
    void refresh(const T&, T(*)(const T&, const T&));
    void refresh(T(*)(const T&, const T&));
    //refresh() == clear()
    
    void set(size_t, size_t, size_t, const size_t&, const T&); // поймать исключение
    void set(const size_t&, const T&); 
    T get(size_t, size_t, size_t, const size_t&, const size_t&) const; // поймать исключение
    T get(const size_t&, const size_t&) const; // переделать на возврат итератора
    
    // debuging
    void getTree() const; // переименовать в wright и выводить в переданный поток
    
private:
    const size_t sizeOfArray_;
    const size_t sizeOfBottomLayer;
    T* const tree;
    T(*interactionFunc_)(const T&, const T&);
    T extremeValue_;
    //T* beginOfLastLayer; // а может это должен быть итератор
    
    size_t initSizeOfBottomLayer();
    void setInteractionFunc(T(*)(const T&, const T&)); // возможно, стоит добавить ловлю исключений
    void setExtremeValue(const T&); // возможно, стоит добавить ловлю исключений
    void setExtremeValue(); // нужно добавить типов
};



} // namespace adstd


#include <../src/segtree.cpp>

#endif // SEGTREE
