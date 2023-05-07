//
// Created by alexs on 2023-03-12.
//

#ifndef DSA_NODE_HPP
#define DSA_NODE_HPP

template<class T>
struct Node {
    T value;
    Node *left;
    Node *right;
    Node *parent;
    int height;

    Node(const T &value, Node *parent);

    [[nodiscard]] bool isLeaf() const;

    [[nodiscard]] int getBalanceFactor() const;
};

template<class T>
Node<T>::Node(const T &value, Node<T> *parent): value(value), left(nullptr), right(nullptr), parent(parent),
                                                height(1) {}

template<class T>
bool Node<T>::isLeaf() const {
    return !left && !right;
}

template<class T>
int Node<T>::getBalanceFactor() const {
    int leftHeight = left ? left->height : 0;
    int rightHeight = right ? right->height : 0;
    return rightHeight - leftHeight;
}

#endif //DSA_NODE_HPP
