//
// Created by alexs on 2023-04-24.
//

#include "gtest/gtest.h"
#include "insertionSort.h"
#include "utils.h"

TEST(sorts, insertion_sort) {
    auto tests = getTestsData();

    for (auto arr: tests) {
        insertionSort(arr.begin(), arr.end(), compare);
        expectVectorToBeSorted(arr);
    }
}
