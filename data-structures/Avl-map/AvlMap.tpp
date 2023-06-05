//
// Created by alexs on 2023-06-04.
//

#ifndef DSA_AVLMAP_TPP
#define DSA_AVLMAP_TPP

#include "AvlMap.hpp"

template<class K, class T>
Node<K, T> *AvlMap<K, T>::insert(const K &key, const T &value) {
    Node<K, T> *from = BstMap<K, T>::insert(key, value);

    updateBalanceFactors(from);
    NodeOverflow<K, T> nodeOverflow = findOverflowedNode(from);

    if (!nodeOverflow.X) {
        return from;
    }

    applyRotations(nodeOverflow.X, nodeOverflow.Z);

    return from;
}

template<class K, class T>
void AvlMap<K, T>::remove(const K &key) {
    BstMap<K, T>::remove(key);
}

template<class K, class T>
void AvlMap<K, T>::updateBalanceFactors(Node<K, T> *from) {
    if (from->parent) {
        if (from->parent->left == from && from->parent->right) {
            return;
        }

        if (from->parent->right == from && from->parent->left) {
            return;
        }
    }

    Node<K, T> *current = from->parent;

    while (current) {
        ++current->height;
        current = current->parent;
    }
}

template<class K, class T>
NodeOverflow<K, T> AvlMap<K, T>::findOverflowedNode(Node<K, T> *from) {
    
}

#endif //DSA_AVLMAP_TPP
