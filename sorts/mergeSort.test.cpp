//
// Created by alexs on 2023-04-15.
//

#include "gtest/gtest.h"
#include "mergeSort.h"
#include "utils.h"

TEST(sorts, merge_sort) {
    auto tests = getTestsData();

    for (auto arr: tests) {
        mergeSort(arr.begin(), arr.end(), compare);
        expectSortedContainer(arr);
    }
}
