#include "gtest/gtest.h"
#include "AVL.h"
#include <iostream>

class TEST_AVL {
private:
    static void insertImplementationFromVector(const std::vector<int> &values, AVL<int> &tree) {
        for (auto x: values) {
            auto node = tree.insertImplementation(x);
            tree.updateBalanceFactors(node, false);
        }
    }

public:
    explicit TEST_AVL() = default;

    static void runLeftRotationsTest() {
        // When t1 and t23 are NULL
        {
            AVL<int> tree;

            insertImplementationFromVector({5, 6, 7}, tree);

            tree.root = tree.rotateLeft(tree.root, tree.root->right);

            EXPECT_EQ(tree.root->parent, nullptr);
            EXPECT_EQ(tree.root->value, 6);
            EXPECT_EQ(tree.root->left->value, 5);
            EXPECT_EQ(tree.root->right->value, 7);

            EXPECT_EQ(tree.root->height, 2);
            EXPECT_EQ(tree.root->right->height, 1);
            EXPECT_EQ(tree.root->left->height, 1);
        }

        {
            AVL<int> tree;

            insertImplementationFromVector({5, 3, 8, 10, 7, 12}, tree);

            tree.root = tree.rotateLeft(tree.root, tree.root->right);

            EXPECT_EQ(tree.root->parent, nullptr);
            EXPECT_EQ(tree.root->value, 8);
            EXPECT_EQ(tree.root->left->value, 5);
            EXPECT_EQ(tree.root->left->left->value, 3);
            EXPECT_EQ(tree.root->left->right->value, 7);
            EXPECT_EQ(tree.root->right->value, 10);
            EXPECT_EQ(tree.root->right->right->value, 12);

            EXPECT_EQ(tree.root->height, 3);
            EXPECT_EQ(tree.root->right->height, 2);
            EXPECT_EQ(tree.root->left->height, 2);
            EXPECT_EQ(tree.root->left->left->height, 1);
            EXPECT_EQ(tree.root->left->right->height, 1);
            EXPECT_EQ(tree.root->right->right->height, 1);
        }
    }

    static void runRightRotationsTest() {
        // When t1 and t23 are NULL
        {
            AVL<int> tree;

            insertImplementationFromVector({5, 4, 3}, tree);

            tree.root = tree.rotateRight(tree.root, tree.root->left);

            EXPECT_EQ(tree.root->parent, nullptr);
            EXPECT_EQ(tree.root->value, 4);
            EXPECT_EQ(tree.root->left->value, 3);
            EXPECT_EQ(tree.root->right->value, 5);

            EXPECT_EQ(tree.root->height, 2);
            EXPECT_EQ(tree.root->left->height, 1);
            EXPECT_EQ(tree.root->right->height, 1);
        }

        {
            AVL<int> tree;

            insertImplementationFromVector({10, 12, 5, 6, 4, 3}, tree);

            tree.root = tree.rotateRight(tree.root, tree.root->left);

            EXPECT_EQ(tree.root->parent, nullptr);
            EXPECT_EQ(tree.root->value, 5);
            EXPECT_EQ(tree.root->left->value, 4);
            EXPECT_EQ(tree.root->left->left->value, 3);
            EXPECT_EQ(tree.root->right->value, 10);
            EXPECT_EQ(tree.root->right->left->value, 6);
            EXPECT_EQ(tree.root->right->right->value, 12);

            EXPECT_EQ(tree.root->height, 3);
            EXPECT_EQ(tree.root->left->height, 2);
            EXPECT_EQ(tree.root->left->left->height, 1);
            EXPECT_EQ(tree.root->right->height, 2);
            EXPECT_EQ(tree.root->right->left->height, 1);
            EXPECT_EQ(tree.root->right->right->height, 1);
        }
    }

    static void runRightLeftRotationsTest() {
        AVL<int> tree;

        insertImplementationFromVector({5, 3, 10, 12, 7, 6}, tree);

        tree.root = tree.rotateRightLeft(tree.root, tree.root->right);

        EXPECT_EQ(tree.root->parent, nullptr);
        EXPECT_EQ(tree.root->value, 7);
        EXPECT_EQ(tree.root->left->value, 5);
        EXPECT_EQ(tree.root->left->left->value, 3);
        EXPECT_EQ(tree.root->left->right->value, 6);

        EXPECT_EQ(tree.root->right->value, 10);
        EXPECT_EQ(tree.root->right->right->value, 12);

        EXPECT_EQ(tree.root->height, 3);
        EXPECT_EQ(tree.root->right->height, 2);
        EXPECT_EQ(tree.root->right->right->height, 1);

        EXPECT_EQ(tree.root->left->height, 2);
        EXPECT_EQ(tree.root->left->left->height, 1);
        EXPECT_EQ(tree.root->left->right->height, 1);
    }

