//
// Created by Aleksandras on 2023-06-08.
//

#include "Modread.h"

template<class T>
Modread<T>::Modread() = default;

template<class T>
Modread<T>::Modread(size_t size): arr(DynamicArray<T>(size)), removed(DynamicArray<bool>(size, false)) {}

template<class T>
Modread<T>::Modread(size_t size, T fillValue): arr(DynamicArray<T>(size, fillValue)),
                                               removed(DynamicArray<bool>(size, false)) {}

template<class T>
void Modread<T>::remove(size_t index) {
    modifications.push(Modification<T>{REMOVE, index, 0});
}

template<class T>
void Modread<T>::insert(size_t index, T value) {
    modifications.push(Modification<T>{INSERT, index, value});
}

template<class T>
T &Modread<T>::operator[](size_t index) {
    if (!modifications.empty()) {
        applyModifications();
    }

    return arr[index];
}

template<class T>
void Modread<T>::applyModifications() {
    while (!modifications.empty()) {
        auto &operation = modifications.front();
        modifications.pop();

        if (operation.type == REMOVE) {

        } else {

        }
    }
}

template
class Modread<int>;

template
class Modification<int>;
