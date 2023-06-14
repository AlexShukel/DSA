//
// Created by alexs on 2023-06-07.
//

#include "gtest/gtest.h"
#include "Midlar.h"
#include "utils.h"
#include <chrono>
#include <random>
#include <map>

TEST(midlar, basic) {
    Midlar<int> arr;

    arr.insert(0, 1);
    arr.insert(0, 2);

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 2);
    EXPECT_EQ(arr[1], 1);

    arr.insert(0, 3);
    arr.insert(0, 4);

    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0], 4);
    EXPECT_EQ(arr[1], 3);
    EXPECT_EQ(arr[2], 2);
    EXPECT_EQ(arr[3], 1);
}

class VectorAdapter {
private:
    std::vector<int> v;

public:
    void insert(size_t index, int value) {
        v.insert(v.begin() + static_cast<int>(index), value);
    }

    size_t size() const {
        return v.size();
    }
};

template<class Container>
long long measureFirstScenario(Container &arr, size_t n) {
    auto test = generateRandomArray(n);
    auto begin = std::chrono::high_resolution_clock::now();

    for (auto x: test) {
        arr.insert(arr.size() / 2, x);
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
}

TEST(midlar, benchmark_comparison) {
    for (size_t i = 100; i <= 1e5; i *= 10) {
        Midlar<int> midlar;
        auto midlarTime = measureFirstScenario(midlar, i);

        VectorAdapter vector;
        auto vectorTime = measureFirstScenario(vector, i);

        EXPECT_LT(midlarTime, vectorTime);
    }
}

TEST(midlar, stress_test) {
    Midlar<int> midlar;

    const int n = 1000;
    auto test = generateRandomArray(n);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, n - 1);

    // Insert random indexes
    for (auto x: test) {
        size_t size = midlar.size();
        auto idx = size == 0 ? 0 : distr(gen) % size;
        midlar.insert(idx, x);
    }

    std::map<int, int> frequency;

    for (int i = 0; i < n; ++i) {
        int originalCount = 0;
        int resultCount = 0;
        for (int j = 0; j < n; ++j) {
            if (test[j] == test[i]) {
                ++originalCount;
            }

            if (midlar[j] == test[i]) {
                ++resultCount;
            }
        }

        EXPECT_EQ(originalCount, resultCount);

        frequency.insert({test[i], originalCount});
    }

    const int m = 300;

    for (int i = 0; i < m; ++i) {
        auto idx = distr(gen) % midlar.size();
        int value = midlar[idx];
        midlar.remove(idx);

        int count = 0;
        for (int j = 0; j < midlar.size(); ++j) {
            if (midlar[j] == value) {
                ++count;
            }
        }

        EXPECT_EQ(count, frequency[value] - 1);
        --frequency[value];
    }
}
