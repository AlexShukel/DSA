//
// Created by alexs on 2023-05-14.
//

#include "gtest/gtest.h"
#include "HashTableMap.hpp"

TEST(hash_table_map, chaining_simple) {
    HashTableMap<int, std::string> table([](const int &key) {
        return key;
    }, 4);

    EXPECT_EQ(table.has(1), false);
    table.insert(1, "hello");
    EXPECT_EQ(table.has(1), true);
    EXPECT_EQ(*table.get(1), "hello");
    table.remove(1);
    EXPECT_EQ(table.has(1), false);
    EXPECT_EQ(table.get(1), nullptr);

    table.insert(1, "a");
    table.insert(17, "b");
    table.insert(9, "c");

    EXPECT_EQ(table.has(9), true);
    EXPECT_EQ(table.has(17), true);
    EXPECT_EQ(table.has(1), true);
    EXPECT_EQ(*table.get(17), "b");

    table.remove(17);
    EXPECT_EQ(table.has(17), false);

    EXPECT_EQ(*table.get(1), "a");
    auto prevSize = table.getSize();
    table.insert(1, "f");
    // Size should not change
    EXPECT_EQ(table.getSize(), prevSize);
    EXPECT_EQ(*table.get(1), "f");
}

TEST(hash_table_map, chaining_resizing) {
    HashTableMap<int, int> table([](const int &item) { return item; }, 4);

    EXPECT_EQ(table.getCapacity(), 4);
    table.insert(1, 100);
    table.insert(2, 100);
    table.insert(3, 100);
    table.insert(4, 100);
    table.insert(5, 100);
    EXPECT_EQ(table.getCapacity(), 8);
    table.remove(5);
    EXPECT_EQ(table.getCapacity(), 8);
    table.remove(4);
    table.remove(3);
    table.remove(2);
    table.remove(1);
    EXPECT_EQ(table.getCapacity(), 4);
}

TEST(hash_table_map, crash_test) {
    HashTableMap<std::string, std::string> table([](const std::string &item) {
        return item.size();
    }, 4);

    EXPECT_EQ(table.has(""), false);
    EXPECT_EQ(table.has("a"), false);
    EXPECT_EQ(table.has("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), false);
    table.remove("");
    table.remove("a");
    table.remove("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    table.insert("a", "value1");
    table.insert("a", "value2");
    table.insert("a", "value3");

    EXPECT_EQ(table.getSize(), 1);
    EXPECT_EQ(*table.get("a"), "value3");

    table.remove("");
    table.remove("b");
    table.remove("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    EXPECT_EQ(table.has("a"), true);

    table.insert("b", "gg");
    table.insert("c", "gg");
    table.insert("d", "gg");

    EXPECT_EQ(table.getSize(), 4);

    table.remove("a");

    EXPECT_EQ(table.has("b") && table.has("c") && table.has("d"), true);

    table.remove("c");
}
