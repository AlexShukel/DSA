//
// Created by alexs on 2023-04-11.
//

#include "gtest/gtest.h"
#include "bubbleSort.h"
#include "utils.h"

TEST(sorts, bubble) {
    auto tests = getTestsData();

    for (auto arr: tests) {
        bubbleSort(arr.begin(), arr.end(), compare);
        expectVectorToBeSorted(arr);
    }
}
