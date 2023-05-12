//
// Created by alexs on 2023-04-24.
//

#ifndef DSA_INSERTIONSORT_H
#define DSA_INSERTIONSORT_H

#include <algorithm>

template<class RandomIt>
void insert(RandomIt first, RandomIt last) {
    typename RandomIt::value_type element = *last;
    for (auto it = last; it != first; --it) {
        *it = *(it - 1);
    }
    *first = element;
}

template<class RandomIt, class Compare>
void insertionSort(RandomIt first, RandomIt last, Compare compare) {
    if (first == last) {
        return;
    }

    for (auto end = first + 1; end != last; ++end) {
        RandomIt upperBound = std::upper_bound(first, end, *end, compare);

        if (upperBound != end) {
            insert(upperBound, end);
        }
    }
}

#endif //DSA_INSERTIONSORT_H
