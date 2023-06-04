//
// Created by alexs on 2023-06-04.
//

#include <utility>

#include "gtest/gtest.h"
#include "BstMap.hpp"

TEST(trees, bst_map) {
    BstMap<int, int> map;

    map.insert(5, 5);

    EXPECT_EQ(map.size(), 1);
    EXPECT_EQ(map.has(5), true);
    EXPECT_EQ(map.has(4), false);
    EXPECT_EQ(*map.get(5), 5);
    EXPECT_EQ(map.get(4), nullptr);

    map.remove(5);

    EXPECT_EQ(map.size(), 0);
    EXPECT_EQ(map.has(5), false);
    EXPECT_EQ(map.get(5), nullptr);

    // Remove non-existing entries
    map.remove(0);
    map.remove(1);

    map.insert(5, 5);
    map.insert(6, 6);
    map.insert(7, 7);

    EXPECT_EQ(map.size(), 3);
    EXPECT_EQ(map.has(5), true);
    EXPECT_EQ(map.has(6), true);
    EXPECT_EQ(map.has(7), true);
    EXPECT_EQ(map.has(8), false);
    EXPECT_EQ(*map.get(5), 5);
    EXPECT_EQ(*map.get(6), 6);
    EXPECT_EQ(*map.get(7), 7);

    map.insert(3, 3);
    map.insert(4, 4);
    map.insert(2, 2);

    // Remove root
    map.remove(5);

    EXPECT_EQ(map.size(), 5);
    EXPECT_EQ(map.has(5), false);
    EXPECT_EQ(map.has(2), true);
    EXPECT_EQ(map.has(3), true);
    EXPECT_EQ(map.has(4), true);
    EXPECT_EQ(map.has(6), true);
    EXPECT_EQ(map.has(7), true);

    map.remove(7);

    // Remove single child root
    map.remove(6);

    EXPECT_EQ(map.size(), 3);
    EXPECT_EQ(map.has(6), false);
    EXPECT_EQ(map.has(2), true);
    EXPECT_EQ(map.has(3), true);
    EXPECT_EQ(map.has(4), true);
}
