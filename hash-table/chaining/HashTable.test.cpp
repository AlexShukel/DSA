//
// Created by alexs on 2023-05-07.
//

#include "gtest/gtest.h"
#include "HashTable.hpp"

TEST(hash_table, chaining) {
    HashTable<int, size_t> table([](int item, size_t capacity) { return item % capacity; },
                                 [](size_t key) { return key; }, 8);

    EXPECT_EQ(table.has(1), false);
    table.insert(1);
    EXPECT_EQ(table.has(1), true);
    table.remove(1);
    EXPECT_EQ(table.has(1), false);

    table.insert(1);
    table.insert(17);
    table.insert(9);

    EXPECT_EQ(table.has(9), true);
    EXPECT_EQ(table.has(17), true);
    EXPECT_EQ(table.has(1), true);

    table.remove(17);
    EXPECT_EQ(table.has(17), false);
}
