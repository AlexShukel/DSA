//
// Created by alexs on 2023-04-11.
//

#include "utils.h"
#include <random>
#include <limits>
#include <ctime>

void expectVectorToBeSorted(const std::vector<int> &arr) {
    if (arr.size() <= 1) {
        return;
    }

    for (size_t i = 0; i < arr.size() - 1; ++i) {
        EXPECT_GE(arr[i + 1], arr[i]);
    }
}

bool compare(const int &a, const int &b) {
    return a <= b;
}

std::vector<int> generateRandomArray(size_t size) {
    srand(static_cast<unsigned int>(time(nullptr)));

    std::vector<int> arr;
    arr.resize(size);
    for (int &i: arr) {
        i = rand() % 100;
    }
    return arr;
}

std::vector<int> generateUniformDistributionArray(size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    std::vector<int> arr;
    arr.resize(size);
    for (int &i: arr) {
        i = dis(gen);
    }
    return arr;
}

std::vector<std::vector<int>> getTestsData() {
    std::vector<std::vector<int>> tests = {
            {},
            {0},
            {1, 0},
            {1, 5, 3, 2, 4, 9, 2},
            generateRandomArray(8),
            generateRandomArray(17),
            generateRandomArray(100),
            generateRandomArray(127),
            generateRandomArray(1000),
            generateUniformDistributionArray(8),
            generateUniformDistributionArray(17),
            generateUniformDistributionArray(100),
            generateUniformDistributionArray(127),
            generateUniformDistributionArray(1000),
    };

    return tests;
}
