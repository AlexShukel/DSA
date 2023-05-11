//
// Created by alexs on 2023-05-07.
//

#include "gtest/gtest.h"
#include "HashTable.hpp"

TEST(hash_table, chaining_simple) {
    HashTable<int> table([](int item) { return item; }, 8);

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

TEST(hash_table, chaining_resizing) {
    HashTable<int> table([](int item) { return item; }, 4);

    EXPECT_EQ(table.getCapacity(), 4);
    table.insert(1);
    table.insert(2);
    table.insert(3);
    table.insert(4);
    table.insert(5);
    EXPECT_EQ(table.getCapacity(), 8);
    table.remove(5);
    EXPECT_EQ(table.getCapacity(), 8);
    table.remove(4);
    table.remove(3);
    table.remove(2);
    table.remove(1);
    EXPECT_EQ(table.getCapacity(), 4);
}
