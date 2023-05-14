//
// Created by alexs on 2023-04-16.
//

#ifndef DSA_HEAPSORT_H
#define DSA_HEAPSORT_H

#include <algorithm>

template<class RandomIt, class Compare>
void siftDown(RandomIt arr, int firstIndex, int lastIndex, Compare compare) {
    int root = firstIndex;

    while (root * 2 + 1 <= lastIndex) {
        int leftChild = root * 2 + 1;
        int rightChild = leftChild + 1;
        int swap = root;

        if (compare(arr[swap], arr[leftChild])) {
            swap = leftChild;
        }

        if (rightChild <= lastIndex && compare(arr[swap], arr[rightChild])) {
            swap = rightChild;
        }

        if (swap == root) {
            return;
        }

        std::swap(arr[root], arr[swap]);
        root = swap;
    }
}

template<class RandomIt, class Compare>
void heapify(RandomIt first, RandomIt last, Compare compare) {
    size_t size = std::distance(first, last);

    for (int i = (int) (size - 1) / 2; i >= 0; --i) {
        siftDown(first, i, size - 1, compare);
    }
}

template<class RandomIt, class Compare>
void heapSort(RandomIt first, RandomIt last, Compare compare) {
    heapify(first, last, compare);

    size_t size = std::distance(first, last);
    for (int i = (int) size - 1; i > 0; --i) {
        std::swap(*first, first[i]);
        siftDown(first, 0, i - 1, compare);
    }
}

#endif //DSA_HEAPSORT_H
