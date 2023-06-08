//
// Created by alexs on 2023-06-07.
//

#ifndef DSA_DYNAMICARRAY_H
#define DSA_DYNAMICARRAY_H

#include <cstddef>

template<class T>
class DynamicArray {
private:
    T *arr;
    size_t _size;
    size_t capacity;

public:
    DynamicArray();

    explicit DynamicArray(size_t size);

    DynamicArray(size_t size, T fillValue);

    ~DynamicArray();

    T &operator[](size_t index);

    void insert(size_t index, T value);

    void remove(size_t index);

    void reverse();

    T *begin();

    T *end();

    size_t size() const;

    void clear();

    void resize(size_t newSize);

    void pushBack(T value);

    void popBack();

    T &back();
};

#endif //DSA_DYNAMICARRAY_H
