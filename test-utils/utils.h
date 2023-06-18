//
// Created by alexs on 2023-06-05.
//

#ifndef DSA_UTILS_H
#define DSA_UTILS_H

#include "gtest/gtest.h"
#include <vector>

void expectVectorToBeSorted(const std::vector<int> &arr);

bool compare(const int &a, const int &b);

std::vector<std::vector<int>> getTestsData();

std::vector<int> generateRandomArray(size_t size);

std::vector<int> generateUniformDistributionArray(size_t size);

template<class T>
void expectVectorsEquality(const std::vector<T> &a, const std::vector<T> &b) {
    ASSERT_EQ(a.size(), b.size());

    for (int i = 0; i < a.size(); ++i) {
        EXPECT_EQ(a[i], b[i]);
    }
}

#endif //DSA_UTILS_H