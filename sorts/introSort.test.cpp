//
// Created by alexs on 2023-04-16.
//

#include "gtest/gtest.h"
#include "introSort.h"
#include "utils.h"

TEST(sorts, intro_sort) {
    auto tests = getTestsData();

    for (auto arr: tests) {
        introSort(arr.begin(), arr.end(), compare);
        expectSortedContainer(arr);
    }
}
