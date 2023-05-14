//
// Created by alexs on 2023-05-07.
//

#include "gtest/gtest.h"
#include "HashTableSet.hpp"

TEST(hash_table_set, chaining_simple) {
    HashTableSet<int> table([](const int &item) { return item; }, 8);

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

    auto prevSize = table.getSize();
    table.insert(1);
    // Should insert only unique values
    EXPECT_EQ(table.getSize(), prevSize);
}

TEST(hash_table_set, chaining_resizing) {
    HashTableSet<int> table([](const int &item) { return item; }, 4);

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

TEST(hash_table_set, crash_test) {
    HashTableSet<std::string> table([](const std::string &item) {
        return item.size();
    }, 4);

    EXPECT_EQ(table.has(""), false);
    EXPECT_EQ(table.has("a"), false);
    EXPECT_EQ(table.has("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), false);
    table.remove("");
    table.remove("a");
    table.remove("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    table.insert("a");
    table.insert("a");
    table.insert("a");

    EXPECT_EQ(table.getSize(), 1);

    table.remove("");
    table.remove("b");
    table.remove("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    EXPECT_EQ(table.has("a"), true);

    table.insert("b");
    table.insert("c");
    table.insert("d");

    EXPECT_EQ(table.getSize(), 4);

    table.remove("a");

    EXPECT_EQ(table.has("b") && table.has("c") && table.has("d"), true);

    table.remove("c");
}
