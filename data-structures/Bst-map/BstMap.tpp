//
// Created by alexs on 2023-06-04.
//

#ifndef DSA_BSTMAP_TPP
#define DSA_BSTMAP_TPP

#include <iostream>
#include <queue>
#include "BstMap.hpp"

template<class K, class T>
BstMap<K, T>::BstMap(): root(nullptr), _size(0) {}

template<class K, class T>
BstMap<K, T>::~BstMap() {
    std::queue<Node<K, T> *> q;
    q.push(root);

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        if (!current) {
            continue;
        }

        q.push(current->left);
        q.push(current->right);
        delete current;
    }
}

template<class K, class T>
Node<K, T> *BstMap<K, T>::insert(const K &key, const T &value) {
    if (!root) {
        root = new Node<K, T>(key, value, (Node<K, T> *) nullptr);
        ++_size;
        return root;
    }

    Node<K, T> *parent = root;
    Node<K, T> *node = root;

    while (node) {
        if (node->key == key) {
            auto newNode = new Node<K, T>(value, node);

            if (node->parent) {
                if (node->parent->left == node) {
                    node->parent->left = newNode;
                } else {
                    node->parent->right = newNode;
                }
            } else {
                root = newNode;
            }

            delete node;
            return newNode;
        }

        parent = node;

        if (key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    ++_size;

    if (key < parent->key) {
        parent->left = new Node<K, T>(key, value, parent);
        return parent->left;
    } else {
        parent->right = new Node<K, T>(key, value, parent);
        return parent->right;
    }
}

template<class K, class T>
void BstMap<K, T>::remove(const K &key) {
    Node<K, T> *node = findNode(key);

    if (!node) {
        return;
    }

    --_size;
    removeImplementation(node);
}

template<class K, class T>
bool BstMap<K, T>::has(const K &key) {
    return findNode(key) != nullptr;
}

template<class K, class T>
T *BstMap<K, T>::get(const K &key) {
    auto ptr = findNode(key);

    if (!ptr) {
        return nullptr;
    }

    return &(ptr->value);
}

template<class K, class T>
size_t BstMap<K, T>::size() const {
    return _size;
}

template<class K, class T>
Node<K, T> *BstMap<K, T>::findNode(const K &key) const {
    Node<K, T> *node = root;

    while (node) {
        if (node->key == key) {
            break;
        }

        if (key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return node;
}

template<class K, class T>
Node<K, T> *BstMap<K, T>::findInorderSuccessor(Node<K, T> *node) const {
    while (node && node->left) {
        node = node->left;
    }

    return node;
}

template<class K, class T>
Node<K, T> *BstMap<K, T>::removeImplementation(Node<K, T> *node) {
    Node<K, T> *parent = node->parent;

    // Node is leaf
    if (node->isLeaf()) {
        if (parent) {
            if (node->key < parent->key) {
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

    // Has single child
    if (!node->right || !node->left) {
        auto subtree = node->right ? node->right : node->left;
        subtree->parent = parent;

        if (parent) {
            if (node->key < parent->key) {
                parent->left = subtree;
            } else {
                parent->right = subtree;
            }
        } else {
            root = subtree;
        }

        delete node;
        return parent;
    }

    Node<K, T> *temp = findInorderSuccessor(node->right);
    node->key = temp->key;
    node->value = temp->value;
    return removeImplementation(temp);
}

#endif //DSA_BSTMAP_TPP
