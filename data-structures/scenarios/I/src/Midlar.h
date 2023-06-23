//
// Created by alexs on 2023-06-07.
//

#ifndef DSA_MIDLAR_H
#define DSA_MIDLAR_H

#include "DynamicArray.h"
#include <iterator>

template<class T>
class Midlar {
    class Iterator {
    private:
        Midlar<T> *arr;
        size_t index;

    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using iterator_category = std::random_access_iterator_tag;

        Iterator(Midlar<T> *arr, size_t index);

        T &operator*() const;

        T *operator->();

        Iterator &operator++();

        Iterator operator++(int);

        Iterator &operator--();

        Iterator operator--(int);

        bool operator!=(const Iterator &other) const;

        bool operator==(const Iterator &other) const;

        bool operator<(const Iterator &other) const;

        bool operator>(const Iterator &other) const;

        bool operator<=(const Iterator &other) const;

        bool operator>=(const Iterator &other) const;

        Iterator operator+(size_t n) const;

        Iterator &operator+=(size_t n);

        Iterator operator-(size_t n) const;

        Iterator &operator-=(size_t n);

        difference_type operator-(const Iterator &other) const;

        reference operator[](size_t n) const;
    };

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

    const T &operator[](size_t index) const;

    void insert(size_t index, T value);

    void remove(size_t index);

    size_t size() const;

    size_t maxSize() const;

    void clear();

    Iterator begin();

    Iterator end();
};

#endif //DSA_MIDLAR_H
