//
// Created by alexs on 2023-03-06.
//

#ifndef DSA_BST_HPP
#define DSA_BST_HPP

#include <vector>
#include <stack>
#include <stdexcept>
#include "Node.hpp"
#include "BstIterator.hpp"

template<class T>
class Bst {
protected:
    Node<T> *root;
    size_t height;
    size_t _size;

    Node<T> *findNode(int value) const;

    Node<T> *findInorderSuccessor(Node<T> *node) const;

    Node<T> *removeImplementation(Node<T> *node);

public:
    explicit Bst();

    ~Bst();

    void insertFromVector(const std::vector<T> &values);

    virtual Node<T> *insert(T value);

    virtual void remove(T value);

    bool has(T value);

    T *find(T value);

    BstIterator<T> getIterator(TraverseOrder order) const;

    size_t getHeight() const;

    size_t size() const;
};

template<class T>
Bst<T>::Bst(): root(nullptr), height(0), _size(0) {}

template<class T>
Bst<T>::~Bst() {
    if (root) {
        BstIterator<T> it(root, PREORDER);

        while (it.hasNext()) {
            delete it.getNode();
            ++it;
        }
    }
}

// Methods

template<class T>
void Bst<T>::insertFromVector(const std::vector<T> &values) {
    for (auto x: values) {
        insert(x);
    }
}

template<class T>
Node<T> *Bst<T>::insert(T value) {
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
void Bst<T>::remove(T value) {
    Node<T> *node = findNode(value);

    if (!node) {
        return;
    }

    removeImplementation(node);
}

template<class T>
BstIterator<T> Bst<T>::getIterator(TraverseOrder order) const {
    return BstIterator<T>(root, order);
}

template<class T>
Node<T> *Bst<T>::findNode(int value) const {
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
Node<T> *Bst<T>::findInorderSuccessor(Node<T> *node) const {
    while (node && node->left) {
        node = node->left;
    }

    return node;
}

template<class T>
Node<T> *Bst<T>::removeImplementation(Node<T> *node) {
    T value = node->value;

    Node<T> *parent = node->parent;

    // Node is leaf
    if (node->isLeaf()) {
        if (parent) {
            if (value < parent->value) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        } else {
            root = nullptr;
        }

        delete node;
        return parent;
    }

    // Has one left child
    if (!node->right) {
        if (parent) {
            if (value < parent->value) {
                parent->left = node->left;
            } else {
                parent->right = node->left;
            }
        } else {
            root = node->left;
        }

        delete node;
        return parent;
    }

    // Has one right child
    if (!node->left) {
        if (parent) {
            if (value < parent->value) {
                parent->left = node->right;
            } else {
                parent->right = node->right;
            }
        } else {
            root = node->right;
        }

        delete node;
        return parent;
    }

    Node<T> *temp = findInorderSuccessor(node->right);
    node->value = temp->value;
    return removeImplementation(temp);
}

template<class T>
bool Bst<T>::has(T value) {
    return static_cast<bool>(findNode(value));
}

template<class T>
T *Bst<T>::find(T value) {
    auto node = findNode(value);

    if (!node) {
        return nullptr;
    }

    return &(node->value);
}

template<class T>
size_t Bst<T>::size() const {
    return _size;
}

template<class T>
size_t Bst<T>::getHeight() const {
    return height;
}

#endif //DSA_BST_HPP
