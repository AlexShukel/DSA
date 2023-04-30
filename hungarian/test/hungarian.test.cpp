//
// Created by alexs on 2023-04-28.
//

#include "gtest/gtest.h"
#include "../src/hungarian.h"
#include <fstream>
#include <vector>

TEST(algorithms, hungarian) {
    std::ifstream input("input.txt");
    int n = 0;
    input >> n;

    for (int i = 0; i < n; ++i) {
        int size;
        input >> size;

        std::vector<std::vector<int>> matrix;
        matrix.resize(size);
        for (int j = 0; j < size; ++j) {
            matrix[j].resize(size);
            for (int k = 0; k < size; ++k) {
                input >> matrix[j][k];
            }
        }

        auto outputMatrix = hungarian(matrix);

        int sum = 0, expectedSum = 0;
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                if (outputMatrix[j][k] == 1) {
                    sum += matrix[j][k];
                }
            }
        }

        input >> expectedSum;
        EXPECT_EQ(expectedSum, sum);
    }

    input.close();
}
