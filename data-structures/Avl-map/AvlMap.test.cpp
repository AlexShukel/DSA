//
// Created by alexs on 2023-06-04.
//

#define AVL_TEST

#include "gtest/gtest.h"
#include "AvlMap.hpp"
#include <vector>

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

    map.printAvl();
}
