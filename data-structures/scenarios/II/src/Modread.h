//
// Created by Aleksandras on 2023-06-08.
//

#ifndef DSA_MODREAD_H
#define DSA_MODREAD_H

#include "DynamicArray.h"
#include <queue>

enum ModificationType {
    INSERT,
    REMOVE
};

template<class T>
struct Modification {
    ModificationType type;
    size_t index;
    T value;
};

template<class T>
class Modread {
private:
    DynamicArray<T> arr;
    DynamicArray<bool> removed;
    std::queue<Modification<T>> modifications;

    void applyModifications();

public:
    Modread();

    explicit Modread(size_t size);

    Modread(size_t size, T fillValue);

    T &operator[](size_t index);

    void insert(size_t index, T value);

    void remove(size_t index);

//    void reverse();
//
//    T *begin();
//
//    T *end();
//
//    size_t size() const;
//
//    size_t capacity() const;
//
//    void clear();
//
//    void resize(size_t newSize);
//
//    void pushBack(T value);
//
//    void popBack();
//
//    T &back();
};

#endif //DSA_MODREAD_H
