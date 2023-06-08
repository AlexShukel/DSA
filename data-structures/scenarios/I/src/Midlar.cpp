//
// Created by alexs on 2023-06-07.
//

#include "Midlar.h"
#include <cstdint>
#include <algorithm>
#include <stdexcept>

#define REBALANCE_THRESHOLD 1000

template<class T>
Midlar<T>::Midlar() = default;

template<class T>
Midlar<T>::Midlar(size_t size) {
    uint8_t carry = size % 2;
    left.resize(size / 2 + carry);
    right.resize(size / 2);
}

template<class T>
Midlar<T>::Midlar(size_t size, T fillValue) {
    uint8_t carry = size % 2;

    left.resize(size / 2 + carry);
    std::fill(left.begin(), left.end(), fillValue);

    right.resize(size / 2);
    std::fill(right.begin(), right.end(), fillValue);
    right.reverse();
}

template<class T>
T &Midlar<T>::operator[](size_t index) {
    if (index >= size()) {
        throw std::out_of_range("ERROR: index out of range");
    }

    if (index < left.size()) {
        return left[index];
    }

    return right[getRightPartIndex(index)];
}

template<class T>
void Midlar<T>::insert(size_t index, T value) {
    if (index > size()) {
        throw std::out_of_range("ERROR: index out of range");
    }

    if (index <= left.size()) {
        left.insert(index, value);
    } else {
        right.insert(getRightPartIndex(index), value);
    }

    if (shouldRebalance()) {
        rebalance();
    }
}

template<class T>
void Midlar<T>::remove(size_t index) {
    if (index >= size()) {
        throw std::out_of_range("ERROR: index out of range");
    }

    if (index < left.size()) {
        left.remove(index);
    } else {
        right.remove(getRightPartIndex(index));
    }

    if (shouldRebalance()) {
        rebalance();
    }
}

template<class T>
size_t Midlar<T>::size() const {
    return left.size() + right.size();
}

template<class T>
size_t Midlar<T>::capacity() const {
    return left.capacity() + right.capacity();
}

template<class T>
size_t Midlar<T>::getRightPartIndex(size_t index) const {
    return right.size() - 1 - (index - left.size());
}

template<class T>
bool Midlar<T>::shouldRebalance() const {
    size_t max = std::max(left.size(), right.size());
    size_t min = std::min(left.size(), right.size());

    return max >= 4 && (max / 2 > min || max - min > REBALANCE_THRESHOLD);
}

template<class T>
void Midlar<T>::rebalance() {
    DynamicArray<T> &bigger = left.size() < right.size() ? right : left;
    DynamicArray<T> &smaller = left.size() < right.size() ? left : right;

    size_t diff = bigger.size() - smaller.size();
    size_t movedSize = diff / 2;

    size_t oldSmallerSize = smaller.size();
    size_t newSmallerSize = oldSmallerSize + movedSize;
    smaller.resize(newSmallerSize);

    size_t biggerSize = bigger.size();

    for (size_t i = oldSmallerSize; i < newSmallerSize; ++i) {
        smaller[i] = bigger[biggerSize - 1 - (i - oldSmallerSize)];
    }

    bigger.resize(biggerSize - movedSize);
}

template<class T>
void Midlar<T>::clear() {
    left.clear();
    right.clear();
}

template
class Midlar<int>;
