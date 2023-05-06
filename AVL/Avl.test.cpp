#include "gtest/gtest.h"
#include "Avl.hpp"

class TestAvl {
private:
    static void insertImplementationFromVector(const std::vector<int> &values, Avl<int> &tree) {
        for (auto x: values) {
            auto node = tree.insertNode(x);
            tree.updateBalanceFactors(node, false);
        }
    }

public:
    explicit TestAvl() = default;

    static void runLeftRotationsTest() {
        // When t1 and t23 are NULL
        {
            Avl<int> tree;

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
            Avl<int> tree;

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
            Avl<int> tree;

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
            Avl<int> tree;

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
        Avl<int> tree;

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
        Avl<int> tree;

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
            Avl<int> avl;
            insertImplementationFromVector({1, 2, 3}, avl);
            auto t = avl.findOverflowedNode(avl.root->right->right);
            EXPECT_EQ(t.X, avl.root);
            EXPECT_EQ(t.Z, avl.root->right);
        }

        {
            Avl<int> avl;
            insertImplementationFromVector({2, 1, 3}, avl);
            auto t = avl.findOverflowedNode(avl.root->right);
            EXPECT_EQ(t.X, nullptr);
        }
    }

    static void runInsertTest() {
        // left rotation
        {
            Avl<int> avl;

            avl.insertFromVector({1, 2, 3});

            EXPECT_EQ(avl.root->parent, nullptr);
            EXPECT_EQ(avl.root->value, 2);
            EXPECT_EQ(avl.root->left->value, 1);
            EXPECT_EQ(avl.root->right->value, 3);
        }

        // right rotation
        {
            Avl<int> avl;

            avl.insertFromVector({3, 2, 1});

            EXPECT_EQ(avl.root->parent, nullptr);
            EXPECT_EQ(avl.root->value, 2);
            EXPECT_EQ(avl.root->left->value, 1);
            EXPECT_EQ(avl.root->right->value, 3);
        }

        // right-left rotation
        {
            Avl<int> avl;

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
            Avl<int> avl;

            avl.insertFromVector({10, 12, 5, 6, 7, 4});

            EXPECT_EQ(avl.root->parent, nullptr);
            EXPECT_EQ(avl.root->value, 6);
            EXPECT_EQ(avl.root->left->value, 5);
            EXPECT_EQ(avl.root->left->left->value, 4);

            EXPECT_EQ(avl.root->right->value, 10);
            EXPECT_EQ(avl.root->right->right->value, 12);
            EXPECT_EQ(avl.root->right->left->value, 7);
        }

        {
            Avl<int> avl;
            avl.insertFromVector({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
            avl.insert(12);

            EXPECT_EQ(avl.root->value, 8);

            EXPECT_EQ(avl.root->left->value, 4);
            EXPECT_EQ(avl.root->left->left->value, 2);
            EXPECT_EQ(avl.root->left->left->left->value, 1);
            EXPECT_EQ(avl.root->left->left->left->isLeaf(), true);
            EXPECT_EQ(avl.root->left->left->right->value, 3);
            EXPECT_EQ(avl.root->left->left->right->isLeaf(), true);
            EXPECT_EQ(avl.root->left->right->value, 6);
            EXPECT_EQ(avl.root->left->right->left->value, 5);
            EXPECT_EQ(avl.root->left->right->left->isLeaf(), true);
            EXPECT_EQ(avl.root->left->right->right->value, 7);
            EXPECT_EQ(avl.root->left->right->right->isLeaf(), true);

            EXPECT_EQ(avl.root->right->value, 10);
            EXPECT_EQ(avl.root->right->left->value, 9);
            EXPECT_EQ(avl.root->right->left->isLeaf(), true);
            EXPECT_EQ(avl.root->right->right->value, 11);
            EXPECT_EQ(avl.root->right->right->right->value, 12);
            EXPECT_EQ(avl.root->right->right->right->isLeaf(), true);
            EXPECT_EQ(avl.root->right->right->left, nullptr);
        }
    }

    static void runDeletionTest() {
        {
            Avl<int> avl;
            avl.remove(5);
            avl.insert(5);
            EXPECT_EQ(avl.has(5), true);
            avl.remove(5);
            EXPECT_EQ(avl.has(5), false);
            EXPECT_EQ(avl.root, nullptr);
        }

        {
            Avl<int> avl;
            avl.insertFromVector({5, 7, 4, 3});
            avl.remove(7);

            EXPECT_EQ(avl.root->value, 4);
            EXPECT_EQ(avl.root->left->value, 3);
            EXPECT_EQ(avl.root->right->value, 5);
            EXPECT_EQ(avl.root->right->isLeaf(), true);
            EXPECT_EQ(avl.root->left->isLeaf(), true);
            EXPECT_EQ(avl.root->parent, nullptr);
        }

        {
            Avl<int> avl;
            avl.insertFromVector({8, 10, 4, 12, 6, 2, 1});
            avl.remove(10);

            EXPECT_EQ(avl.root->value, 4);
            EXPECT_EQ(avl.root->left->value, 2);
            EXPECT_EQ(avl.root->left->left->value, 1);
            EXPECT_EQ(avl.root->left->left->isLeaf(), true);
            EXPECT_EQ(avl.root->right->value, 8);
            EXPECT_EQ(avl.root->right->left->value, 6);
            EXPECT_EQ(avl.root->right->right->value, 12);
            EXPECT_EQ(avl.root->right->right->isLeaf(), true);
            EXPECT_EQ(avl.root->right->left->isLeaf(), true);
            EXPECT_EQ(avl.root->parent, nullptr);
        }
    }
};

TEST(AVL, leftRotation) {
    TestAvl::runLeftRotationsTest();
}

TEST(AVL, rightRotation) {
    TestAvl::runRightRotationsTest();
}

TEST(AVL, rightLeftRotation) {
    TestAvl::runRightLeftRotationsTest();
}

TEST(AVL, leftRightRotation) {
    TestAvl::runLeftRightRotationsTest();
}

TEST(AVL, findOverflowedNode) {
    TestAvl::runFindOverflowedNodeTest();
}

TEST(AVL, insert) {
    TestAvl::runInsertTest();
}

TEST(AVL, deletion) {
    TestAvl::runDeletionTest();
}
