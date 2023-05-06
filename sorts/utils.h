//
// Created by alexs on 2023-04-11.
//

#ifndef DSA_UTILS_H
#define DSA_UTILS_H

#include "gtest/gtest.h"

void expectVectorToBeSorted(const std::vector<int> &arr);

int compare(int a, int b);

std::vector<std::vector<int>> getTestsData();

#endif //DSA_UTILS_H
