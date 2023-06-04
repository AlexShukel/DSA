//
// Created by alexs on 2023-06-04.
//

#ifndef DSA_NODE_TPP
#define DSA_NODE_TPP

template<class K, class T>
Node<K, T>::Node(const K &key, const T &value, Node<K, T> *parent): key(key), value(value), left(nullptr),
                                                                    right(nullptr), parent(parent),
                                                                    height(1) {}

template<class K, class T>
bool Node<K, T>::isLeaf() const {
    return !left && !right;
}

template<class K, class T>
int Node<K, T>::getBalanceFactor() const {
    int leftHeight = left ? left->height : 0;
    int rightHeight = right ? right->height : 0;
    return rightHeight - leftHeight;
}

#endif //DSA_NODE_TPP
