#include <vector>

#include "gtest/gtest.h"
#include "BST.h"
#include "testUtils.h"

TEST(BST, initialization) {
    // Should initialize empty BST
    BST<int> emptyBst;
}

TEST(BST, insertion) {
    BST<int> bst;

    bst.insert(5);

    EXPECT_EQ(bst.has(5), true);
    EXPECT_EQ(bst.has(1), false);
}

void freeNode(Node<int> *root) {
    if (root == nullptr) {
        return;
    }

    freeNode(root->left);
    freeNode(root->right);

    delete root;
}

TEST(BST_iterator, inorder) {
    auto root = new Node(5);
    root->left = new Node(3);
    root->right = new Node(6);
    root->left->left = new Node(2);
    root->left->right = new Node(4);

    BST_iterator<int> it(root, INORDER);

    std::vector<int> values;
    while (it.hasNext()) {
        values.push_back(*it);
        ++it;
    }

    expectVectorsEquality(values, {2, 3, 4, 5, 6});

    freeNode(root);
}

TEST(BST_iterator, preorder) {
    auto root = new Node(5);
    root->left = new Node(3);
    root->right = new Node(6);
    root->left->left = new Node(2);
    root->left->right = new Node(4);

    BST_iterator<int> it(root, PREORDER);

    std::vector<int> values;
    while (it.hasNext()) {
        values.push_back(*it);
        ++it;
    }

    expectVectorsEquality(values, {5, 3, 2, 4, 6});

    freeNode(root);
}

TEST(BST_iterator, postorder) {
    auto root = new Node(5);
    root->left = new Node(3);
    root->right = new Node(6);
    root->left->left = new Node(2);
    root->left->right = new Node(4);

    BST_iterator<int> it(root, POSTORDER);

    std::vector<int> values;
    while (it.hasNext()) {
        values.push_back(*it);
        ++it;
    }

    expectVectorsEquality(values, {2, 4, 3, 6, 5});

    freeNode(root);
}
