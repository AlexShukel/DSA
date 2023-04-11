//
// Created by alexs on 2023-04-11.
//

#include "utils.h"

void expectVectorToBeSorted(const std::vector<int> &arr) {
    for (int i = 0; i < arr.size() - 1; ++i) {
        EXPECT_GE(arr[i + 1], arr[i]);
    }
}

int compare(int a, int b) {
    return a - b;
}