    static void runLeftRightRotationsTest() {
        AVL<int> tree;

        insertImplementationFromVector({10, 12, 5, 6, 7, 4}, tree);

        tree.root = tree.rotateLeftRight(tree.root, tree.root->left);

        EXPECT_EQ(tree.root->parent, nullptr);
        EXPECT_EQ(tree.root->value, 6);
        EXPECT_EQ(tree.root->left->value, 5);
        EXPECT_EQ(tree.root->left->left->value, 4);

        EXPECT_EQ(tree.root->right->value, 10);
        EXPECT_EQ(tree.root->right->right->value, 12);
        EXPECT_EQ(tree.root->right->left->value, 7);

        EXPECT_EQ(tree.root->height, 3);
        EXPECT_EQ(tree.root->left->height, 2);
        EXPECT_EQ(tree.root->left->left->height, 1);

        EXPECT_EQ(tree.root->right->height, 2);
        EXPECT_EQ(tree.root->right->left->height, 1);
        EXPECT_EQ(tree.root->right->right->height, 1);
    }

    static void runFindOverflowedNodeTest() {
        {
            AVL<int> avl;
            insertImplementationFromVector({1, 2, 3}, avl);
            auto [X, Z] = avl.findOverflowedNode(avl.root->right->right);
            EXPECT_EQ(X, avl.root);
            EXPECT_EQ(Z, avl.root->right);
        }

        {
            AVL<int> avl;
            insertImplementationFromVector({2, 1, 3}, avl);
            auto [X, Z] = avl.findOverflowedNode(avl.root->right);
            EXPECT_EQ(X, nullptr);
        }
    }

    static void runInsertTest() {
        // left rotation
        {
            AVL<int> avl;

            avl.insertFromVector({1, 2, 3});

            EXPECT_EQ(avl.root->parent, nullptr);
            EXPECT_EQ(avl.root->value, 2);
            EXPECT_EQ(avl.root->left->value, 1);
            EXPECT_EQ(avl.root->right->value, 3);
        }

        // right rotation
        {
            AVL<int> avl;

            avl.insertFromVector({3, 2, 1});

            EXPECT_EQ(avl.root->parent, nullptr);
            EXPECT_EQ(avl.root->value, 2);
            EXPECT_EQ(avl.root->left->value, 1);
            EXPECT_EQ(avl.root->right->value, 3);
        }

        // right-left rotation
        {
            AVL<int> avl;

            avl.insertFromVector({5, 3, 10, 12, 7, 6});

            EXPECT_EQ(avl.root->parent, nullptr);
            EXPECT_EQ(avl.root->value, 7);
            EXPECT_EQ(avl.root->left->value, 5);
            EXPECT_EQ(avl.root->left->left->value, 3);
            EXPECT_EQ(avl.root->left->right->value, 6);

            EXPECT_EQ(avl.root->right->value, 10);
            EXPECT_EQ(avl.root->right->right->value, 12);
        }

        // left-right rotation
        {
            AVL<int> avl;

            avl.insertFromVector({10, 12, 5, 6, 7, 4});

            EXPECT_EQ(avl.root->parent, nullptr);
            EXPECT_EQ(avl.root->value, 6);
            EXPECT_EQ(avl.root->left->value, 5);
            EXPECT_EQ(avl.root->left->left->value, 4);

            EXPECT_EQ(avl.root->right->value, 10);
            EXPECT_EQ(avl.root->right->right->value, 12);
            EXPECT_EQ(avl.root->right->left->value, 7);
        }
    }
};

TEST(AVL, leftRotation) {
    TEST_AVL::runLeftRotationsTest();
}

TEST(AVL, rightRotation) {
    TEST_AVL::runRightRotationsTest();
}

TEST(AVL, rightLeftRotation) {
    TEST_AVL::runRightLeftRotationsTest();
}

TEST(AVL, leftRightRotation) {
    TEST_AVL::runLeftRightRotationsTest();
}

TEST(AVL, findOverflowedNode) {
    TEST_AVL::runFindOverflowedNodeTest();
}

TEST(AVL, insert) {
    TEST_AVL::runInsertTest();
}
