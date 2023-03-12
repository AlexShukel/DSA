//
// Created by alexs on 2023-03-12.
//

#ifndef DSA_NODE_H
#define DSA_NODE_H

template<class T>
struct Node {
    T value;
    Node *left;
    Node *right;
    Node *parent;
    int balanceFactor;

    Node(T value, Node *parent);

    [[nodiscard]] bool isLeaf() const;
};

template<class T>
Node<T>::Node(T value, Node<T> *parent): value(value), left(nullptr), right(nullptr), parent(parent),
                                         balanceFactor(0) {}

template<class T>
bool Node<T>::isLeaf() const {
    return !left && !right;
}

#endif //DSA_NODE_H
