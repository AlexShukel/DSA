//
// Created by alexs on 2023-04-15.
//

#ifndef DSA_MERGESORT_H
#define DSA_MERGESORT_H

#include <vector>

template<class RandomIt, class Compare>
void merge(RandomIt first, RandomIt mid, RandomIt last, Compare compare) {
    size_t size = std::distance(first, last);
    typedef typename std::iterator_traits<RandomIt>::value_type T;
    std::vector<T> temp;
    temp.resize(size);

    RandomIt left = first, right = mid;
    int i = 0;
    while (i < size) {
        if (left == mid) {
            temp[i] = *right;
            ++right;
        } else if (right == last) {
            temp[i] = *left;
            ++left;
        } else if (compare(*left, *right) > 0) {
            temp[i] = *right;
            ++right;
        } else {
            temp[i] = *left;
            ++left;
        }

        ++i;
    }

//    for (i = 0; i < size; ++i) {
//        std::cout << temp[i] << " ";
//    }
//    std::cout << std::endl;

    std::move(temp.begin(), temp.end(), first);
}

template<class RandomIt, class Compare>
void mergeSort(RandomIt first, RandomIt last, Compare compare) {
    size_t size = first == last ? 0 : std::distance(first, last);

    if (size <= 1) {
        return;
    }

    int subarraySize = 1;
    while (subarraySize < size) {
        subarraySize *= 2;
        int i;
        for (i = 0; i < size / subarraySize; ++i) {
            RandomIt begin = first + i * subarraySize;
            merge(begin, begin + subarraySize / 2, first + (i + 1) * subarraySize, compare);
        }

        RandomIt tailBegin = first + i * subarraySize;
        size_t tailSize = std::distance(tailBegin, last);
        if (tailSize > subarraySize / 2) {
            merge(tailBegin, tailBegin + subarraySize / 2, last, compare);
        }
    }
}

#endif //DSA_MERGESORT_H
