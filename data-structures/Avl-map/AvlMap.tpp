//
// Created by alexs on 2023-06-04.
//

#ifndef DSA_AVLMAP_TPP
#define DSA_AVLMAP_TPP

#include "AvlMap.hpp"
#include <queue>

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
Node<K, T> *AvlMap<K, T>::remove(const K &key) {
    Node<K, T> *from = BstMap<K, T>::remove(key);

    if (!from) {
        return nullptr;
    }

    updateBalanceFactors(from);
    NodeOverflow<K, T> nodeOverflow = findOverflowedNode(from);

    if (!nodeOverflow.X) {
        return from;
    }

    if (nodeOverflow.X == nodeOverflow.Z) {
        if (nodeOverflow.X->left) {
            nodeOverflow.Z = nodeOverflow.X->left;
        } else if (nodeOverflow.X->right) {
            nodeOverflow.Z = nodeOverflow.X->right;
        }
    }

    applyRotations(nodeOverflow.X, nodeOverflow.Z);
    return from;
}

template<class K, class T>
void AvlMap<K, T>::updateBalanceFactors(Node<K, T> *from) {
    while (from) {
        int leftHeight = from->left ? from->left->height : 0;
        int rightHeight = from->right ? from->right->height : 0;
        from->height = std::max(leftHeight + 1, rightHeight + 1);
        from = from->parent;
    }
}

template<class K, class T>
NodeOverflow<K, T> AvlMap<K, T>::findOverflowedNode(Node<K, T> *from) {
    auto prev = from;
    while (from && abs(from->getBalanceFactor()) < 2) {
        prev = from;
        from = from->parent;
    }

    return NodeOverflow<K, T>(from, prev);
}

template<class K, class T>
void AvlMap<K, T>::applyRotations(Node<K, T> *X, Node<K, T> *Z) {
    Node<K, T> *newRoot = nullptr;
    Node<K, T> *prevParent = X->parent;
    bool isLeft = false;
    if (X->parent) {
        isLeft = X->parent->left == X;
    }

    if (X->right == Z) {
        if (Z->getBalanceFactor() >= 0) {
            newRoot = rotateLeft(X, Z);
        } else {
            newRoot = rotateRightLeft(X, Z);
        }
    }

    if (X->left == Z) {
        if (Z->getBalanceFactor() <= 0) {
            newRoot = rotateRight(X, Z);
        } else {
            newRoot = rotateLeftRight(X, Z);
        }
    }

    if (prevParent) {
        if (isLeft) {
            prevParent->left = newRoot;
        } else {
            prevParent->right = newRoot;
        }
    } else {
        BstMap<K, T>::setRoot(newRoot);
    }

    updateBalanceFactors(prevParent);
}

template<class K, class T>
Node<K, T> *AvlMap<K, T>::rotateLeft(Node<K, T> *X, Node<K, T> *Z) {
    Node<K, T> *t23 = Z->left;
    X->right = t23;
    if (t23) {
        t23->parent = X;
    }

    Z->left = X;
    Z->parent = X->parent;
    X->parent = Z;

    X->height -= 2;
    Z->height = std::max(Z->left->height + 1, Z->right->height + 1);

    return Z;
}

template<class K, class T>
Node<K, T> *AvlMap<K, T>::rotateRight(Node<K, T> *X, Node<K, T> *Z) {
    Node<K, T> *t23 = Z->right;
    X->left = t23;
    if (t23) {
        t23->parent = X;
    }

    Z->right = X;
    Z->parent = X->parent;
    X->parent = Z;

    X->height -= 2;
    Z->height = std::max(Z->left->height + 1, Z->right->height + 1);

    return Z;
}

template<class K, class T>
Node<K, T> *AvlMap<K, T>::rotateRightLeft(Node<K, T> *X, Node<K, T> *Z) {
    Node<K, T> *prevParent = X->parent;

    Node<K, T> *Y = Z->left;

    Node<K, T> *t3 = Y->right;
    Z->left = t3;
    if (t3) {
        t3->parent = Z;
    }

    Node<K, T> *t2 = Y->left;
    X->right = t2;

    if (t2) {
        t2->parent = X;
    }

    Y->right = Z;
    Z->parent = Y;

    Y->left = X;
    X->parent = Y;
    Y->parent = prevParent;

    ++Y->height;
    X->height = std::max(t2 ? t2->height : 0, X->left ? X->left->height : 0) + 1;
    Z->height = std::max(t3 ? t3->height : 0, Z->right ? Z->right->height : 0) + 1;

    return Y;
}

template<class K, class T>
Node<K, T> *AvlMap<K, T>::rotateLeftRight(Node<K, T> *X, Node<K, T> *Z) {
    Node<K, T> *prevParent = X->parent;

    Node<K, T> *Y = Z->right;

    Node<K, T> *t2 = Y->right;
    X->left = t2;
    if (t2) {
        t2->parent = X;
    }

    Node<K, T> *t3 = Y->left;
    Z->right = t3;
    if (t3) {
        t3->parent = Z;
    }

    Y->right = X;
    X->parent = Y;

    Y->left = Z;
    Z->parent = Y;
    Y->parent = prevParent;

    ++Y->height;
    X->height = std::max(t2 ? t2->height : 0, X->right ? X->right->height : 0) + 1;
    Z->height = std::max(t3 ? t3->height : 0, Z->left ? Z->left->height : 0) + 1;

    return Y;
}

#ifdef AVL_TEST

template<class K, class T>
bool AvlMap<K, T>::isAvl() const {
    BstMapIterator<K, T> it = BstMap<K, T>::getIterator(INORDER);

    while (it.hasNext()) {
        if (it.getNode()->getBalanceFactor() >= 2) {
            return false;
        }
        ++it;
    }

    return true;
}

template<class K, class T>
void AvlMap<K, T>::printAvl() {
    Node<K, T> *root = BstMap<K, T>::getRoot();

    std::queue<std::pair<int, Node<K, T> *>> q;
    q.push({0, root});
    int prevDepth = -1;

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        int depth = current.first;
        Node<K, T> *node = current.second;

        if (depth != prevDepth) {
            std::cout << std::endl;
        }
        prevDepth = depth;

        if (!node) {
            std::cout << "X ";
            continue;
        }

//        std::cout << node->value << " " << node->getBalanceFactor() << " " << node->height << std::endl;

        std::cout << node->value << " ";

        q.push({depth + 1, node->left});
        q.push({depth + 1, node->right});
    }
}

#endif //AVL_TEST

#endif //DSA_AVLMAP_TPP
