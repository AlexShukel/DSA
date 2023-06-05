//
// Created by alexs on 2023-06-04.
//

#ifndef DSA_AVLMAP_HPP
#define DSA_AVLMAP_HPP

#include "BstMap.hpp"

template<class K, class T>
struct NodeOverflow {
    Node<K, T> *X;
    Node<K, T> *Z;

    NodeOverflow(Node<K, T> *X, Node<K, T> *Z) : X(X), Z(Z) {};
};

template<class K, class T>
class AvlMap : public BstMap<K, T> {
private:
    // See https://en.wikipedia.org/wiki/AVL_tree#Rebalancing
    Node<K, T> *rotateLeft(Node<K, T> *X, Node<K, T> *Z);

    Node<K, T> *rotateRight(Node<K, T> *X, Node<K, T> *Z);

    Node<K, T> *rotateRightLeft(Node<K, T> *X, Node<K, T> *Z);

    Node<K, T> *rotateLeftRight(Node<K, T> *X, Node<K, T> *Z);

    void updateBalanceFactors(Node<K, T> *from);

    NodeOverflow<K, T> findOverflowedNode(Node<K, T> *from);

    void applyRotations(Node<K, T> *X, Node<K, T> *Z);

public:
    explicit AvlMap() = default;

    Node<K, T> *insert(const K &key, const T &value) override;

    Node<K, T> *remove(const K &key) override;

#ifdef AVL_TEST

    bool isAvl() const;

    void printAvl();

#endif //AVL_TEST
};

#include "AvlMap.tpp"

#endif //DSA_AVLMAP_HPP
