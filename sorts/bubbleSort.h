//
// Created by alexs on 2023-04-11.
//

#ifndef DSA_BUBBLESORT_H
#define DSA_BUBBLESORT_H

#include <algorithm>

template<class T>
int compare(T a, T b) {
    if (a < b) {
        return -1;
    }

    if (a > b) {
        return 1;
    }

    return 0;
}

template<class RandomIt, class Compare>
void bubbleSort(RandomIt first, RandomIt last, Compare compare) {
    size_t size = std::distance(first, last);

    for (size_t i = 1; i < size; ++i) {
        bool swapped = false;

        bool rotating = false;
        typename RandomIt::value_type rotated = *first;

        size_t j;
        for (j = 0; j < size - i; ++j) {
            bool shouldMove;

            if (rotating) {
                shouldMove = compare(rotated, first[j + 1]) > 0;
            } else {
                shouldMove = compare(first[j], first[j + 1]) > 0;
            }

            if (shouldMove) {
                if (!rotating) {
                    rotated = first[j];
                    rotating = true;
                }

                first[j] = first[j + 1];
                swapped = true;
            }

            if (!shouldMove && rotating) {
                first[j] = rotated;
                rotating = false;
            }
        }

        if (rotating) {
            first[j] = rotated;
        }

        if (!swapped) {
            break;
        }
    }
}

#endif //DSA_BUBBLESORT_H
