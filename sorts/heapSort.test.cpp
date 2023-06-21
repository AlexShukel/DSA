//
// Created by alexs on 2023-04-16.
//

#include "gtest/gtest.h"
#include "heapSort.h"
#include "utils.h"

TEST(sorts, heap_sort) {
    auto tests = getTestsData();

    for (auto arr: tests) {
        heapSort(arr.begin(), arr.end(), compare);
        expectSortedContainer(arr);
    }
}
