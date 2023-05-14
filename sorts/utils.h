//
// Created by alexs on 2023-04-11.
//

#ifndef DSA_UTILS_H
#define DSA_UTILS_H

#include "gtest/gtest.h"

void expectVectorToBeSorted(const std::vector<int> &arr);

bool compare(const int &a, const int &b);

std::vector<std::vector<int>> getTestsData();

#endif //DSA_UTILS_H
