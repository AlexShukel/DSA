//
// Created by alexs on 2023-03-11.
//

#ifndef DSA_BSTITERATOR_HPP
#define DSA_BSTITERATOR_HPP

#include "Node.hpp"
#include <queue>
#include <stdexcept>
#include <algorithm>

enum TraverseOrder {
    INORDER,
    PREORDER,
    POSTORDER,
};

template<class K, class T>
class BstMapIterator {
private:
    std::queue<Node<K, T> *> values;

    void constructInorder(Node<K, T> *current);

    void constructPreorder(Node<K, T> *current);

    void constructPostorder(Node<K, T> *current);

public:
    BstMapIterator(Node<K, T> *root, TraverseOrder order);

    BstMapIterator &operator++();

    Node<K, T> *getNode() const;

    [[nodiscard]] bool hasNext() const;
};

template<class K, class T>
void BstMapIterator<K, T>::constructPostorder(Node<K, T> *current) {
    if (current->isLeaf()) {
        values.push(current);
        return;
    }

    if (current->left) {
        constructInorder(current->left);
    }

    if (current->right) {
        constructInorder(current->right);
    }

    values.push(current);
}

template<class K, class T>
void BstMapIterator<K, T>::constructPreorder(Node<K, T> *current) {
    if (current->isLeaf()) {
        values.push(current);
        return;
    }

    values.push(current);

    if (current->left) {
        constructInorder(current->left);
    }

    if (current->right) {
        constructInorder(current->right);
    }
}

template<class K, class T>
void BstMapIterator<K, T>::constructInorder(Node<K, T> *current) {
    if (current->isLeaf()) {
        values.push(current);
        return;
    }

    if (current->left) {
        constructInorder(current->left);
    }

    values.push(current);

    if (current->right) {
        constructInorder(current->right);
    }
}

template<class K, class T>
BstMapIterator<K, T>::BstMapIterator(Node<K, T> *root, TraverseOrder order) {
    if (!root) {
        return;
    }

    switch (order) {
        // LVD (left, vertex, right)
        case INORDER: {
            constructInorder(root);

            break;
        }

            // VLR (vertex, left, right)
        case PREORDER: {
            constructPreorder(root);

            break;
        }

            // LRV (left, right, vertex)
        case POSTORDER: {
            constructPostorder(root);

            break;
        }

        default: {
            throw std::invalid_argument("Invalid traverse order.");
        }
    }
}

template<class K, class T>
BstMapIterator<K, T> &BstMapIterator<K, T>::operator++() {
    values.pop();
    return *this;
}

template<class K, class T>
Node<K, T> *BstMapIterator<K, T>::getNode() const {
    return values.front();
}

template<class K, class T>
bool BstMapIterator<K, T>::hasNext() const {
    return !values.empty();
}

#endif //DSA_BSTITERATOR_HPP
