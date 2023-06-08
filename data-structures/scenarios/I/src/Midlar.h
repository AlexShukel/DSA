//
// Created by alexs on 2023-06-07.
//

#ifndef DSA_MIDLAR_H
#define DSA_MIDLAR_H

#include "DynamicArray.h"

template<class T>
class Midlar {
private:
    DynamicArray<T> left;
    DynamicArray<T> right;

    size_t getRightPartIndex(size_t index) const;

    bool shouldRebalance() const;

    void rebalance();

public:
    Midlar();

    explicit Midlar(size_t size);

    Midlar(size_t size, T fillValue);

    T &operator[](size_t index);

    void insert(size_t index, T value);

    void remove(size_t index);

    size_t size();

    void clear();
};

#endif //DSA_MIDLAR_H
