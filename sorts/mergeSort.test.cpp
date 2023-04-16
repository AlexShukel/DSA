//
// Created by alexs on 2023-04-15.
//

#include "gtest/gtest.h"
#include "mergeSort.h"
#include "utils.h"

TEST(sorts, merge_sort) {
    std::vector<std::vector<int>> tests = {
            {1, 3, 5, 2, 0, 9, 6, 4, 3},
            {1, 3, 5, 2, 0, 9, 6, 4},
            {1, 3, 5, 2, 0, 9, 6},
            {},
            {1},
            {2, 1},
            {1, 0, 0, 0, 0}
    };

    for (auto arr: tests) {
        mergeSort(arr.begin(), arr.end(), compare);
        expectVectorToBeSorted(arr);
    }
}
