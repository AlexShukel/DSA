//
// Created by alexs on 2023-06-07.
//

#include "DynamicArray.h"
#include <cstdlib>
#include <algorithm>
#include <stdexcept>
#include <limits>

template<class T>
DynamicArray<T>::DynamicArray(): arr(nullptr), _size(0), _capacity(0) {}

template<class T>
DynamicArray<T>::DynamicArray(size_t size): arr((T *) malloc(size * sizeof(T))), _size(size), _capacity(size) {}

template<class T>
DynamicArray<T>::DynamicArray(size_t size, T fillValue): arr((T *) malloc(size * sizeof(T))), _size(size),
                                                         _capacity(size) {
    std::fill(arr, arr + size, fillValue);
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    free(arr);
}

template<class T>
T &DynamicArray<T>::operator[](size_t index) {
    if (index >= _size) {
        throw std::out_of_range("ERROR: index out of range");
    }

    return arr[index];
}

template<class T>
void DynamicArray<T>::insert(size_t index, T value) {
    if (index > _size) {
        throw std::out_of_range("ERROR: index out of range");
    }

    ++_size;
    if (_size > _capacity) {
        _capacity = std::max((size_t) 2, _capacity * 2);
        arr = (T *) realloc(arr, _capacity * sizeof(T));
    }

    for (size_t i = _size - 1; i > index; --i) {
        arr[i] = arr[i - 1];
    }
    arr[index] = value;
}

template<class T>
void DynamicArray<T>::remove(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("ERROR: index out of range");
    }

    --_size;
    for (size_t i = index; i < _size; ++i) {
        arr[i] = arr[i + 1];
    }

    if (_size <= _capacity / 2) {
        _capacity /= 2;
        arr = (T *) realloc(arr, _capacity * sizeof(T));
    }
}

template<class T>
T *DynamicArray<T>::begin() {
    return arr;
}

template<class T>
T *DynamicArray<T>::end() {
    return arr + _size;
}

template<class T>
size_t DynamicArray<T>::size() const {
    return _size;
}

template<class T>
size_t DynamicArray<T>::maxSize() const {
    return std::numeric_limits<size_t>::max();
}

template<class T>
void DynamicArray<T>::clear() {
    free(arr);
    _size = 0;
    _capacity = 0;
}

template<class T>
void DynamicArray<T>::resize(size_t newSize) {
    arr = (T *) realloc(arr, newSize * sizeof(T));
    _size = newSize;
    _capacity = newSize;
}

template<class T>
void DynamicArray<T>::pushBack(T value) {
    insert(_size, value);
}

template<class T>
void DynamicArray<T>::popBack() {
    remove(_size - 1);
}

template<class T>
T &DynamicArray<T>::back() {
    return arr[_size - 1];
}

template
class DynamicArray<int>;
