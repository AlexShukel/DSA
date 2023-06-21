//
// Created by alexs on 2023-04-11.
//

#include "gtest/gtest.h"
#include "cocktailShakerSort.h"
#include "utils.h"

TEST(sorts, cocktail_shaker) {
    auto tests = getTestsData();

    for (auto arr: tests) {
        cocktailShakerSort(arr.begin(), arr.end(), compare);
        expectSortedContainer(arr);
    }
}
