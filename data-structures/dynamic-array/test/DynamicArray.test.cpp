//
// Created by alexs on 2023-06-07.
//

#include "gtest/gtest.h"
#include "DynamicArray.h"

TEST(dynamic_array, basic) {
    DynamicArray<int> arr(4, 1);

    EXPECT_EQ(arr.size(), 4);

    arr.insert(0, 2);

    EXPECT_EQ(arr.size(), 5);

    for (auto it = arr.begin(); it != arr.end(); ++it) {
        if (it == arr.begin()) {
            EXPECT_EQ(*it, 2);
        } else {
            EXPECT_EQ(*it, 1);
        }
    }

    arr.insert(0, 2);
    arr.insert(0, 2);
    arr.insert(0, 2);
    arr.insert(arr.size(), 42);
    EXPECT_EQ(arr[arr.size() - 1], 42);

    arr[arr.size() - 1] = 24;
    EXPECT_EQ(arr[arr.size() - 1], 24);
}

TEST(dynamic_array, remove) {
    DynamicArray<int> arr(2, 2);

    arr.remove(0);
    arr.remove(0);

    EXPECT_EQ(arr.size(), 0);

    EXPECT_THROW(arr.remove(0), std::out_of_range);

    arr.insert(0, 1);
    arr.insert(0, 1);
    arr.insert(0, 1);
    arr.insert(0, 1);
    arr.insert(0, 1);

    EXPECT_EQ(arr.size(), 5);
    for (int &it: arr) {
        EXPECT_EQ(it, 1);
    }
}
