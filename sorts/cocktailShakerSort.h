//
// Created by alexs on 2023-04-11.
//

#ifndef DSA_COCKTAILSHAKERSORT_H
#define DSA_COCKTAILSHAKERSORT_H

#include <algorithm>

template<class RandomIt, class Compare>
void cocktailShakerSort(RandomIt first, RandomIt last, Compare compare) {
    size_t size = std::distance(first, last);

    if (size <= 1) {
        return;
    }

    int begin = 0, end = (int) size - 2;

    while (begin <= end) {
        bool rotating = false;
        typename RandomIt::value_type rotated = *first;

        int newBegin = end, newEnd = begin;

        int i;
        for (i = begin; i <= end; ++i) {
            bool shouldMove;

            if (rotating) {
                shouldMove = !compare(rotated, first[i + 1]);
            } else {
                shouldMove = !compare(first[i], first[i + 1]);
            }

            if (shouldMove) {
                if (!rotating) {
                    rotated = first[i];
                    rotating = true;
                }

                first[i] = first[i + 1];

                newEnd = i;
            }

            if (!shouldMove && rotating) {
                first[i] = rotated;
                rotating = false;
            }
        }

        if (rotating) {
            first[i] = rotated;
        }

        end = newEnd - 1;
        rotating = false;

        for (i = end; i >= begin; --i) {
            bool shouldMove;

            if (rotating) {
                shouldMove = !compare(first[i], rotated);
            } else {
                shouldMove = !compare(first[i], first[i + 1]);
            }

            if (shouldMove) {
                if (!rotating) {
                    rotated = first[i + 1];
                    rotating = true;
                }

                first[i + 1] = first[i];

                newBegin = i;
            }

            if (!shouldMove && rotating) {
                first[i + 1] = rotated;
                rotating = false;
            }
        }

        if (rotating) {
            first[begin] = rotated;
        }

        begin = newBegin + 1;
    }
}

#endif //DSA_COCKTAILSHAKERSORT_H
