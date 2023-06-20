//
// Created by alexs on 2023-06-07.
//

#include "gtest/gtest.h"
#include "Midlar.h"
#include "utils.h"
#include <chrono>
#include <random>
#include <algorithm>

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
    for (size_t i = 1000; i <= 1e5; i *= 10) {
        Midlar<int> midlar;
        auto midlarTime = measureFirstScenario(midlar, i);

        VectorAdapter vector;
        auto vectorTime = measureFirstScenario(vector, i);

        EXPECT_LT(midlarTime, vectorTime);
    }
}

int findValueCount(Midlar<int> &midlar, int value) {
    int count = 0;
    for (auto x: midlar) {
        if (value == x) {
            ++count;
        }
    }
    return count;
}

TEST(midlar, stress_test) {
    Midlar<int> midlar;

    const int n = 1000;
    auto test = generateUniformDistributionArray(n);

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, n - 1); // define the range

    int sizeCounter = 0;
    for (auto x: test) {
        auto size = midlar.size();
        midlar.insert(size == 0 ? 0 : distr(gen) % midlar.size(), x);
        ++sizeCounter;
        EXPECT_EQ(midlar.size(), sizeCounter);
    }

    for (auto x: test) {
        bool found = false;

        for (auto value: midlar) {
            if (value == x) {
                found = true;
                break;
            }
        }

        if (!found) {
            ASSERT_TRUE(false) << "The element " << x << " not found!";
        }
    }

    std::sort(midlar.begin(), midlar.end());
    expectVectorToBeSorted(midlar);

    for (int i = 0; i < n; ++i) {
        size_t size = midlar.size();
        size_t index = distr(gen) % size;

        auto value = midlar[index];

        int before = findValueCount(midlar, value);
        midlar.remove(index);
        int after = findValueCount(midlar, value);

        EXPECT_EQ(before - after, 1);
    }
}

TEST(midlar, iterators) {
    const int n = 100;

    Midlar<int> midlar(n);
    std::vector<int> vec(n);

    for (int i = 0; i < n; ++i) {
        midlar[i] = i;
        vec[i] = i;
    }

    int i = 0;
    for (auto val: midlar) {
        EXPECT_EQ(val, vec[i]);
        ++i;
    }
}
