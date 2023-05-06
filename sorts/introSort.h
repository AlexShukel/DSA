//
// Created by alexs on 2023-04-16.
//

#ifndef DSA_INTROSORT_H
#define DSA_INTROSORT_H

#include "heapSort.h"

template<class RandomIt, class Compare>
RandomIt partitionHoare(RandomIt first, RandomIt last, Compare compare) {
    auto pivot = last - 1;
    auto i = first, j = pivot - 1;

    while (true) {
        while (compare(*i, *pivot) <= 0 && i != last - 1) {
            ++i;
        }

        while (compare(*j, *pivot) > 0 && j != first) {
            --j;
        }

        if (i >= j) {
            break;
        }

        std::swap(*i, *j);
        ++i;
        --j;
    }

    std::swap(*i, *pivot);
    return i;
}

template<class RandomIt, class Compare>
void introSortImpl(RandomIt first, RandomIt last, Compare compare, int maxDepth) {
    if (std::distance(first, last) <= 1) {
        return;
    }

    if (maxDepth == 0) {
        heapSort(first, last, compare);
        return;
    }

    auto pivot = partitionHoare(first, last, compare);

    introSortImpl(first, pivot, compare, maxDepth - 1);
    introSortImpl(pivot, last, compare, maxDepth - 1);
}

#define MAX_RECURSION_DEPTH 100

template<class RandomIt, class Compare>
void introSort(RandomIt first, RandomIt last, Compare compare) {
    introSortImpl(first, last, compare, MAX_RECURSION_DEPTH);
}

#endif //DSA_INTROSORT_H
