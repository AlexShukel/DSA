//
// Created by alexs on 2023-04-11.
//

#include "gtest/gtest.h"
#include "cocktailShakerSort.h"
#include "utils.h"

TEST(sorts, cocktail_shaker) {
    std::vector<int> arr = {5, 1, 4, 2, 8, 0, 2};
    cocktailShakerSort(arr.begin(), arr.end(), compare);
    expectVectorToBeSorted(arr);
}
