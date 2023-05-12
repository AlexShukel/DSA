//
// Created by alexs on 2023-04-24.
//

#include "gtest/gtest.h"
#include "insertionSort.h"
#include "utils.h"

bool compare_bounds(const int &a, const int &b) {
    return a < b;
}

TEST(sorts, insertion_sort) {
    auto tests = getTestsData();

    for (auto arr: tests) {
        insertionSort(arr.begin(), arr.end(), compare_bounds);
        expectVectorToBeSorted(arr);
    }
}
