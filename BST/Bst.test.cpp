#include <vector>

#include "gtest/gtest.h"
#include "Bst.hpp"
#include "testUtils.h"

TEST(Bst, insertion) {
    Bst<int> bst;

    EXPECT_EQ(bst.has(5), false);
    bst.insert(5);
    EXPECT_EQ(bst.has(5), true);
}

TEST(Bst, leafDeletion) {
    Bst<int> bst;
    bst.insertFromVector({5, 3, 6, 2, 4});

    EXPECT_EQ(bst.has(6), true);
    bst.remove(6);
    EXPECT_EQ(bst.has(6), false);

    EXPECT_EQ(bst.has(2), true);
    bst.remove(2);
    EXPECT_EQ(bst.has(2), false);
}

TEST(Bst, singleChildDeletion) {
    {
        Bst<int> bst;
        bst.insertFromVector({5, 3, 6, 2, 4, 0});

        EXPECT_EQ(bst.has(2), true);
        bst.remove(2);
        EXPECT_EQ(bst.has(2), false);
        EXPECT_EQ(bst.has(0), true);
    }

    // Root has one child
    {
        Bst<int> bst;
        bst.insertFromVector({1, 2, 3, 4});

        EXPECT_EQ(bst.has(1), true);
        bst.remove(1);
        EXPECT_EQ(bst.has(1), false);
        EXPECT_EQ(bst.has(4), true);
    }
}

TEST(Bst, deletion) {
    {
        Bst<int> bst;
        bst.insertFromVector({50, 70, 60, 65, 80, 85, 75, 30, 20, 40, 32, 34, 36});

        bst.remove(70);
        EXPECT_EQ(bst.has(70), false);
    }

    {
        Bst<int> bst;
        bst.insertFromVector({50, 70, 60, 65, 80, 85, 75, 30, 20, 40, 32, 34, 36});

        bst.remove(30);
        EXPECT_EQ(bst.has(30), false);
    }
}

TEST(BST_iterator, inorder) {
    Bst<int> bst;
    bst.insertFromVector({5, 3, 6, 2, 4});
    auto it = bst.getIterator(INORDER);

    std::vector<int> values;
    while (it.hasNext()) {
        values.push_back(it.getValue());
        ++it;
    }

    expectVectorsEquality(values, {2, 3, 4, 5, 6});
}

TEST(BST_iterator, preorder) {
    Bst<int> bst;
    bst.insertFromVector({5, 3, 6, 2, 4});
    auto it = bst.getIterator(PREORDER);

    std::vector<int> values;
    while (it.hasNext()) {
        values.push_back(it.getValue());
        ++it;
    }

    expectVectorsEquality(values, {5, 3, 2, 4, 6});
}

TEST(BST_iterator, postorder) {
    Bst<int> bst;
    bst.insertFromVector({5, 3, 6, 2, 4});
    auto it = bst.getIterator(POSTORDER);

    std::vector<int> values;
    while (it.hasNext()) {
        values.push_back(it.getValue());
        ++it;
    }

    expectVectorsEquality(values, {2, 4, 3, 6, 5});
}

TEST(Bst, getHeight) {
    Bst<int> bst;
    EXPECT_EQ(bst.getHeight(), 0);
    bst.insert(5);
    EXPECT_EQ(bst.getHeight(), 1);
    bst.insert(3);
    bst.insert(7);
    EXPECT_EQ(bst.getHeight(), 2);
    bst.insert(7);
    EXPECT_EQ(bst.getHeight(), 2);
}

TEST(Bst, getSize) {
    Bst<int> bst;
    EXPECT_EQ(bst.size(), 0);
    bst.insert(5);
    EXPECT_EQ(bst.size(), 1);
    bst.insert(5);
    EXPECT_EQ(bst.size(), 1);

    bst.insert(4);
    bst.insert(5);
    bst.insert(13);
    EXPECT_EQ(bst.size(), 3);
}
