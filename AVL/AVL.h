//
// Created by alexs on 2023-03-11.
//

#ifndef DSA_AVL_H
#define DSA_AVL_H

#include "../BST/BST.h"

template<class T>
class AVL : public BST<T> {
    friend class TEST_AVL;

private:
    Node<T> *rotateLeft(Node<T> *X, Node<T> *Z);

    Node<T> *rotateRight(Node<T> *X, Node<T> *Z);

    Node<T> *rotateRightLeft(Node<T> *X, Node<T> *Z);

    Node<T> *rotateLeftRight(Node<T> *X, Node<T> *Z);

public:
    explicit AVL() = default;

    explicit AVL(const std::vector<T> &values);

    void insert(T value);

    void remove(T value);
};

template<class T>
AVL<T>::AVL(const std::vector<T> &values) {
    for (auto x: values) {
        insert(x);
    }
}

template<class T>
void AVL<T>::insert(T value) {
    this->insertImplementation(value);
}

template<class T>
void AVL<T>::remove(T value) {
    Node<T> *node = this->findNode(value);

    if (!node) {
        return;
    }

    this->removeImplementation(node);
}

// https://en.wikipedia.org/wiki/AVL_tree#Rebalancing
template<class T>
Node<T> *AVL<T>::rotateLeft(Node<T> *X, Node<T> *Z) {
    Node<T> *t23 = Z->left;
    X->right = t23;
    if (t23) {
        t23->parent = X;
    }

    Z->left = X;
    Z->parent = X->parent;
    X->parent = Z;

    if (Z->balanceFactor == 0) {
        ++X->balanceFactor;
        --Z->balanceFactor;
    } else {
        X->balanceFactor = 0;
        Z->balanceFactor = 0;
    }

    return Z;
}

template<class T>
Node<T> *AVL<T>::rotateRight(Node<T> *X, Node<T> *Z) {
    Node<T> *t23 = Z->right;
    X->left = t23;
    if (t23) {
        t23->parent = X;
    }

    Z->right = X;
    Z->parent = X->parent;
    X->parent = Z;

    if (Z->balanceFactor == 0) {
        ++X->balanceFactor;
        --Z->balanceFactor;
    } else {
        X->balanceFactor = 0;
        Z->balanceFactor = 0;
    }

    return Z;
}

template<class T>
Node<T> *AVL<T>::rotateRightLeft(Node<T> *X, Node<T> *Z) {
    return X;
}

template<class T>
Node<T> *AVL<T>::rotateLeftRight(Node<T> *X, Node<T> *Z) {
    return X;
}

#endif //DSA_AVL_H
