//
// Created by alexs on 2023-06-04.
//

#define AVL_TEST

#include "gtest/gtest.h"
#include "AvlMap.hpp"
#include "utils.h"
#include <vector>
#include <set>

TEST(trees, avl_map_insertion_deletion) {
    AvlMap<int, int> map;

    map.remove(1);
    map.insert(1, 1);

    EXPECT_EQ(map.size(), 1);
    EXPECT_EQ(map.has(1), true);
    EXPECT_EQ(*map.get(1), 1);

    map.remove(1);

    EXPECT_EQ(map.size(), 0);
    EXPECT_EQ(map.has(1), false);
    EXPECT_EQ(map.get(1), nullptr);

    const int n = 255;
    for (int i = 0; i < n; ++i) {
        map.insert(i, i);
    }

    EXPECT_EQ(map.isAvl(), true);
    EXPECT_EQ(map.size(), n);
    EXPECT_EQ(map.has(0), true);
    EXPECT_EQ(map.has(n - 1), true);
    EXPECT_EQ(map.has(n), false);
    EXPECT_EQ(map.get(n), nullptr);
}

TEST(trees, avl_map_duplicates) {
    AvlMap<int, int> map;

    map.insert(1, 1);

    EXPECT_EQ(map.size(), 1);
    EXPECT_EQ(*map.get(1), 1);

    map.insert(1, 2);

    EXPECT_EQ(map.size(), 1);
    EXPECT_EQ(*map.get(1), 2);

    map.insert(2, 2);
    map.remove(1);

    EXPECT_EQ(map.size(), 1);
    EXPECT_EQ(map.get(1), nullptr);
    EXPECT_EQ(*map.get(2), 2);
}

TEST(trees, randomized_data) {
    auto tests = getTestsData();

    for (auto &testCase: tests) {
        AvlMap<int, int> map;
        std::set<int> set(testCase.begin(), testCase.end());

        for (auto x: testCase) {
            map.insert(x, x);
        }

        EXPECT_EQ(map.isAvl(), true);
        EXPECT_EQ(map.size(), set.size());

        for (auto x: testCase) {
            EXPECT_EQ(map.has(x), true);
            EXPECT_EQ(*map.get(x), x);
        }

        std::vector<int> correctVector(set.begin(), set.end());
        std::vector<int> myVector;
        auto it = map.getIterator(INORDER);

        while (it.hasNext()) {
            myVector.push_back(it.getNode()->value);
            ++it;
        }

        expectVectorsEquality(myVector, correctVector);
    }
}
