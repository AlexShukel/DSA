//
// Created by alexs on 2023-03-06.
//

#ifndef DSA_BST_HPP
#define DSA_BST_HPP

#include <vector>
#include <stack>
#include <stdexcept>
#include "Node.hpp"
#include "BST_iterator.hpp"

template<class T>
class BST {
protected:
    Node<T> *root;
    size_t height;
    size_t _size;

    Node<T> *findNode(int value) const;

    Node<T> *findInorderSuccessor(Node<T> *node) const;

    void removeImplementation(Node<T> *node);

public:
    explicit BST();

    ~BST();

    void insertFromVector(const std::vector<T> &values);

    virtual Node<T> *insert(T value);

    virtual void remove(T value);

    bool has(T value);

    BST_iterator<T> getIterator(TraverseOrder order) const;

    size_t getHeight() const;

    size_t size() const;
};

template<class T>
BST<T>::BST(): root(nullptr), height(0), _size(0) {}

template<class T>
BST<T>::~BST() {
    if (root) {
        BST_iterator<T> it(root, PREORDER);

        while (it.hasNext()) {
            delete it.getNode();
            ++it;
        }
    }
}

// Methods

template<class T>
void BST<T>::insertFromVector(const std::vector<T> &values) {
    for (auto x: values) {
        insert(x);
    }
}

template<class T>
Node<T> *BST<T>::insert(T value) {
    if (!root) {
        root = new Node<T>(value, (Node<T> *) nullptr);
        height = 1;
        ++_size;
        return root;
    }

    Node<T> *parent = root;
    Node<T> *node = root;

    while (node) {
        if (node->value == value) {
            return node;
        }

        parent = node;

        if (value < node->value) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    ++_size;
    if (parent->isLeaf()) {
        ++height;
    }

    if (value < parent->value) {
        parent->left = new Node<T>(value, parent);
        return parent->left;
    } else {
        parent->right = new Node<T>(value, parent);
        return parent->right;
    }
}

template<class T>
void BST<T>::remove(T value) {
    Node<T> *node = findNode(value);

    if (!node) {
        return;
    }

    removeImplementation(node);
}

template<class T>
BST_iterator<T> BST<T>::getIterator(TraverseOrder order) const {
    return BST_iterator<T>(root, order);
}

template<class T>
Node<T> *BST<T>::findNode(int value) const {
    Node<T> *node = root;

    while (node) {
        if (node->value == value) {
            break;
        }

        if (value < node->value) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return node;
}

template<class T>
Node<T> *BST<T>::findInorderSuccessor(Node<T> *node) const {
    while (node && node->left) {
        node = node->left;
    }

    return node;
}

template<class T>
void BST<T>::removeImplementation(Node<T> *node) {
    T value = node->value;

    // Node is leaf
    if (node->isLeaf()) {
        if (node->parent) {
            if (value < node->parent->value) {
                node->parent->left = nullptr;
            } else {
                node->parent->right = nullptr;
            }
        }

        delete node;
        return;
    }

    // Has one left child
    if (!node->right) {
        if (node->parent) {
            if (value < node->parent->value) {
                node->parent->left = node->left;
            } else {
                node->parent->right = node->left;
            }
        } else {
            root = node->left;
        }

        delete node;
        return;
    }

    // Has one right child
    if (!node->left) {
        if (node->parent) {
            if (value < node->parent->value) {
                node->parent->left = node->right;
            } else {
                node->parent->right = node->right;
            }
        } else {
            root = node->right;
        }

        delete node;
        return;
    }

    Node<T> *temp = findInorderSuccessor(node->right);
    node->value = temp->value;
    removeImplementation(temp);
}

template<class T>
bool BST<T>::has(T value) {
    return static_cast<bool>(findNode(value));
}

template<class T>
size_t BST<T>::size() const {
    return _size;
}

template<class T>
size_t BST<T>::getHeight() const {
    return height;
}

#endif //DSA_BST_HPP
