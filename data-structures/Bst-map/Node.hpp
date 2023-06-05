//
// Created by alexs on 2023-06-04.
//

#ifndef DSA_NODE_HPP
#define DSA_NODE_HPP

template<class K, class T>
class Node {
public:
    K key;
    T value;
    Node *left;
    Node *right;
    Node *parent;
    int height;

    Node(const K &key, const T &value, Node *parent);

    Node(const T &value, Node *other);

    bool isLeaf() const;

    int getBalanceFactor() const;
};

#include "Node.tpp"

#endif //DSA_NODE_HPP
